#ifndef _CHARACTERS_H
#define _CHARACTERS_H

#include <stdint.h>
#include "functions.h"
#include "gameCharacter.h"
#include "knight_sprites.h"
#include "knight_tiles.h"
#include "ForestBG.h"

extern const UWORD spritePalette[];
extern const UWORD backgroundPalette[];

extern uint8_t i;
extern uint8_t spritesize;
extern uint8_t frame;
extern uint8_t spriteID;
extern uint8_t timer;

extern BOOLEAN shield;
extern BOOLEAN hit;
extern BOOLEAN explosion;

extern UBYTE checkCollision(GameCharacter* one, GameCharacter* two);
extern UBYTE checkPlayerCollision(GameCharacter* character);
extern void checkObstacles(GameCharacter* one, GameCharacter* two);
extern void moveCharacter(GameCharacter* character, uint8_t x, uint8_t y);
extern void setupPlayer();
extern void animations();
extern void setupCoins();
extern void positionCoins();
extern void setupArrow();
extern void positionArrow();
extern void setupObstacles();
extern void positionObstacles();
extern void setupBombs();
extern void positionBombs();
extern void setupBackground();
extern void setupCharacters();

#endif