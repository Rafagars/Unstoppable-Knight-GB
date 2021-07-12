#include <gb/gb.h>
#include <gb/font.h>
#include "inc/functions.h"

void main(){

    //Choose font
    font_t min_font;

    //Set font
    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    disable_interrupts();

    setupBackground();
    set_win_tiles(0, 0, 20, 1, windowmap);
    move_win(7, 128);
    set_sprite_data(0, 15, knight_sprites);
    setupPlayer();
    setupCoins();
    setupArrow();
    init();

    while(1){
        SHOW_WIN;
        scroll_bkg(0, 4);
        joyHandler();
        if(player.x < 40){
            player.x = 40;
        } else if(player.x > 120){
            player.x = 120;
        }
        positionCoins();
        playerAnimation();
        moveCharacter(&player, player.x, player.y);
        positionArrow();
        if (frame > 2){
            frame = 0;
        }
        wait_vbl_done();
    }
}