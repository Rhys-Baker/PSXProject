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


bool showingText = false;

// Used to keep track of which channel is playing.
// 0 is combat, 1 is clean.
int selectedMusicChannel = 1;
Sound laser;


typedef struct MenuItem{
    char *label;
    void (*function)();

} MenuItem;

typedef struct Menu{
    char *title;
    uint8_t numItems;
    MenuItem *menuItems;
} Menu;

// TODO: potentially refactor the constructor. The title must be const and is passed by reference
// Should we specify the number of items upfront or make use of realloc?
// I generally like to avoid malloc on the psx because of the limited memory and the higher possiblity of wasted space.
Menu menu_create(const char* title, uint8_t numItems){
    Menu _menu;
    _menu.title = title;
    _menu.numItems = numItems;
    _menu.menuItems = (MenuItem*)malloc(sizeof(MenuItem) * numItems);
    return _menu;
}

int menu_setItem(Menu* menu, int index, const char* label, void (*function)()){
    if(index >= menu->numItems) return -1;
    menu->menuItems[index].label = label;
    menu->menuItems[index].function = function;
    return 0;
}

Menu* activeMenu = NULL;


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



// TODO: Check that the menu actually exists/is referenced before running the math.
uint8_t selectedMenuIndex = 0;
void selectNextMenuItem(void){
    selectedMenuIndex = (selectedMenuIndex+1) % activeMenu->numItems;
}
void selectPrevMenuItem(void){
    selectedMenuIndex = (selectedMenuIndex-1 + activeMenu->numItems) % activeMenu->numItems;
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

void RenderActiveMenu(void){
    // Build a string for the menu
    char menuText[1024] = "";

    // Print the title with a fancy header
    sprintf(menuText, "=== %s ===\n", activeMenu->title);

    // Render each item's label
    for(int i=0; i<activeMenu->numItems; i++){
        if(i == selectedMenuIndex){
            sprintf(menuText, "%s>\t%s\n", menuText, activeMenu->menuItems[i]);
        } else {
            sprintf(menuText, "%s \t%s\n", menuText, activeMenu->menuItems[i]);
        }
    }
    printString(activeChain, &font, 0, 0, menuText);
}



// Start of main
__attribute__((noreturn))
int main(void){

    // Tell the compiler that variables might be updated randomly (ie, IRQ handlers)
    __atomic_signal_fence(__ATOMIC_ACQUIRE);

    // Initialise important things for later
    initHardware();
    stream_init();
    
    // Load model from the disk
    model_load("MYHEAD.MDL;1", &myHead);
    model_load("OBAMA.MDL;1", &obamaPrism);
    model_load("FILTH.MDL;1", &filth);

    // Load sound and song from disk.
    sound_loadSound("LASER.VAG;1", &laser);
    stream_loadSong("SONG.VAG;1");
    
    // Begin playback of music on channels 0 and 1.
    stream_startWithChannelMask(MAX_VOLUME, MAX_VOLUME, 0b000000000000000000000011);


    // The song uses Left and Right channels to hold the Combat and Calm songs.
    // I set the selected channel to Max on both left and right. This allows me
    // to swap the song instantly without needing to load anything.
    setChannelVolume(( selectedMusicChannel), MAX_VOLUME);
    setChannelVolume((!selectedMusicChannel), 0); // Mute the other channel

    // Set up the pause menu
    pauseMenu.title = "Pause Menu";
    pauseMenu.numItems = 5;
    pauseMenu.menuItems = malloc(sizeof(MenuItem) * 5);
    
    pauseMenu.menuItems[0].label = "Resume";
    pauseMenu.menuItems[0].function = unpauseGame;
    pauseMenu.menuItems[1].label = "Settings Menu";
    pauseMenu.menuItems[1].function = showSettingsMenu;
    pauseMenu.menuItems[2].label = "Third Item";
    pauseMenu.menuItems[2].function = NULL;
    pauseMenu.menuItems[3].label = "Fourth Item";
    pauseMenu.menuItems[3].function = NULL;
    pauseMenu.menuItems[4].label = "Fith Item";
    pauseMenu.menuItems[4].function = NULL;

    settingsMenu.title = "Settings";
    settingsMenu.numItems = 3;
    settingsMenu.menuItems = malloc(sizeof(MenuItem) * 3);

    settingsMenu.menuItems[0].label = "Setting 1";
    settingsMenu.menuItems[0].function = NULL;
    settingsMenu.menuItems[1].label = "Setting 2";
    settingsMenu.menuItems[1].function = NULL;
    settingsMenu.menuItems[2].label = "Back";
    settingsMenu.menuItems[2].function = showPauseMenu;



    // TODO
    // Probably need to create a better function for this, but this will subscribe all the button events and set the game state
    unpauseGame();


    // Main loop. Runs every frame, forever
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

        model_renderTextured(&filth, &filth_128, &mainCamera, 0, 0, 0, 0, 0 ,0);
        model_renderTextured(&myHead, &myHead_256, &mainCamera, 0, 0, 0, 0, 0, -2000);
        model_renderTextured(&obamaPrism, &obama_256, &mainCamera, 0, 0, 0, 0, 5000, -32000);


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
            sprintf(textBuffer, "D-Pad: Move\nFace buttons: Look Around\nL1: Toggle menu\nL2: Toggle music\nR2: Play SFX\n\nPitch(x): %d\nRoll (y): %d\nYaw  (Z): %d\n\nx: %d\ny: %d\nz: %d\n\n%d\n%d\n%d", mainCamera.pitch, mainCamera.roll, mainCamera.yaw, mainCamera.x, mainCamera.y, mainCamera.z, ((int)yawCos), ((int) yawCos) * 30, (((int)yawCos) * 30) >>12);
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
            RenderActiveMenu();
        }

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