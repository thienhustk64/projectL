#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "player.c"
#include "collision.c"

typedef struct{
    Man man;
    Man man2;
    Ledge mapCollision;
    SDL_Texture *map;
    SDL_Renderer *renderer;
    int frame;
    int isCombo;
}GameState;

const int WIDTH = 800, HEIGHT = 600, FPS = 15;
SDL_Renderer *renderer;
SDL_Window *window;

void initGame(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Project L", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(window == NULL){
        printf("Window could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        printf("Cant create render! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) &imgFlags)){
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }
    if(TTF_Init() == -1){
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }
}

void loadGame( GameState *game){
    SDL_Surface *surface = NULL;

    // Load image
    surface = IMG_Load("data/background.png");
    game->map = SDL_CreateTextureFromSurface( game->renderer, surface);
    SDL_FreeSurface( surface);

    //Load man
    game->man = initMan( game->renderer);
    game->man2 = initMan( game->renderer);

    game->frame = 0;
    game->isCombo = 0;
    game->mapCollision.x = 0;
    game->mapCollision.y = 0;
    game->mapCollision.h = 500;
    game->mapCollision.w = 800;
}

void collisionDetect(GameState *game){
    float mw = 128, mh = 128;
    float mx = game->man.x, my = game->man.y;
    float bx = game->mapCollision.x, by = game->mapCollision.y, bw = game->mapCollision.w, bh = game->mapCollision.h;

    if( mx < bx){
        game->man.x = bx;
    }
    if( mx + mw > bx + bw){
        game->man.x = bw - mw;
    }
    if( my < by){
        game->man.y = by;
    }
    if( my + mh > by + bh){
        game->man.y = bh - mh;
    }

}

int processEvents(GameState *game){
    SDL_Event windowEvent;
    int done = 0;
    while( SDL_PollEvent( &windowEvent)){
        switch( windowEvent.type){
            case SDL_WINDOWEVENT_CLOSE:{
                if( window){
                    SDL_DestroyWindow( window);
                    done = 1;
                    window = NULL;
                }
            }
            break;
            case SDL_KEYDOWN:{
                switch ( windowEvent.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = 1;
                    break;
                default:
                    break;
                }
            }
            break;
            case SDL_QUIT:
                done = 1;
                break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if( state[ SDL_SCANCODE_RIGHT]){
        game->man.x += 10;
    }
    if( state[ SDL_SCANCODE_LEFT]){
        game->man.x -= 10;
    }
    if( state[ SDL_SCANCODE_UP]){
        game->man.y -= 20;
    }
    if( state[ SDL_SCANCODE_J]){
        if( game->man.action == 1){
            game->isCombo = 1;
        }
        if( game->man.action == 0){
            game->man.action = 1;
        }
    }
    // if( state[ SDL_SCANCODE_DOWN]){
    //     game->man.y += 10;
    // }

    return done;
}

void processGame( GameState *game){
    game->man.y += game->man.dy;
}

void doRender( GameState *game){
    // clear the screen
    SDL_RenderClear(game->renderer);

    // draw map
    SDL_Rect mapRect = { 0, 0, WIDTH, HEIGHT};
    SDL_RenderCopy( game->renderer, game->map, NULL, &mapRect);

    // Load animation
    SDL_Rect walkRect = { game->man.x, game->man.y, game->man.animation.size[game->man.action].w, game->man.animation.size[game->man.action].h};
    if( game->frame >= game->man.animation.len[ game->man.action]){
        game->frame = 0;
        if( game->isCombo == 1){
            game->man.action = 2;
            game->isCombo = 0;
        }else{
            game->man.action = 0;
        }
    }
    SDL_RenderCopyEx( game->renderer, game->man.animation.animations[game->man.action][game->frame], NULL, &walkRect, 0, NULL, SDL_FLIP_NONE);
    // SDL_RenderCopyEx( game->renderer, game->man.animation.animations[game->man.action][game->frame], NULL, &walkRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    game->frame = game->frame + 1;

    // show after you drawing
    SDL_RenderPresent(game->renderer);
}

void destroy(GameState *game){
    SDL_DestroyTexture( game->map);
    SDL_DestroyWindow( window);
    SDL_DestroyRenderer( renderer);
    //destroy animation texture
}

int main(int argc, char *argv[]) {
    GameState gameState;
    Uint32 start;

    initGame( window, renderer);
    gameState.renderer = renderer;

    loadGame( &gameState);
    int done = 0;
    while( !done) {
        start = SDL_GetTicks();
        done = processEvents( &gameState);
        processGame( &gameState);
        collisionDetect( &gameState);
        doRender( &gameState);
        // Tránh CPU xử lý nhiều
        if(1000/FPS > SDL_GetTicks()-start) {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
    }
    
    // Wait a few second before quitting
    destroy( &gameState);
    SDL_Quit();
    return EXIT_SUCCESS;
}
