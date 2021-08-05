#ifndef _GAMECHARACTER_H
#define _GAMECHARACTER_H

#include <gb/gb.h>
#include <stdint.h>

typedef struct GameCharacter{
    uint8_t spriteID[4];
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
    uint8_t health;
} GameCharacter;

extern GameCharacter player;

extern GameCharacter coins[3];

extern GameCharacter arrow;

extern GameCharacter obstacles[2];

extern GameCharacter bombs;

#endif