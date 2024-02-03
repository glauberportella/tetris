#!/bin/sh

#
# Bibliotecas SDL 2 instalada via Homebrew
# - SDL_Mixer
# - SDL_TTF
#
# Altere as opções -I para corresponder ao local de seus arquivos include da SDL
#
gcc src/core/board.c src/core/piece.c \
    src/game/game.c \
    src/main.c \
    -o bin/tetris \
    -I/usr/src/sdl2/2.28.5/include/SDL2/ \
    -I/usr/src/sdl2_ttf/2.20.2/include/SDL2/ \
    -I/usr/src/sdl2_mixer/2.6.3_1/include/SDL2/ \
    -L/usr/src/sdl2/2.28.5/lib/ \
    -L/usr/src/sdl2_ttf/2.20.2/lib/ \
    -L/usr/src/sdl2_mixer/2.6.3_1/lib/ \
    -lSDL2 \
    -lSDL2_ttf \
    -lSDL2_mixer