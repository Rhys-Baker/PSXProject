#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "cdrom.h"
#include "controller.h"
#include "filesystem.h"
#include "font.h"
#include "gpu.h"
#include "gte.h"
#include "irq.h"
#include "model.h"
#include "menu.h"
#include "spu.h"
#include "stream.h"
#include "trig.h"

#include "registers.h"
#include "system.h"

#define SCREEN_WIDTH     320
#define SCREEN_HEIGHT    256


// Include texture data files
extern const uint8_t fontData[];
extern const uint8_t fontPalette[];
TextureInfo font;

extern const uint8_t reference_64Data[];
extern const uint8_t reference_64Palette[];
TextureInfo reference_64;

extern const uint8_t myHead_256Data[];
TextureInfo myHead_256;

extern const uint8_t obama_256Data[];
TextureInfo obama_256;

extern const uint8_t filth_128Data[];
TextureInfo filth_128;

Model myHead;
Model obamaPrism;
Model filth;
Model amorph;

int screenColor = 0xfa823c;

// Lookup table of 6 colours, used for debugging purposes
int colours[6] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0xFF00FF,
    0xFFFF00,
    0x00FFFF
};


bool showingText = true;

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
    uploadIndexedTexture(&font, fontData, SCREEN_WIDTH, 0, FONT_WIDTH, FONT_HEIGHT, 
        fontPalette, SCREEN_WIDTH, FONT_HEIGHT, GP0_COLOR_4BPP);
    uploadIndexedTexture(&reference_64, reference_64Data, SCREEN_WIDTH, FONT_HEIGHT+1,
        64, 64, reference_64Palette, SCREEN_WIDTH, FONT_HEIGHT+65, GP0_COLOR_4BPP);

    uploadTexture(&myHead_256, myHead_256Data, SCREEN_WIDTH + 256, 0, 256, 256);
    uploadTexture(&obama_256, obama_256Data, SCREEN_WIDTH + 256, 256, 256, 256);
    uploadTexture(&filth_128, filth_128Data, SCREEN_WIDTH, 128, 128, 128);
}

// Used for movement calculations.
int yawSin;
int yawCos;

Camera mainCamera = {
    .x=2000,
    .y=-(3*128),
    .z=0,
    .pitch=0,
    .yaw=1024,
    .roll=0,
    };


// Functions for look controls
void lookLeft(void){
    mainCamera.yaw += 20;
}
void lookRight(void){
    mainCamera.yaw -= 20;
}
void lookUp(void){
    mainCamera.pitch -= 20;
}
void lookDown(void){
    mainCamera.pitch += 20;
}

// Functions for move controls
void moveForward(void){
    mainCamera.x -= (((int)yawSin) * MOVEMENT_SPEED) >>9;
    mainCamera.z += (((int)yawCos) * MOVEMENT_SPEED) >>9;
}
void moveBackward(void){
    mainCamera.x += (((int)yawSin) * MOVEMENT_SPEED) >>9;
    mainCamera.z -= (((int)yawCos) * MOVEMENT_SPEED) >>9;
}
void moveLeft(void){
    mainCamera.x -=  (((int)yawCos) * MOVEMENT_SPEED) >>9;
    mainCamera.z += -(((int)yawSin) * MOVEMENT_SPEED) >>9;
}
void moveRight(void){
    mainCamera.x +=  (((int)yawCos) * MOVEMENT_SPEED) >>9;
    mainCamera.z -= -(((int)yawSin) * MOVEMENT_SPEED) >>9;
}

void moveUp(void){
    mainCamera.y -= 32;
}
void moveDown(void){
    mainCamera.y += 32;
}

// Misc button functions
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

void toggleText(void){
    showingText = !showingText;
}

Menu pauseMenu;
Menu settingsMenu;

bool gamePaused = false;
void pauseGame(void);
void unpauseGame(void);
void runSelectedItem(void);

void runSelectedItem(void){
    if(activeMenu->menuItems[selectedMenuIndex].function!=NULL){
        (*activeMenu->menuItems[selectedMenuIndex].function)();
    }
}

void pauseGame(void){
    // TODO: Set up an actual GAMESTATE machine
    // Set game state to GAMESTATE_PAUSED
    if(!gamePaused){
        gamePaused = true;
    }
    activeMenu = &pauseMenu;
    selectedMenuIndex = 0;
    
    // Update all the controls. Set any unused controls to null.
    controller_unsubscribeAll();

    controller_subscribeOnKeyDown(&runSelectedItem,    BUTTON_INDEX_X       );
    controller_subscribeOnKeyDown(&selectPrevMenuItem, BUTTON_INDEX_UP      );
    controller_subscribeOnKeyDown(&selectNextMenuItem, BUTTON_INDEX_DOWN    );
    controller_subscribeOnKeyDown(&unpauseGame,        BUTTON_INDEX_START   );
}

void unpauseGame(void){
    if(gamePaused){
        gamePaused = false;
    }
    // Remove the active menu
    activeMenu = NULL;

    // Update all the controls
    controller_unsubscribeAll();
    // Look controls
    controller_subscribeOnKeyHold(&lookLeft,     BUTTON_INDEX_SQUARE  );
    controller_subscribeOnKeyHold(&lookRight,    BUTTON_INDEX_CIRCLE  );
    controller_subscribeOnKeyHold(&lookUp,       BUTTON_INDEX_TRIANGLE);
    controller_subscribeOnKeyHold(&lookDown,     BUTTON_INDEX_X       );
    // Move controls
    controller_subscribeOnKeyHold(&moveForward,  BUTTON_INDEX_UP      );
    controller_subscribeOnKeyHold(&moveBackward, BUTTON_INDEX_DOWN    );

    controller_subscribeOnKeyHold(&moveLeft,     BUTTON_INDEX_LEFT    );
    controller_subscribeOnKeyHold(&moveRight,    BUTTON_INDEX_RIGHT   );
    controller_subscribeOnKeyDown(&pauseGame,    BUTTON_INDEX_START   );
    // Visual toggles
    controller_subscribeOnKeyDown(&toggleText,   BUTTON_INDEX_L1);
    // Sound
    controller_subscribeOnKeyDown(&swapMusic,    BUTTON_INDEX_L2);
    controller_subscribeOnKeyDown(&playSfx,      BUTTON_INDEX_R2);
}

void showSettingsMenu(void){
    selectedMenuIndex = 0;
    activeMenu = &settingsMenu;
}
void showPauseMenu(void){
    selectedMenuIndex = 0;
    activeMenu = &pauseMenu;
}

// TODO: Consider renaming this to be a bit more specific?
// This is for anything that has a model, basically. Probably going to extend the functionality in future.
typedef struct Entity{
    Model *model;
    TextureInfo *texture;
    uint32_t xpos, ypos, zpos;
    uint16_t xrot, yrot, zrot;
} Entity;

Entity loadedEntities[128];


int loadEntity(Model *model, TextureInfo *texture, uint32_t xpos, uint32_t ypos, uint32_t zpos, uint16_t xrot, uint16_t yrot, uint16_t zrot){
    // Linear search to find next free entry
    for(int i=0; i<128; i++){
        if(loadedEntities[i].model == NULL){
            loadedEntities[i].model = model;
            loadedEntities[i].texture = texture;
            loadedEntities[i].xpos = xpos;
            loadedEntities[i].ypos = ypos;
            loadedEntities[i].zpos = zpos;
            loadedEntities[i].xrot = xrot;
            loadedEntities[i].yrot = yrot;
            loadedEntities[i].zrot = zrot;
            return i;
        }
    }
    return -1;
}
void unloadEntity(int index){
    loadedEntities[index].model = NULL;
}

void spawnFilthAtPlayer(void){
    loadEntity(&filth, &filth_128, -mainCamera.x, 0, -mainCamera.z, 0, 0, (-mainCamera.yaw)-(ONE/4));
}

void spawnObamaAtPlayer(void){
    loadEntity(&obamaPrism, &obama_256, -mainCamera.x, 0, -mainCamera.z, 0, 0, (-mainCamera.yaw)-(ONE/4));
}

void spawnAmorphAtPlayer(void){
    loadEntity(&amorph, &reference_64, -mainCamera.x, 0, -mainCamera.z, 0, 0, (-mainCamera.yaw)-(ONE/4));
}


// Start of main
__attribute__((noreturn))
int main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();
    stream_init();
    printf("Logging started!\n");
    
    // Load model from the disk
    model_load("MYHEAD.MDL;1", &myHead);
    model_load("OBAMA.MDL;1", &obamaPrism);
    model_load("FILTH.MDL;1", &filth);
    model_load("AMORPH.MDL;1", &amorph);
    printf("All models loaded. Max verts length: %d\n", maxNumVerts);
    
    transformedVerts = malloc(sizeof(TransformedVert) * maxNumVerts);

    // Load sound and song from disk.
    sound_loadSound("LASER.VAG;1", &laser);
    stream_loadSong("SONG.VAG;1");
    printf("All sounds and songs loaded. Beginning song playback\n");
    
    // Begin playback of music on channels 0 and 1.
    stream_startWithChannelMask(MAX_VOLUME, MAX_VOLUME, 0b000000000000000000000011);
    

    // The song uses Left and Right channels to hold the Combat and Calm songs.
    // I set the selected channel to Max on both left and right. This allows me
    // to swap the song instantly without needing to load anything.
    setChannelVolume(( selectedMusicChannel), MAX_VOLUME);
    setChannelVolume((!selectedMusicChannel), 0); // Mute the other channel

    // Set up the pause menu
    menu_create(&pauseMenu, "Pause", 5);
    menu_setItem(&pauseMenu, 0, "Resume",           unpauseGame);
    menu_setItem(&pauseMenu, 1, "Toggle Music",     swapMusic);
    menu_setItem(&pauseMenu, 2, "Spawn Filth",      spawnFilthAtPlayer);
    menu_setItem(&pauseMenu, 3, "Spawn ObamaPrism", spawnObamaAtPlayer);
    menu_setItem(&pauseMenu, 4, "Spawn Amorph",     spawnAmorphAtPlayer);
    printf("Menu created.\n");

    // TODO
    // Probably need to create a better function for this, but this will subscribe all the button events and set the game state
    unpauseGame();
    
    // Initialise Timer
    TIMER_CTRL(1) = (TIMER_CTRL_EXT_CLOCK);
    TIMER_TARGET(1) = 0xFFFF;
    int deltaTime = 0;
    int prevTimerValue = 0;
    if(TIMER_CTRL(1) & TIMER_CTRL_OVERFLOWED){
        deltaTime = 0xFFFF + TIMER_VALUE(1);
    } else {
        deltaTime = TIMER_VALUE(1);
    }
    int newTimerValue = TIMER_VALUE(1);
    // Main loop. Runs every frame, forever
    

    
    loadEntity(&filth, &filth_128, -500, 0, -375, 0, 0, 1024);
    loadEntity(&filth, &filth_128, -500, 0, -250, 0, 0, 1024);
    loadEntity(&filth, &filth_128, -500, 0, -125, 0, 0, 1024);

    loadEntity(&filth, &filth_128, -500, 0,  125, 0, 0,-1024);
    loadEntity(&filth, &filth_128, -500, 0,  250, 0, 0,-1024);
    loadEntity(&filth, &filth_128, -500, 0,  375, 0, 0,-1024);
    printf("Test entities loaded.\n");

    printf("Begin main loop!\n");
    for(;;){
        // Point to the relevant DMA chain for this frame, then swap the active frame.
        activeChain = &dmaChains[usingSecondFrame];
        usingSecondFrame = !usingSecondFrame;

        
        // Reset the ordering table to a blank state.
        clearOrderingTable((activeChain->orderingTable), ORDERING_TABLE_SIZE);
        activeChain->nextPacket = activeChain->data;

        // Refresh the GTE for transformations
        gte_setRotationMatrix(
            ONE, 0, 0,
            0, ONE, 0,
            0, 0, ONE
        );
        

        // Rotate camera
        rotateCurrentMatrix(mainCamera.pitch, mainCamera.roll, mainCamera.yaw);
        // Reset translation Matrix
        setTranslationMatrix(0, 0, 0);
        numPrims = 0;
        for (int i=0; i<128; i++){
            model_renderTextured(
                loadedEntities[i].model,
                loadedEntities[i].texture,
                &mainCamera,
                loadedEntities[i].xrot,
                loadedEntities[i].yrot,
                loadedEntities[i].zrot,
                loadedEntities[i].xpos,
                loadedEntities[i].ypos,
                loadedEntities[i].zpos
            );
        }


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

        // Display the help/debug text.
        if(showingText && !gamePaused){
            char textBuffer[1024];
            sprintf(
                textBuffer,
                "D-Pad: Move\n"
                "Face buttons: Look Around\n"
                "L1: Toggle menu\n"
                "L2: Toggle music\n"
                "R2: Play SFX\n\n"
                
                "Pitch(x): %d\n"
                "Roll (y): %d\n"
                "Yaw  (Z): %d\n\n"
                
                "x: %d\n"
                "y: %d\n"
                "z: %d\n\n"
                
                "Prims: %d\n"

                "dt: %d",

                mainCamera.pitch, mainCamera.roll, mainCamera.yaw,
                mainCamera.x, mainCamera.y, mainCamera.z,
                numPrims,
                deltaTime
            );

            printString(activeChain, &font, 10, 10, textBuffer);
        }

        // Update the stream state machine.
        // Feed more data if needed.
        // Do this every frame, or almost every frame.
        // It is non-blocking but must be checked constantly.
        stream_update();

        // Used for movement calculations.
        // Update these before polling the controller
        yawSin = isin(mainCamera.yaw);
        yawCos = icos(mainCamera.yaw);
        // Update the controller every frame.
        // Will run the function associated with each button if the button is pressed.
        controller_update();

        if(gamePaused){
            RenderActiveMenu(&font);
        }

        // This will wait for the GPU to be ready,
        // It also waits for Vblank.
        waitForGP0Ready();
        waitForVblank();

        // Update deltaTime
        newTimerValue = TIMER_VALUE(1);
        if(TIMER_CTRL(1) & TIMER_CTRL_OVERFLOWED){
            deltaTime = ((0xFFFF + newTimerValue - prevTimerValue) * 1000 ) / 15734;
        } else {
            deltaTime = ((newTimerValue - prevTimerValue) * 1000) / 15734;
        }
        prevTimerValue = newTimerValue;

        // Swap the frame buffers.
        bufferY = usingSecondFrame ? SCREEN_HEIGHT : 0;
        GPU_GP1 = gp1_fbOffset(bufferX, bufferY);

        // Give DMA a pointer to the last item in the ordering table.
        // We don't need to add a terminator, as it is already done for us by the OTC.
        sendLinkedList(&(activeChain->orderingTable)[ORDERING_TABLE_SIZE - 1]);
   }
    __builtin_unreachable();
}