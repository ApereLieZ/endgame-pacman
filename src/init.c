#include "../inc/header.h"

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

int SCREEN_WIDTH = 950;
int SCREEN_HEIGHT = 1100;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {//INIT PNG
        int flags = IMG_INIT_PNG;
        if (!(IMG_Init(flags) & flags)){
            printf("Cant init image PNG: \n");
            success = false;
         }
        TTF_Init();
        //Create window
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        gWindow = SDL_CreateWindow( "PAC MAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH , SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        
    }

    return success;
}
