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
    src/ui/widget.c \
    src/main.c \
    -o bin/tetris \
    -I/opt/homebrew/Cellar/sdl2/2.28.5/include/SDL2/ \
    -I/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include/SDL2/ \
    -I/opt/homebrew/Cellar/sdl2_mixer/2.6.3_1/include/SDL2/ \
    -L/opt/homebrew/Cellar/sdl2/2.28.5/lib/ \
    -L/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib/ \
    -L/opt/homebrew/Cellar/sdl2_mixer/2.6.3_1/lib/ \
    -lSDL2 \
    -lSDL2_ttf \
    -lSDL2_mixer