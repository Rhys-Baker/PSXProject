#pragma once

#include <stdint.h>
#include "gpu.h"

// MenuItems are essentially just buttons. They are displayed in the menu.
typedef struct MenuItem{
    const char *label;
    void (*function)();

} MenuItem;

// Menu struct
typedef struct Menu{
    const char *title;
    uint8_t numItems;
    MenuItem *menuItems;
} Menu;

// There can only be one active menu at a time. This is a global variable.
extern Menu* activeMenu;
extern uint8_t selectedMenuIndex;

// TODO: potentially refactor the constructor. The title must be const and is passed by reference
// Should we specify the number of items upfront or make use of realloc?
// I generally like to avoid malloc on the psx because of the limited memory and the higher possiblity of wasted space.
void menu_create(Menu *menu, const char* title, uint8_t numItems);

int menu_setItem(Menu* menu, int index, const char* label, void (*function)());

void RenderActiveMenu(TextureInfo *font);

// TODO: Check that the menu actually exists/is referenced before running the math.
void selectNextMenuItem(void);
void selectPrevMenuItem(void);