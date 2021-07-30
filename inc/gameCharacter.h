#ifndef _GAMECHARACTER_H
#define _GAMECHARACTER_H

#include <gb/gb.h>

typedef struct GameCharacter{
    UINT8 spriteID[4];
    UINT8 x;
    UINT8 y;
    UINT8 w;
    UINT8 h;
    UINT8 health;
} GameCharacter;

extern GameCharacter player;

extern GameCharacter coins[3];

extern GameCharacter arrow;

extern GameCharacter obstacles[2];

extern GameCharacter bombs;

#endif