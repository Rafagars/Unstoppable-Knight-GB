#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/font.h>
#include "inc/functions.h"
#include "src/titlescreen_data.c"
#include "src/titlescreen_map.c"

void main(){

    //Choose font
    font_t min_font;

    //Set up the background's palettes for the Title Screen
    set_bkg_palette(0, 5, &spritePalette[0]);
    
    //Set up the titlescreen
    set_bkg_data(0, 149, titlescreen_data);
    set_bkg_tiles(0, 0, 20, 18, titlescreen_map);

    SHOW_BKG;
    DISPLAY_ON;

    //The game won't begin until the start button is pressed
    waitpad(J_START | J_A);

    fadeOut(); //Fade out effect

    //Set up the background's palettes 
    set_bkg_palette(0, 4, &backgroundPalette[0]);

    HIDE_BKG;
    DISPLAY_OFF;

    disable_interrupts();

    //Set font
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    //Start background music
    gbt_play(song_Data, 2, 1);
    gbt_loop(1);

    if(_cpu == CGB_TYPE){
        VBK_REG = 1;
        set_win_tiles(0, 0, 20, 1, windowpalette); // Set window color palette
        VBK_REG = 0;
    }
    
    set_win_tiles(0, 0, 20, 1, windowmap); // Set the tiles for the window layer
    move_win(7, 132); //Bottom of the screen
    set_sprite_data(0, 64, knight_sprites);
    set_sprite_palette(0, 6, &spritePalette[0]); //Load sprite's color palettes
    setupBackground(); // Set up the Background
    setupCharacters(); // Set up The player's and obstacle's sprites
    init(); // Initialize all the default variables needed to start the game

    while(1){
        if(game_on){
            scroll_bkg(0, 4); // Vertical Scroll
            joyHandler(); //Instructions for the controls
            // Player's movement limits
            if(player.x < 48){
                player.x = 48;
            } else if(player.x > 112){
                player.x = 112;
            }
            positionCoins();
            animations();
            moveCharacter(&player, player.x, player.y);
            positionArrow();
            positionObstacles();
            positionBombs();
            updateHealth();
            set_win_tiles(0, 0, 20, 1, windowmap);  //Updates the whole window layer
            if (frame > 2){ //Restart animation
                frame = 0;
            }
            gbt_update(); // This will change to ROM bank 1.
        } else {
            if(joypad() & J_START){
                //Restart game
                game_on = TRUE;
                if(paused ){
                    gbt_pause(1);
                    turnOnSound();
                    paused = FALSE;
                } else {
                    setupBackground();
                    //Restart background music
                    gbt_play(song_Data, 2, 1);
                    gbt_loop(1);
                    init();
                }
                performDelay(10);
            }
        }
        wait_vbl_done();
    }
}