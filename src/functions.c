#include "../inc/functions.h"

UINT8 i;
UINT8 spritesize = 8;
UINT8 swap;

UINT8 frame;
UINT8 spriteID;

UINT16 score = 0;
UINT8 lives = 3;

unsigned char windowmap[] = {
    0x1D,0x0D,0x19,0x1C,0x0F,0x00,0x01,0x01,0x01,0x01,0x00,0x30,0x22,0x01,0x01,0x00,0x31,0x31,0x31,0x00
};

void interruptLCD(){
    HIDE_WIN;
}

void turnOnSound(){
    NR52_REG = 0x8F; //Turn on the sound
    NR51_REG = 0x11; //Enable the sound channel
    NR50_REG = 0x77; //Increase the volume to its max
}

void turnOffSound(){
    NR52_REG = 0x00;
}

void init(){
    SHOW_WIN;
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
    turnOnSound();

    add_LCD(interruptLCD);
    enable_interrupts();
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
}

void performDelay(UINT8 numloops){
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

UBYTE checkCollision(GameCharacter* one, GameCharacter* two){
    return(one->x >= two->x && one->x <= two->x + two->w) && (one->y >= two->y && one->y <= two->y + two->h) || (two->x >= one->x && two->x <= one->x + one->w) && (two->y >= one->y && two->y <= one->y + one->h);
}

void moveCharacter(GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spriteID[0], x, y);
    move_sprite(character->spriteID[1], x + spritesize, y);
    move_sprite(character->spriteID[2], x, y + spritesize);
    move_sprite(character->spriteID[3], x + spritesize, y + spritesize);
}

void setupPlayer(){
    player.x = 80;
    player.y = 20;
    player.h = 16;
    player.w = 16;
    player.health = 3;

    //load player's sprites
    set_sprite_tile(0, 0);
    player.spriteID[0] = 0;
    set_sprite_tile(2, 2);
    player.spriteID[1] = 2;
    set_sprite_tile(1, 1);
    player.spriteID[2] = 1;
    set_sprite_tile(3, 3);
    player.spriteID[3] = 3;

    moveCharacter(&player, player.x, player.y);
}

void playerAnimation(){
    UINT8 n = 3*frame + frame;
    set_sprite_tile(0, 0 + n);
    set_sprite_tile(2, 2 + n);
    set_sprite_tile(1, 1 + n);
    set_sprite_tile(3, 3 + n);

    frame++;
    performDelay(4);
}

void setupCoins(){
    for(i = 0; i < 3; i++){
        coins[i].x = 48 + randomize(64);
        coins[i].y = player.y + 120 + randomize(80);
        coins[i].h = 8;
        coins[i].w = 8;
        coins[i].health = 1;

        spriteID = 4 + i;
        //load coin's sprite
        set_sprite_tile(spriteID, 12);
        coins[i].spriteID[0] = spriteID;

        move_sprite(coins[i].spriteID[0], coins[i].x, coins[i].y);
    }
}

void positionCoins(){
    for(i = 0; i < 3; i++){
        if(coins[i].health > 0){
            coins[i].y -= 4;
            if(checkCollision(&player, &coins[i]) == TRUE || coins[i].y < 8){
                coins[i].health = 0;
            }
        } else {
            coins[i].x = 48 + randomize(64);
            coins[i].y = player.y + 120;  
            coins[i].health = 1;
            //performDelay(2);
        }
        move_sprite(coins[i].spriteID[0], coins[i].x, coins[i].y);
    }
}

void setupArrow(){
    arrow.x = 48 + randomize(64);
    arrow.y = player.y + 120;
    arrow.h = 8;
    arrow.w = 6;
    arrow.health = 1;

    spriteID += 1;
    set_sprite_tile(spriteID, 14);
    arrow.spriteID[0] = spriteID;

    move_sprite(arrow.spriteID[0], arrow.x, arrow.y);
}

void positionArrow(){
    if(arrow.health > 0){
        arrow.y -= 8;
        if(checkCollision(&player, &arrow) == TRUE || arrow.y < 8){
            arrow.health = 0;
        }
    } else {
        arrow.x = 48 + randomize(64);
        arrow.y = player.y + 120;
        arrow.health = 1;
    }
    move_sprite(arrow.spriteID[0], arrow.x, arrow.y);
}

void setupBackground(){
    set_bkg_data(37, 13, Knight_tiles);
    set_bkg_tiles(0, 0, ForestBGWidth, ForestBGHeight, ForestBG);
}

void joyHandler(){
    switch (joypad())
    {
    case J_LEFT:
        player.x -= 16;
        break;
    case J_RIGHT:
        player.x += 16;
    default:
        player.x += 0;
        break;
    }
}

//Creates a fade out effect
void fadeOut(){
    for(i = 0; i < 4; i++){
        switch (i)
        {
        case 0:
            BGP_REG = 0xE4;
            break;
        case 1:
            BGP_REG = 0xF9;
            break;
        case 2:
            BGP_REG = 0xFE;
            break;
        case 3:
            BGP_REG = 0xFF;
            break;
        }
        performDelay(10);
    }
}

//Creates a fade in effect
void fadeIn(){
    for(i = 0; i < 3; i++){
        switch (i)
        {
        case 0:
            BGP_REG = 0xFE;
            break;
        case 1:
            BGP_REG = 0xF9;
            break;
        case 2:
            BGP_REG = 0xE4;
            break;
        }
        performDelay(10);
    }
}

void resetBackground(){
    HIDE_WIN;
    move_bkg(0, 0); //Moves background to its default position
    HIDE_SPRITES;
}

////Creates a random number between 0 - n
UINT8 randomize(UINT8 n){
    return rand() % n;
}