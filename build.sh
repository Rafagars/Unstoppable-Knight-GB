/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o src/knight_sprites.o src/knight_sprites.c 
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o src/knight_tiles.o src/knight_tiles.c 
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o src/gameCharacter.o src/gameCharacter.c 
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o src/ForestBG.o src/ForestBG.c 
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o src/GameOverBackground.o src/GameOverBackground.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o src/functions.o src/functions.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o audio/output.o audio/output.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o audio/gbt_player.o audio/gbt_player.s
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o audio/gbt_player_bank1.o audio/gbt_player_bank1.s  
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -Wm-yn"KNIGHT" -Wm-yc -o knight.gb src/knight_sprites.o main.o src/functions.o src/knight_tiles.o src/gameCharacter.o src/ForestBG.o src/GameOverBackground.o audio/output.o audio/gbt_player.o audio/gbt_player_bank1.o

rm *.o *.lst *.asm *.sym

cd src

rm *.o *.lst *.asm *.sym

cd ../

cd audio

rm *.o *.lst *.asm *.sym

cd ../
