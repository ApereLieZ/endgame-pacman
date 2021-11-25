#include "../inc/header.h"

SDL_Window* gWindow;

//The image we will load and show on the screen


void closeWIN()
{
    
    //Deallocate surface
    
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
}
