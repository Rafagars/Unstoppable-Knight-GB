#include "../inc/windowLayer.h"

UINT8 swap = 0;

//Characters for the window layer. UI
unsigned char windowmap[] = {
    0x1D,0x0D,0x19,0x1C,0x0F,0x00,0x01,0x01,0x01,0x01,0x00,0x30,0x22,0x01,0x01,0x00,0x31,0x31,0x31,0x00
};

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