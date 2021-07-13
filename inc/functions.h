#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <gb/gb.h>
#include <rand.h>
#include "gameCharacter.h"
#include "knight_sprites.h"
#include "knight_tiles.h"
#include "ForestBG.h"
#include "GameOverBackground.h"

#define SPEED 3

extern BOOLEAN game_on;

extern UINT8 i;
extern UINT8 spritesize;

extern UINT16 score;
extern UINT8 lives;

extern BOOLEAN hit;

extern UINT8 frame;

extern uint16_t seed;

extern unsigned char windowmap[];

extern void interruptLCD();
extern void turnOnSound();
extern void turnOffSound();
extern void init();
extern void performDelay(UINT8 numloops);

extern UBYTE checkCollision(GameCharacter* one, GameCharacter* two);
extern void moveCharacter(GameCharacter* character, UINT8 x, UINT8 y);
extern void setupPlayer();
extern void playerAnimation();
extern void setupCoins();
extern void positionCoins();
extern void setupArrow();
extern void positionArrow();
extern void setupObstacles();
extern void positionObstacles();

extern void joyHandler();

extern void updateLives();
extern void setupBackground();
extern void fadeOut();
extern void fadeIn();
extern void resetBackground();
extern void updateCoinsCounter();
extern void updateHealth();
extern UINT8 randomize(UINT8 n);
extern void gameOverScreen();

#endif