#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_test_images.h>

const int WIDTH = 800, HEIGHT = 600;

typedef struct{
    int x, y;
    short life;
    char *name;
}Man;

typedef struct{
    Man man;
    SDL_Texture *star;
    SDL_Renderer *renderer;
}GameState;

void loadGame( GameState *game){
    SDL_Surface *starSurface = NULL;
    // Load image
    starSurface = SDL_LoadBMP("anime-naruto.bmp");
    if( starSurface == NULL){
        printf("Cant find image\n");
        SDL_Quit();
        exit(1);
    }

    game->star = SDL_CreateTextureFromSurface( game->renderer, starSurface);
    SDL_FreeSurface( starSurface);
}

int processEvents(SDL_Window *window, GameState *game){
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
        game->man.y -= 10;
    }
    if( state[ SDL_SCANCODE_DOWN]){
        game->man.y += 10;
    }

    return done;
}

void doRender( GameState *game){
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
    // clear the screen
    SDL_RenderClear(game->renderer);
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_Rect rect = { game->man.x, game->man.y, 80, 80};
    SDL_RenderFillRect( game->renderer, &rect);

    // draw image
    SDL_Rect imgRect = { 50, 50, 64, 64};
    SDL_RenderCopy( game->renderer, game->star, NULL, &imgRect);

    // show after you drawing
    SDL_RenderPresent(game->renderer);
    
}


int main(int argc, char *argv[]) {

    GameState gameState;
    gameState.man.x = 320-40;
    gameState.man.y = 240-40;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer *renderer;
    SDL_Window *window;

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gameState.renderer = renderer;

    if( NULL == window){
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    loadGame( &gameState);
    int done = 0;
    while( !done) { 
        done = processEvents( window, &gameState);
        doRender( &gameState);
        // Tránh CPU xử lý nhiều
        SDL_Delay(10);
    }

    // Wait a few second before quitting
    SDL_DestroyTexture( gameState.star);
    SDL_DestroyWindow( window);
    SDL_DestroyRenderer( renderer);
    SDL_Quit();
    return EXIT_SUCCESS;
}
