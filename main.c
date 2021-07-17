#include <gb/gb.h>
#include <gb/cgb.h>
#include <gb/font.h>
#include "inc/functions.h"
#include "src/titlescreen_data.c"
#include "src/titlescreen_map.c"

void main(){

    //Choose font
    font_t min_font;

    set_bkg_palette(0, 4, &backgroundPalette[0]);
    
    //Set up the titlescreen
    set_bkg_data(0, 149, titlescreen_data);
    set_bkg_tiles(0, 0, 20, 18, titlescreen_map);

    SHOW_BKG;
    DISPLAY_ON;

    //The game won't begin until the start button is pressed
    waitpad(J_START | J_A);

    fadeOut();

    //fadeIn();

    HIDE_BKG;
    DISPLAY_OFF;

    disable_interrupts();

    //Set font
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    setupBackground();
    set_win_tiles(0, 0, 20, 1, windowmap);
    move_win(7, 136);
    set_sprite_data(0, 32, knight_sprites);
    set_sprite_palette(0, 5, &spritePalette[0]);
    setupPlayer();
    setupCoins();
    setupArrow();
    setupObstacles();
    init();

    while(1){
        SHOW_WIN;
        if(game_on == TRUE){
            scroll_bkg(0, 4);
            joyHandler();
            if(player.x < 48){
                player.x = 48;
            } else if(player.x > 112){
                player.x = 112;
            }
            positionCoins();
            playerAnimation();
            moveCharacter(&player, player.x, player.y);
            positionArrow();
            positionObstacles();
            updateHealth();
            //Updates the whole window layer
            set_win_tiles(0, 0, 20, 1, windowmap);
            if (frame > 2){
                frame = 0;
            }
        } else {
            if(joypad() & J_START){
                //Restart game
                game_on = TRUE;
                setupBackground();
                SHOW_SPRITES;
                performDelay(10);
            }
        }
        wait_vbl_done();
    }
}