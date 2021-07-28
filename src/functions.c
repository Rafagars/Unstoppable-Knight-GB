#include "../inc/functions.h"

BOOLEAN game_on = TRUE;

const UWORD spritePalette[] = {
    /* Gameboy Color palette 0 */
    knight_spritesCGBPal0c0,
    knight_spritesCGBPal0c1,
    knight_spritesCGBPal0c2,
    knight_spritesCGBPal0c3,

    /* Gameboy Color palette 1 */
    knight_spritesCGBPal1c0,
    knight_spritesCGBPal1c1,
    knight_spritesCGBPal1c2,
    knight_spritesCGBPal1c3,

    /* Gameboy Color palette 2 */
    knight_spritesCGBPal2c0,
    knight_spritesCGBPal2c1,
    knight_spritesCGBPal2c2,
    knight_spritesCGBPal2c3,

    /* Gameboy Color palette 3 */
    knight_spritesCGBPal3c0,
    knight_spritesCGBPal3c1,
    knight_spritesCGBPal3c2,
    knight_spritesCGBPal3c3,

    /* Gameboy Color palette 4 */
    knight_spritesCGBPal4c0,
    knight_spritesCGBPal4c1,
    knight_spritesCGBPal4c2,
    knight_spritesCGBPal4c3,


    /* Gameboy Color palette 5 */
    knight_spritesCGBPal5c0,
    knight_spritesCGBPal5c1,
    knight_spritesCGBPal5c2,
    knight_spritesCGBPal5c3,
};

const UWORD backgroundPalette[] = {
    /* Gameboy Color palette 0 */
    Knight_tilesCGBPal0c0,
    Knight_tilesCGBPal0c1,
    Knight_tilesCGBPal0c2,
    Knight_tilesCGBPal0c3,

    /* Gameboy Color palette 1 */
    Knight_tilesCGBPal1c0,
    Knight_tilesCGBPal1c1,
    Knight_tilesCGBPal1c2,
    Knight_tilesCGBPal1c3,

    /* Gameboy Color palette 2 */
    Knight_tilesCGBPal2c0,
    Knight_tilesCGBPal2c1,
    Knight_tilesCGBPal2c2,
    Knight_tilesCGBPal2c3,

    /* Gameboy Color palette 3 */
    Knight_tilesCGBPal3c0,
    Knight_tilesCGBPal3c1,
    Knight_tilesCGBPal3c2,
    Knight_tilesCGBPal3c3,
};

UINT8 i;
UINT8 spritesize = 8;
UINT8 swap = 0;
UINT8 frame;
UINT8 expFrame = 0;
UINT8 spriteID;

BOOLEAN hit = FALSE;
BOOLEAN explosion = FALSE;

uint16_t seed;

unsigned char windowmap[] = {
    0x1D,0x0D,0x19,0x1C,0x0F,0x00,0x01,0x01,0x01,0x01,0x00,0x30,0x22,0x01,0x01,0x00,0x31,0x31,0x31,0x00
};

void interruptLCD(){
    HIDE_WIN;
}

void turnOnSound(){
    NR52_REG = 0x8F; //Turn on the sound
    NR51_REG = 0x11; //Enable the sound channels
    NR50_REG = 0x77; //Increase the volume to its max()
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

// Give the player a smaller hitbox
UBYTE checkPlayerCollision(GameCharacter* character){
    return(player.x  + 2 >= character->x && player.x + 2 <= character->x + character->w) && (player.y + 2 >= character->y && player.y + 2 <= character->y + character->h) || (character->x >= player.x + 2 && character->x <= player.x + player.w - 2) && (character->y >= player.y + 2 && character->y <= player.y + player.h - 2);
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
    set_sprite_tile(2, 0);
    player.spriteID[1] = 2;
    set_sprite_tile(1, 1);
    player.spriteID[2] = 1;
    set_sprite_tile(3, 3);
    player.spriteID[3] = 3;

    moveCharacter(&player, player.x, player.y);
}

void Animations(){
    UINT8 n = 3*frame + frame;
    UINT8 m = 3*expFrame + expFrame;

    //Orc Animation
    set_sprite_tile(obstacles[1].spriteID[0], 19 + n);
    set_sprite_prop(obstacles[1].spriteID[0], S_PRIORITY | 4);
    set_sprite_tile(obstacles[1].spriteID[2], 20 + n);
    set_sprite_prop(obstacles[1].spriteID[2], S_PRIORITY | 4);    
    set_sprite_tile(obstacles[1].spriteID[1], 21 + n);
    set_sprite_prop(obstacles[1].spriteID[1], S_PRIORITY | 4);    
    set_sprite_tile(obstacles[1].spriteID[3], 22 + n); 
    set_sprite_prop(obstacles[1].spriteID[3], S_PRIORITY | 4);

    //Bomb animation
    set_sprite_tile(bombs.spriteID[0], 32 + n);
    set_sprite_prop(bombs.spriteID[0], 0);
    set_sprite_tile(bombs.spriteID[2], 33 + n);
    set_sprite_prop(bombs.spriteID[2], 0);    
    set_sprite_tile(bombs.spriteID[1],  34 + n);
    set_sprite_prop(bombs.spriteID[1], 0);    
    set_sprite_tile(bombs.spriteID[3], 35 + n); 
    set_sprite_prop(bombs.spriteID[3], 0);    

    if(obstacles[0].y < 8){
        hit = FALSE;
    }

    if(hit == TRUE){
        //Hit effect
        set_sprite_tile(0, 49);
        set_sprite_tile(2, 49);
        set_sprite_tile(1, 49);
        set_sprite_tile(3, 49);
        performDelay(2);
        set_sprite_tile(0, 0 + n);
        set_sprite_tile(2, 2 + n);
        set_sprite_tile(1, 1 + n);
        set_sprite_tile(3, 3 + n);
        performDelay(2);
    } else {
        //Default Animation
        set_sprite_tile(0, 0 + n);
        set_sprite_tile(2, 2 + n);
        set_sprite_tile(1, 1 + n);
        set_sprite_tile(3, 3 + n);
        performDelay(4);
    }
    frame++;
}

void explosionAnimation(){
    UINT8 m = 3*expFrame + expFrame;
    if(explosion == TRUE){
        set_sprite_tile(bombs.spriteID[0], 19 + m);
        performDelay(2);
        expFrame++;
    }
}

void setupCoins(){
    for(i = 0; i < 3; i++){
        coins[i].x = 16*randomize(5) + 48;
        coins[i].y = player.y + 120 + randomize(80);
        coins[i].h = 8;
        coins[i].w = 8;
        coins[i].health = 1;

        spriteID = 4 + i;
        //load coin's sprite
        set_sprite_tile(spriteID, 12);
        set_sprite_prop(spriteID, 1);
        coins[i].spriteID[0] = spriteID;

        move_sprite(coins[i].spriteID[0], coins[i].x, coins[i].y);
    }
}

void positionCoins(){
    for(i = 0; i < 3; i++){
        if(coins[i].health > 0){
            coins[i].y -= 4;
            if(checkCollision(&player, &coins[i]) == TRUE ){
                coins[i].health = 0;
                coinSound();
                updateCoinsCounter();
                updateScore();
            } else if(coins[i].y < 8){
                coins[i].health = 0;
            }
        } else {
            coins[i].x = 16*randomize(5) + 48;
            coins[i].y = player.y + 120;  
            coins[i].health = 1;

            //Not exactly sure if this part of the code do something or not. Sometimes it looks like it does, sometimes don't
            
            if(checkCollision(&coins[i], &obstacles[0]) == TRUE || checkCollision(&coins[i], &bombs) == TRUE || checkCollision(&coins[i], &coins[i+1]) == TRUE){
                coins[i].x = 16*randomize(5) + 48;
                coins[i].y = player.y + 120; 
            }
            
            //
        }
        move_sprite(coins[i].spriteID[0], coins[i].x, coins[i].y);
    }
}

void setupArrow(){
    arrow.x = 16*randomize(5) + 48;
    arrow.y = player.y + 120;
    arrow.h = 8;
    arrow.w = 6;
    arrow.health = 1;

    spriteID += 1;
    set_sprite_tile(spriteID, 14);
    set_sprite_prop(spriteID, 3);
    arrow.spriteID[0] = spriteID;

    move_sprite(arrow.spriteID[0], arrow.x, arrow.y);
}

void positionArrow(){
    if(arrow.health > 0){
        arrow.y -= 8;
        if(checkPlayerCollision(&arrow) == TRUE && hit == FALSE){
            arrow.health = 0;
            player.health--;
            hit = TRUE;
            hitSound();
        } else if(arrow.y < 8){
            arrow.health = 0;
        }
    } else {
        arrow.x = 16*randomize(5) + 48;
        arrow.y = player.y + 120;
        arrow.health = 1;
    }
    move_sprite(arrow.spriteID[0], arrow.x, arrow.y);
}

void setupObstacles(){
    spriteID += 1;
    for(i = 0; i < 2; i++){
        obstacles[i].x = 16*randomize(4) + 64;
        obstacles[i].y = player.y + 120;
        obstacles[i].w = 16;
        obstacles[i].h = 16;
        obstacles[i].health = 1;

        UINT8 n = (4*i + i);
        //load obstacles's sprites
        set_sprite_tile(spriteID + n, 15 + n);
        set_sprite_prop(spriteID + n, 3 + i);
        obstacles[i].spriteID[0] = spriteID + n;
        set_sprite_tile(spriteID + n + 1 , 16 + n);
        set_sprite_prop(spriteID + n + 1, 3 + i);
        obstacles[i].spriteID[2] = spriteID + n + 1;
        set_sprite_tile(spriteID + n + 2, 17 + n);
        set_sprite_prop(spriteID + n + 2, 3 + i);
        obstacles[i].spriteID[1] = spriteID + n + 2;
        set_sprite_tile(spriteID + n + 3, 18 + n);
        set_sprite_prop(spriteID + n + 3, 3 + i);
        obstacles[i].spriteID[3] = spriteID + n + 3;

        moveCharacter(&obstacles[i], obstacles[i].x, obstacles[i].y); 
    }   
}

void positionObstacles(){
    for(i = 0; i < 2; i++){
        if(obstacles[i].health > 0){
            obstacles[i].y -= 4 + 2*i;
            if(obstacles[i].y < 8){
                obstacles[i].health = 0;
            }else if(checkPlayerCollision(&obstacles[i]) == TRUE && hit == FALSE){
                player.health--;
                hit = TRUE;
                hitSound();
            }
        } else {
            obstacles[i].x = 16*randomize(4) + 64;
            obstacles[i].y = player.y + 120;
            obstacles[i].health = 1;
            if(obstacles[0].x == obstacles[1].x && obstacles[0].y - obstacles[1].y < 16){
                if(obstacles[0].x > 64 && obstacles[0].x < 80){
                    obstacles[1].x = obstacles[0].x + 16;    
                } else {
                    obstacles[1].x = obstacles[0].x - 16;    
                }
            } 
        }
        moveCharacter(&obstacles[i], obstacles[i].x, obstacles[i].y);
    }
}

void setupBombs(){ 
    bombs.x = 16*randomize(5) + 48;
    bombs.y = player.y + 120;
    bombs.h = 16;
    bombs.w = 16;
    bombs.health = 1;

    set_sprite_tile(17 , 32);
    set_sprite_prop(17, 0);
    bombs.spriteID[0] = 17;
    set_sprite_tile(18, 33);
    set_sprite_prop(18, 0);
    bombs.spriteID[2] = 18;
    set_sprite_tile(19, 33);
    set_sprite_prop(19, 0);
    bombs.spriteID[1] = 19;
    set_sprite_tile(20, 34);
    set_sprite_prop(20, 0);
    bombs.spriteID[3] = 20;

    moveCharacter(&bombs, bombs.x, bombs.y); 
}

void positionBombs(){
    if(bombs.health > 0){
        bombs.y -= 4;
        if(checkPlayerCollision(&bombs) == TRUE && hit == FALSE){
            bombs.health = 0;
            explosionAnimation();
            player.health--;
            hit = TRUE;
            hitSound();
        } else if(bombs.y < 8){
            bombs.health = 0;
            set_sprite_tile(17 + i, 31);
            set_sprite_prop(17 + i, 0);
            explosion = FALSE;
        }
    } else {
        bombs.x = 16*randomize(5) + 48;
        bombs.y = player.y + 120;
        bombs.health = 1;
        if(checkCollision(&bombs, &obstacles[0]) == TRUE){
            bombs.x = 16*randomize(5) + 48;
            bombs.y = player.y + 120;
        }
    }
    moveCharacter(&bombs, bombs.x, bombs.y);

}


void setupBackground(){
    set_bkg_data(37, 13, Knight_tiles);

    // switch to 2nd video memory bank
    VBK_REG = 1;

    // Set background color palette map
    set_bkg_tiles(0, 0, ForestBGWidth, ForestBGHeight, ForestBGPLN1);
    
    // switch to 1st video memory bank
    VBK_REG = 0;

    set_bkg_tiles(0, 0, ForestBGWidth, ForestBGHeight, ForestBGPLN0);
}

void joyHandler(){
    switch (joypad())
    {
    case J_LEFT:
        player.x -= 16;
        break;
    case J_RIGHT:
        player.x += 16;
        break;
    case J_START:
    //Pause game
        game_on = FALSE;
        performDelay(10);
        break;
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

void resetBackground(){
    HIDE_WIN;
    move_bkg(0, 0); //Moves background to its default position
    HIDE_SPRITES;
}

void updateCoinsCounter(){
    if(windowmap[14] == 0x0A){
        swap = (UINT8) windowmap[13] + 1;
        windowmap[13] = (char) swap;
        windowmap[14] = 0x01;
    } else if(windowmap[13] == 0x0A){ //100 coins
        windowmap[13] = 0x01;
        if(player.health < 3){
            player.health++;
        }
    } else {
        swap = (UINT8) windowmap[14] + 1;
        windowmap[14] = (char) swap;
    }
}

void updateHealth(){
    switch (player.health)
    {
    case 3:
        windowmap[16] = 0x31;
        windowmap[17] = 0x31;
        windowmap[18] = 0x31;
        break;
    case 2:
        windowmap[16] = 0x00;
        windowmap[17] = 0x31;
        break;
    case 1:
        windowmap[17] = 0x00;
        windowmap[18] = 0x31;
        break;
    case 0:
        windowmap[18] = 0x00;
        gameOverScreen();
        break;
    default:
        windowmap[16] = 0x31;
        break;
    }
}

void updateScore(){
    if(windowmap[8] == 0x0A){
        windowmap[8] = 0x01;
        swap = (UINT8) windowmap[7] + 1;
        windowmap[7] = (char) swap;
    } else if(windowmap[7] == 0x0A){
        windowmap[7] = 0x01;
        swap = (UINT8) windowmap[6] + 1;
        windowmap[6] = (char) swap;
    }else{
        swap = (UINT8) windowmap[8] + 1;
        windowmap[8] = (char) swap;
    }
}

void hitSound(){
    NR10_REG = 0x25;
    NR11_REG = 0x42;
    NR12_REG = 0x74;
    NR13_REG = 0x00;
    NR14_REG = 0xC3;
}

void coinSound(){
    NR10_REG = 0x32;
    NR11_REG = 0x43;
    NR12_REG = 0x73;
    NR13_REG = 0x01;
    NR14_REG = 0xC3;
}

////Creates a random number between 0 - n
UINT8 randomize(UINT8 n){
    seed = DIV_REG;
    initrand(seed);
    return rand() % n;
}

void gameOverScreen(){
    resetBackground();
    HIDE_WIN;
    gbt_stop();
    set_bkg_data(37, 13, Knight_tiles);
    set_bkg_tiles(0, 0, GameOverWidth, GameOverHeight, GameOver);
    game_on = FALSE;
    //Restart everything to its default values
    hit = FALSE;
    player.health = 3;
    windowmap[6] = 0x01;
    windowmap[7] = 0x01;
    windowmap[8] = 0x01;
    windowmap[13] = 0x01;
    windowmap[14] = 0x01;
    setupPlayer();
    setupCoins();
    setupArrow();
    setupObstacles();
    setupBombs();
    gbt_play(song_Data, 2, 2);
    gbt_loop(1);
}