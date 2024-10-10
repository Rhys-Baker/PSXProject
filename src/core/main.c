#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cdrom.h"
#include "controller.h"
#include "filesystem.h"
#include "font.h"
#include "gpu.h"
#include "gte.h"
#include "irq.h"
#include "spu.h"
#include "stream.h"

#include "registers.h"
#include "system.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

// the X and Y of the buffer we are currently using.
int bufferX = 0;
int bufferY = 0;
// The pointer to the DMA packet.
// We allocate space for each packet before we use it.
uint32_t *dmaPtr;
DMAChain dmaChains[2];
DMAChain *activeChain;
bool usingSecondFrame = false;

int screenColor = 0xfa823c;
int colours[6] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0xFF00FF,
    0xFFFF00,
    0x00FFFF
};


// Used to keep track of which channel is playing.
// 0 is combat, 1 is clean.
int selectedMusicChannel = 1;
Sound laser;


void waitForVblank(){
    while(!vblank){
        // Do nothing
    }
    vblank = false;
}

// Gets called once at the start of main.
void initHardware(void){
    // Enable display blanking if not already.
    // Prevents logo from appearing while loading.
    GPU_GP1 = gp1_dispBlank(true);

    // Initialise the serial port for printing
    initSerialIO(115200);
    initSPU();
    initCDROM();
    initIRQ();
    initControllerBus();
    initFilesystem();
    // TODO: Fill the screen with black / Add a loading screen here?
    initGPU(); // Disables screen blanking after setting up screen.
    
    setupGTE(SCREEN_WIDTH, SCREEN_HEIGHT);


    // Upload textures
    uploadIndexedTexture(&font, fontData, SCREEN_WIDTH+16, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, SCREEN_WIDTH+16, FONT_HEIGHT, GP0_COLOR_4BPP);
    
}

// Debugging hexdump function.
// Considering adding a "utilies" or "debug" library for these kinds of things
void hexdump(const uint8_t *ptr, size_t length) {
    while (length) {
        size_t lineLength = (length < 16) ? length : 16;
        length -= lineLength;

        for (; lineLength; lineLength--)
            printf(" %02x", *(ptr++));

        putchar('\n');
    }
}



void swapMusic(void){
    setChannelVolume(selectedMusicChannel, 0);
    selectedMusicChannel = !selectedMusicChannel;
    setChannelVolume(selectedMusicChannel, MAX_VOLUME);
    // Update screen colour to reflect which music we are playing.
    screenColor = selectedMusicChannel ? 0xfa823c : 0x0c34e8;
}

void playSfx(void){
    sound_play(&laser, MAX_VOLUME, MAX_VOLUME);
}



typedef struct Vert{
    int16_t x, y, z;
    int16_t _;
} Vert;
typedef struct Tri{
    uint16_t a, b, c;
    uint16_t _;

} Tri;
typedef struct Model{
    uint8_t  numVerts;
    uint16_t numTris;
    Vert    *verts;
    Tri     *tris;
} Model;

Model myModel;

void model_render(Model *model){
    printf("\n\nBegin model render.\n");

    for(int i = 0; i<model->numTris; i++){
        GTEVector16 a, b, c;
        a.x = (model->verts[model->tris[i].a].x);
        a.y = (model->verts[model->tris[i].a].y);
        a.z = (model->verts[model->tris[i].a].z);

        b.x = (model->verts[model->tris[i].b].x);
        b.y = (model->verts[model->tris[i].b].y);
        b.z = (model->verts[model->tris[i].b].z);

        c.x = (model->verts[model->tris[i].c].x);
        c.y = (model->verts[model->tris[i].c].y);
        c.z = (model->verts[model->tris[i].c].z);

        gte_loadV0(&a);
        gte_loadV1(&b);
        gte_loadV2(&c);
        printf("a: %d{%d, %d, %d}\n", model->tris[i].a, a.x, a.y, a.z);
        printf("b: %d{%d, %d, %d}\n", model->tris[i].b, b.x, b.y, b.z);
        printf("c: %d{%d, %d, %d}\n", model->tris[i].c, c.x, c.y, c.z);

        gte_command(GTE_CMD_RTPT | GTE_SF);
        gte_command(GTE_CMD_NCLIP);

        gte_command(GTE_CMD_AVSZ3 | GTE_SF);
        int zIndex = gte_getOTZ();

        //if(zIndex <= 0){
        //    printf(" Triangle is behind camera, continuing.\n");
        //    continue;
        //}

        dmaPtr = allocatePacket(activeChain, zIndex, 4);
        dmaPtr[0] = colours[i]| gp0_shadedTriangle(false, false, false);
        dmaPtr[1] = gte_getSXY0();
        dmaPtr[2] = gte_getSXY1();
        dmaPtr[3] = gte_getSXY2();
    }
};


/// @brief Load a model from a file on disc. The .verts and .tris properties will be set. It is important to free these as they are allocated on the heap. Use model_destroy() to do this.
/// @param name Filename for the model.
/// @param model Pointer to a model struct to store the data.
/// @return 
size_t model_load(const char *name, Model *model){
    uint32_t modelLba;
    uint16_t sectorBuffer[1024];
    
    modelLba = getLbaToFile(name);
    if(!modelLba){
        // File not found
        return 1;
    }

    printf(" LBA to file \"%s\": %d\n", name, modelLba);
    printf(" Start CDROM Read...\n");
    startCDROMRead(
        modelLba,
        sectorBuffer,
        1,
        2048,
        true,
        true
    );
    printf(" Read complete!\n");

    size_t sectorOffset = 0;

    uint16_t _numVerts = sectorBuffer[sectorOffset++];
    printf(" Num verts: %d\n", _numVerts);

    printf(" Allocating %d bytes of memory for vert array\n", (sizeof(Vert) * _numVerts));
    Vert *_verts = malloc(sizeof(Vert) * _numVerts);
    printf(" Allocated at 0x%x\n", _verts);
    

    printf(" Verts...\n");
    // For each vert
    for(int i = 0; i<_numVerts; i++){

        printf("  Write to struct at index: %d\n", i);
        // For each axis
        for(int j = 0; j < 3; j++){
            // If we are reaching past the buffer
            if(sectorOffset >= 1024){
                // Read the next sector
                startCDROMRead(
                    ++modelLba,
                    sectorBuffer,
                    1,
                    2048,
                    true,
                    true
                );
            }
            printf("   Write to struct data index: %d\n", j);
            // Copy the X, Y, then Z data into the struct, then increment the data pointer.
            ((uint16_t *) &_verts[i])[j] = sectorBuffer[sectorOffset++];
        }
        
    }

    // Also do the check here.
    if(sectorOffset >= 1024){
        // Read the next sector
        startCDROMRead(
            ++modelLba,
            sectorBuffer,
            1,
            2048,
            true,
            true
        );
    }

    uint16_t _numTris = sectorBuffer[sectorOffset++];
    printf(" Num tris: %d\n", _numTris);

    printf(" Allocating %d bytes of memory for tri array\n", (sizeof(Tri) * _numTris));
    Tri *_tris = malloc(sizeof(Tri) * _numTris);
    printf(" Allocated at 0x%x\n", _tris);

    printf(" Tris...\n");
    // For each triangle
    for(int i = 0; i<_numTris; i++){
        printf("  Write to struct at index: %d\n", i);
        // For each vert
        for(int j = 0; j < 3; j++){
            // If we are reaching past the buffer
            if(sectorOffset >= 1024){
                // Read the next sector
                startCDROMRead(
                    ++modelLba,
                    sectorBuffer,
                    1,
                    2048,
                    true,
                    true
                );
            }
            printf("   Write to struct data index: %d | %d\n", j, sectorBuffer[sectorOffset]);
            // Copy the a, b, then c vert pointer into the struct, then increment the data pointer.
            ((uint16_t *) &_tris[i])[j] = sectorBuffer[sectorOffset++];
        }
    }

    model->numVerts = _numVerts;
    model->numTris = _numTris;
    model->verts = _verts;
    model->tris = _tris;

    printf(" Model Load compelete!\n");
    return 0;
}

// TODO: Check that this is okay to do with invalid pointers. Will free() break if I pass some other pointer?
/// @brief Free the allocated pointers and set values to 0.
/// @param model Pointer to the model to destroy.
void model_destroy(Model *model){
    model->numVerts = 0;
    model->numTris = 0;
    free(model->verts);
    free(model->tris);
    model->verts = NULL;
    model->tris = NULL;

}



// Start of main
__attribute__((noreturn))
int main(void){   

    //Vert modelVerts[3] = {
    //    {.x =  10, .y =  10, .z =  0},
    //    {.x =  10, .y = -10, .z =  0},
    //    {.x = -10, .y = -10, .z =  0}
    //    //{.x = -10, .y =  10, .z =  0}
    //};
    //Tri modelTris[1] = {
    //    {.a = 1, .b = 2, .c = 0},
    //    //{.a = 3, .b = 0, .c = 2}
    //};
    //myModel.numVerts = 3;
    //myModel.verts = &modelVerts;
    //myModel.numTris = 1;
    //myModel.tris = &modelTris;

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();
    stream_init();
    

    printf("Begin Model Load\n");
    int result = model_load("MODEL.MDL;1", &myModel);
    printf("Model load result: %d\n", result);

    printf("HAHAHAH: %d %d %d\n", myModel.tris[0].a,myModel.tris[0].b,myModel.tris[0].c);

    sound_loadSound("LASER.VAG;1", &laser);
    stream_loadSong("SONG.VAG;1");

    //object_load("CUBE.OBJ;1", &cube);
    
    stream_startWithChannelMask(MAX_VOLUME, MAX_VOLUME, 0b000000000000000000000011);
    // This isn't necessarily a part of the stream function.
    // By default, the stream will play all channels. It is up to the user to handle the volume of which channels they want.
    setChannelVolume(( selectedMusicChannel), MAX_VOLUME);
    setChannelVolume((!selectedMusicChannel), 0); // Mute the other channel


    // Attach functions to button presses
    controller_attachFunctionToButton(&swapMusic, BUTTON_INDEX_CIRCLE);
    controller_attachFunctionToButton(&playSfx,   BUTTON_INDEX_SQUARE);


    
    // Main loop. Runs every frame, forever
    for(;;){
        // Point to the relevant DMA chain for this frame, then swap the active frame.
        activeChain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;

        // Reset the ordering table to a blank state.
        clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
        activeChain->nextPacket = activeChain->data;
      
        gte_setRotationMatrix(
            ONE, 0, 0,
            0, ONE, 0,
            0, 0, ONE
        );
        rotateCurrentMatrix(0,0,0);
        updateTranslationMatrix(0, 0, 0);

        model_render(&myModel);


        // Place the framebuffer offset and screen clearing commands last.
        // This means they will be executed first and be at the back of the screen.
        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE -1 , 3);
        dmaPtr[0] = screenColor | gp0_vramFill();
        dmaPtr[1] = gp0_xy(bufferX, bufferY);
        dmaPtr[2] = gp0_xy(SCREEN_WIDTH, SCREEN_HEIGHT);

        dmaPtr = allocatePacket(activeChain, ORDERING_TABLE_SIZE - 1, 4);
        dmaPtr[0] = gp0_texpage(0, true, false);
        dmaPtr[1] = gp0_fbOffset1(bufferX, bufferY);
        dmaPtr[2] = gp0_fbOffset2(bufferX + SCREEN_WIDTH - 1, bufferY + SCREEN_HEIGHT - 2);
        dmaPtr[3] = gp0_fbOrigin(bufferX, bufferY);


        // Update the stream state machine.
        // Feed more data if needed.
        // Do this every frame, or almost every frame.
        // It is non-blocking but must be checked constantly.
        stream_update();

        // Update the controller every frame.
        // Will run the function associated with each button if the button is pressed.
        controller_update();


        // This will wait for the GPU to be ready,
        // It also waits for Vblank.
        waitForGP0Ready();
        waitForVblank();

        // Swap the frame buffers.
        bufferY = usingSecondFrame ? SCREEN_HEIGHT : 0;
        GPU_GP1 = gp1_fbOffset(bufferX, bufferY);

        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(activeChain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
   }

    __builtin_unreachable();
}