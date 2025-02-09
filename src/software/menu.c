#include "menu.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "gpu.h"
#include "font.h"

// There can only be one active menu at a time. This is a global variable.
Menu* activeMenu = NULL;
uint8_t selectedMenuIndex = 0;

// TODO: potentially refactor the constructor. The title must be const and is passed by reference
// Should we specify the number of items upfront or make use of realloc?
// I generally like to avoid malloc on the psx because of the limited memory and the higher possiblity of wasted space.
void menu_create(Menu *menu, const char* title, uint8_t numItems){
    menu->title = title;
    menu->numItems = numItems;
    menu->menuItems = (MenuItem*)malloc(sizeof(MenuItem) * numItems);
}

int menu_setItem(Menu* menu, int index, const char* label, void (*function)()){
    if(index >= menu->numItems) return -1;
    menu->menuItems[index].label = label;
    menu->menuItems[index].function = function;
    return 0;
}

void menu_destroy(Menu* menu){
    free(menu->menuItems);
}

void RenderActiveMenu(TextureInfo *font){
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
    printString(activeChain, font, 0, 0, menuText);
}

// TODO: Check that the menu actually exists/is referenced before running the math.
void selectNextMenuItem(void){
    selectedMenuIndex = (selectedMenuIndex+1) % activeMenu->numItems;
}
void selectPrevMenuItem(void){
    selectedMenuIndex = (selectedMenuIndex-1 + activeMenu->numItems) % activeMenu->numItems;
}
void runSelectedItem(void){
    if(activeMenu->menuItems[selectedMenuIndex].function!=NULL){
        (*activeMenu->menuItems[selectedMenuIndex].function)();
    }
}