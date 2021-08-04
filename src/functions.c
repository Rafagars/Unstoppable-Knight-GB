#include "../inc/functions.h"

BOOLEAN game_on = TRUE;

UINT16 seed; //Seed for the randomize function

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

void performDelay(UINT8 numloops){
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
UINT8 randomize(UINT8 n){
    seed = DIV_REG;
    initrand(seed);
    return rand() % n;
}

void gameOverScreen(){
    resetBackground();
    interruptLCD(); //Hide Window layer
    gbt_stop();
    turnOffSound();
    set_bkg_data(37, 13, Knight_tiles);
    set_bkg_tiles(0, 0, GameOverWidth, GameOverHeight, GameOver);
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
    gbt_play(song_Data, 2, 2);
    gbt_loop(1);
}