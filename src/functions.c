#include "../inc/functions.h"

BOOLEAN game_on = TRUE;
BOOLEAN paused = FALSE;

uint16_t seed; //Seed for the randomize function

void interruptLCD(){
    HIDE_WIN;
}

void turnOnSound(){
    NR52_REG = 0x80; //Turn on the sound
    NR51_REG = 0x11; //Enable the sound channels
    NR50_REG = 0x77; //Increase the volume to its max()
}

void turnOffSound(){
    NR52_REG = 0x00;
}

// Initialize all the default variables needed to start the game
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

void performDelay(uint8_t numloops){
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
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
    case J_B:
        //Activates the shield
        shield = TRUE;
        set_sprite_prop(1, 2); //Shield palette
        break;
    case J_START:
        //Pause game
        game_on = FALSE;
        paused = !paused;
        gbt_pause(0);
        turnOffSound();
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

////Returns a random number between 0 - n
uint8_t randomize(uint8_t n){
    seed = DIV_REG;
    initrand(seed);
    return rand() % n;
}

void gameOverScreen(){
    resetBackground();
    SHOW_WIN;
    gbt_stop();
    turnOffSound();
    move_win(7, 0);
    if(_cpu == CGB_TYPE){
        VBK_REG = 1;
        set_win_tiles(0, 0, 20, 11, gameOverPalette); // Set window color palette
        VBK_REG = 0;
    }
    gameOverMap[151] = windowmap[6];
    gameOverMap[152] = windowmap[7];
    gameOverMap[153] = windowmap[8];
    set_win_tiles(0, 0, 20, 11, gameOverMap); // Set the game over message with the score
    game_on = FALSE;
    //Restart everything to its default values
    hit = FALSE;
    explosion= FALSE;
    player.health = 3;
    windowmap[6] = 0x01;
    windowmap[7] = 0x01;
    windowmap[8] = 0x01;
    windowmap[13] = 0x01;
    windowmap[14] = 0x01;
    setupCharacters();
}
