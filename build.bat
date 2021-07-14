C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o src\knight_sprites.o src\knight_sprites.c 
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o src\knight_tiles.o src\knight_tiles.c 
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o src\gameCharacter.o src\gameCharacter.c 
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o src\ForestBG.o src\ForestBG.c 
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o src\GameOverBackground.o src\GameOverBackground.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o src\functions.o src\functions.c 
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o main.o main.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yc -o knight.gb src/knight_sprites.o main.o src/functions.o src/knight_tiles.o src/gameCharacter.o src/ForestBG.o src/GameOverBackground.o

del *.o *.lst *.asm *.sym *.cdb *.ihx *.map *.noi

ls src

del *.o *.lst *.asm *.sym