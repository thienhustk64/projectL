#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct{
    float x, y;
    float dy;
    short life;
    char *name;
    short action;
    SDL_Texture *idle[6];
}Man;

Man initMan(SDL_Renderer *renderer){
    Man man;
    SDL_Surface *surface = NULL;
    man.dy = 10;
    man.action = 0;
    man.x = 320-40;
    man.y = 240-40;
    man.life = 200;

    surface = IMG_Load( "data/ryu/idle00.png");
    man.idle[0] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle01.png");
    man.idle[1] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle02.png");
    man.idle[2] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle03.png");
    man.idle[3] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle04.png");
    man.idle[4] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle05.png");
    man.idle[5] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);
    return man;
}