#ifndef _CHARACTERS_H
#define _CHARACTERS_H

#include "functions.h"
#include "gameCharacter.h"
#include "knight_sprites.h"
#include "knight_tiles.h"
#include "ForestBG.h"

extern const UWORD spritePalette[];
extern const UWORD backgroundPalette[];

extern UINT8 i;
extern UINT8 spritesize;
extern UINT8 frame;
extern UINT8 spriteID;

extern BOOLEAN hit;
extern BOOLEAN explosion;

extern UBYTE checkCollision(GameCharacter* one, GameCharacter* two);
extern UBYTE checkPlayerCollision(GameCharacter* character);
extern void moveCharacter(GameCharacter* character, UINT8 x, UINT8 y);
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

#endif