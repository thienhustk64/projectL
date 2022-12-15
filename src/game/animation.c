#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct{
    int w, h;
}Size;

typedef struct{
    SDL_Texture *animations[6][6];
    int len[6];
    Size size[6];
}Animation;

Animation initAnimation( SDL_Renderer *renderer){
    Animation animation;
    SDL_Surface *surface = NULL;
    surface = IMG_Load( "data/ryu/idle00.png");
    animation.animations[0][0] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle01.png");
    animation.animations[0][1] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle02.png");
    animation.animations[0][2] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle03.png");
    animation.animations[0][3] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle04.png");
    animation.animations[0][4] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/idle05.png");
    animation.animations[0][5] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);
    
    // Punch 1
    surface = IMG_Load( "data/ryu/1punch00.png");
    animation.animations[1][0] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/1punch01.png");
    animation.animations[1][1] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/1punch02.png");
    animation.animations[1][2] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/1punch03.png");
    animation.animations[1][3] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    // Punch 2
    surface = IMG_Load( "data/ryu/2punch00.png");
    animation.animations[2][0] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/2punch01.png");
    animation.animations[2][1] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/2punch02.png");
    animation.animations[2][2] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/2punch03.png");
    animation.animations[2][3] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/2punch04.png");
    animation.animations[2][4] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "data/ryu/2punch05.png");
    animation.animations[2][5] = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_FreeSurface( surface);


    animation.len[0] = 6;
    animation.len[1] = 4;
    animation.len[2] = 6;

    animation.size[0].w = 64;
    animation.size[0].h = 128;
    animation.size[1].w = 128;
    animation.size[1].h = 128;
    animation.size[2].w = 128;
    animation.size[2].h = 128;
    return animation;
}