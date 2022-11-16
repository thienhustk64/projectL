#include<stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include<time.h>

const int WIDTH = 800, HEIGHT = 600, FPS = 20;
SDL_Renderer *renderer;
SDL_Window *window;

typedef struct{
    int x, y;
    short life;
    char *name;
    short action;
    SDL_Texture *walk;
    SDL_Rect walkStatus[6];
}Man;

typedef struct{
    Man man;
    SDL_Texture *map;
    SDL_Renderer *renderer;
}GameState;

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
    int i;
    SDL_Surface *surface = NULL;

    // Load image
    surface = IMG_Load("map/Background.png");
    game->map = SDL_CreateTextureFromSurface( game->renderer, surface);
    SDL_FreeSurface( surface);

    surface = IMG_Load( "character/ichigo2(60x90).png");
    game->man.walk = SDL_CreateTextureFromSurface( game->renderer, surface);
    SDL_FreeSurface( surface);

    game->man.action = 0;
    game->man.x = 320-40;
    game->man.y = 240-40;

    // Detect animation
    for( i = 0; i < 4; i++){
        game->man.walkStatus[i].x = 90*i;
        game->man.walkStatus[i].y = 0;
        game->man.walkStatus[i].w = 90;
        game->man.walkStatus[i].h = 60;
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
        game->man.action = 0;
    }
    if( state[ SDL_SCANCODE_LEFT]){
        game->man.x -= 10;
        game->man.action = 1;
    }
    if( state[ SDL_SCANCODE_UP]){
        game->man.y -= 10;
    }
    if( state[ SDL_SCANCODE_DOWN]){
        game->man.y += 10;
    }

    return done;
}

void doRender( GameState *game, int *frame){
    // clear the screen
    SDL_RenderClear(game->renderer);

    // draw map
    SDL_Rect mapRect = { 0, 0, WIDTH, HEIGHT};
    SDL_RenderCopy( game->renderer, game->map, NULL, &mapRect);

    // Load animation
    SDL_Rect walkRect = { game->man.x, game->man.y, 64, 64};
    if( *frame >= 4){
        *frame = 0;
    }
    if( game->man.action == 0){
        SDL_RenderCopyEx( game->renderer, game->man.walk, &game->man.walkStatus[*frame], &walkRect, 0, NULL, SDL_FLIP_NONE);
    }else if( game->man.action == 1){
        SDL_RenderCopyEx( game->renderer, game->man.walk, &game->man.walkStatus[*frame], &walkRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    *frame = *frame + 1;

    // show after you drawing
    SDL_RenderPresent(game->renderer);
}

void destroy(GameState *game){
    SDL_DestroyTexture( game->man.walk);
    SDL_DestroyTexture( game->map);
    SDL_DestroyWindow( window);
    SDL_DestroyRenderer( renderer);
}

int main(int argc, char *argv[]) {
    GameState gameState;
    Uint32 start;

    initGame( window, renderer);
    gameState.renderer = renderer;

    loadGame( &gameState);
    int done = 0;
    int frame = 0;
    while( !done) {
        start = SDL_GetTicks();
        done = processEvents( &gameState);
        doRender( &gameState, &frame);
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
