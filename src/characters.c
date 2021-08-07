#include "../inc/characters.h"

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

uint8_t i;
const uint8_t spritesize = 8;
uint8_t frame;
uint8_t spriteID;
uint8_t timer = 5;

BOOLEAN shield = FALSE;
BOOLEAN hit = FALSE;
BOOLEAN explosion = FALSE;

UBYTE checkCollision(GameCharacter* one, GameCharacter* two){
    return(one->x >= two->x && one->x <= two->x + two->w) && (one->y >= two->y && one->y <= two->y + two->h) || (two->x >= one->x && two->x <= one->x + one->w) && (two->y >= one->y && two->y <= one->y + one->h);
}

// Gives the player a smaller hitbox
UBYTE checkPlayerCollision(GameCharacter* character){
    return(player.x  + 2 >= character->x && player.x + 2 <= character->x + character->w) && (player.y + 2 >= character->y && player.y + 2 <= character->y + character->h) || (character->x >= player.x + 2 && character->x <= player.x + player.w - 2) && (character->y >= player.y + 2 && character->y <= player.y + player.h - 2);
}

//Avoid certain obstacles on top of another
void checkObstacles(GameCharacter* one, GameCharacter* two){
    if(one->x == two->x && one->y - two->y < 16){
        if(one->x > 64 && one->x < 80){
            two->x = one->x + 16;    
        } else {
            two->x = one->x - 16;    
        }
    }
}

void moveCharacter(GameCharacter* character, uint8_t x, uint8_t y){
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

void animations(){
    uint8_t n = 3*frame + frame;

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
    if(!explosion){
        set_sprite_tile(bombs.spriteID[0], 32 + n);
        set_sprite_prop(bombs.spriteID[0], 0);
        set_sprite_tile(bombs.spriteID[2], 33 + n);
        set_sprite_prop(bombs.spriteID[2], 0);    
        set_sprite_tile(bombs.spriteID[1],  34 + n);
        set_sprite_prop(bombs.spriteID[1], 0);    
        set_sprite_tile(bombs.spriteID[3], 35 + n); 
        set_sprite_prop(bombs.spriteID[3], 0);    
    } else {
        //Explosion animation
        set_sprite_tile(bombs.spriteID[0], 48 + n);
        set_sprite_prop(bombs.spriteID[0], 5);
        set_sprite_tile(bombs.spriteID[2], 49 + n);
        set_sprite_prop(bombs.spriteID[2], 5);    
        set_sprite_tile(bombs.spriteID[1], 50 + n);
        set_sprite_prop(bombs.spriteID[1], 5);    
        set_sprite_tile(bombs.spriteID[3], 51 + n); 
        set_sprite_prop(bombs.spriteID[3], 5); 
    }
    
    if(obstacles[0].y < 8){
        hit = FALSE;
    }

    if(hit){
        //Hit effect
        set_sprite_tile(0, 64);
        set_sprite_tile(2, 64);
        set_sprite_tile(1, 64);
        set_sprite_tile(3, 64);
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
        if(shield  && timer > 1){
            set_sprite_tile(1, 31); //Shield sprite
            timer--;
        } else {
            set_sprite_tile(1, 1 + n); //Default sprites
            set_sprite_prop(1, 0);
            timer = 5;
            shield = FALSE;
        }
        set_sprite_tile(3, 3 + n);
        performDelay(4);
    }
    frame++;
}

void setupCoins(){
    GameCharacter* coin = coins;
    for(i = 0; i < 4; i++){
        coin->x = 16*randomize(5) + 48;
        coin->y = player.y + 120 + 16*i;
        coin->h = 8;
        coin->w = 8;
        coin->health = 1;

        spriteID = 4 + i;
        //load coin's sprite
        set_sprite_tile(spriteID, 12);
        set_sprite_prop(spriteID, 1);
        coin->spriteID[0] = spriteID;

        move_sprite(coin->spriteID[0], coin->x, coin->y);
        coin++;
        GameCharacter* coin = &coins[i];
    }
}

void positionCoins(){
    GameCharacter* coin = coins;
    for(i = 0; i < 4; i++){
        if(coin->health > 0){
            coin->y -= 4;
            if(checkCollision(&player, coin)){
                coin->health = 0;
                coinSound();
                updateCoinsCounter();
                updateScore();
            } else if(coin->y < 8){
                coin->health = 0;
            }
        } else {
            coin->x = 16*randomize(5) + 48;
            coin->y = player.y + 120 + 16*i;  
            coin->health = 1;
        }
        move_sprite(coin->spriteID[0], coin->x, coin->y);
        coin++;
        GameCharacter* coin = &coins[i];
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
        if(checkPlayerCollision(&arrow) && !hit){
            arrow.health = 0;
            if(!shield){ 
                player.health--;
                hit = TRUE;
                hitSound();
            }
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
    GameCharacter* obstacle = obstacles;
    spriteID += 1;
    for(i = 0; i < 2; i++){
        obstacle->x = 16*randomize(4) + 64;
        obstacle->y = player.y + 120;
        obstacle->w = 16;
        obstacle->h = 16;
        obstacle->health = 1;

        uint8_t n = (4*i + i);
        //load obstacles's sprites
        set_sprite_tile(spriteID + n, 15 + n);
        set_sprite_prop(spriteID + n, 3 + i);
        obstacle->spriteID[0] = spriteID + n;
        set_sprite_tile(spriteID + n + 1 , 16 + n);
        set_sprite_prop(spriteID + n + 1, 3 + i);
        obstacle->spriteID[2] = spriteID + n + 1;
        set_sprite_tile(spriteID + n + 2, 17 + n);
        set_sprite_prop(spriteID + n + 2, 3 + i);
        obstacle->spriteID[1] = spriteID + n + 2;
        set_sprite_tile(spriteID + n + 3, 18 + n);
        set_sprite_prop(spriteID + n + 3, 3 + i);
        obstacle->spriteID[3] = spriteID + n + 3;

        moveCharacter(obstacle, obstacle->x, obstacle->y);
        obstacle++;
        GameCharacter* obstacle = &obstacles[i];
    }   
}

void positionObstacles(){
    GameCharacter* obstacle = obstacles;
    for(i = 0; i < 2; i++){
        if(obstacle->health > 0){
            obstacle->y -= 4 + 2*i;
            if(obstacle->y < 4){
                obstacle->health = 0;
            }else if(checkPlayerCollision(obstacle) && !hit){
                player.health--;
                hit = TRUE;
                hitSound();
            }
        } else {
            obstacle->x = 16*randomize(4) + 64;
            obstacle->y = player.y + 120;
            obstacle->health = 1;
            checkObstacles(&obstacles[0], &obstacles[1]); // The orc(obstacle 1) should avoid the pit too
        }
        moveCharacter(obstacle, obstacle->x, obstacle->y);
        obstacle++;
        GameCharacter* obstacle = &obstacles[i];
    }
}

void setupBombs(){ 
    bombs.x = 16*randomize(5) + 48;
    bombs.y = player.y + 120;
    bombs.h = 16;
    bombs.w = 16;
    bombs.health = 1;

    set_sprite_tile(18 , 32);
    set_sprite_prop(18, 3);
    bombs.spriteID[0] = 18;
    set_sprite_tile(19, 33);
    set_sprite_prop(19, 3);
    bombs.spriteID[2] = 19;
    set_sprite_tile(20, 33);
    set_sprite_prop(20, 3);
    bombs.spriteID[1] = 20;
    set_sprite_tile(21, 34);
    set_sprite_prop(21, 3);
    bombs.spriteID[3] = 21;

    checkObstacles(&obstacles[0], &bombs); // We don't want bombs over the pits 

    moveCharacter(&bombs, bombs.x, bombs.y); 
}

void positionBombs(){
    if(bombs.health > 0){
        bombs.y -= 4;
        if(checkPlayerCollision(&bombs)  && !hit){
            explosion = TRUE;
            if(!shield){
                player.health--;
                hit = TRUE;
                hitSound();
            }
        } else if(bombs.y < 2){
            bombs.health = 0;
            explosion = FALSE;
        }
    } else {
        bombs.x = 16*randomize(5) + 48;
        bombs.y = player.y + 120;
        bombs.health = 1;
        
        checkObstacles(&obstacles[0], &bombs); // We don't want bombs over the pits 
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

void setupCharacters(){
    // Set up the player's character and all the games obstacles
    setupPlayer();
    setupCoins();
    setupArrow();
    setupObstacles();
    setupBombs();
}