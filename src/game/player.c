#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "animation.c"

typedef struct{
    float x, y;
    float dy;
    short life;
    char *name;
    short action;
    Animation animation;
}Man;

Man initMan(SDL_Renderer *renderer){
    Man man;
    man.dy = 10;
    man.action = 0;
    man.x = 320-40;
    man.y = 240-40;
    man.life = 200;

    man.animation = initAnimation( renderer);
    return man;
}