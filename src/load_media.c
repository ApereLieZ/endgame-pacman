#include "../inc/header.h"

SDL_Renderer* renderer;

SDL_Texture* wall_texture = NULL;
SDL_Texture* coin_texture = NULL;

SDL_Texture* pacman_open_right_texture;
SDL_Texture* pacman_close_left_texture;

SDL_Texture* pacman_open_left_texture;
SDL_Texture* pacman_close_right_texture;

SDL_Texture* pacman_open_front_texture = NULL;
SDL_Texture* pacman_close_front_texture = NULL;

SDL_Texture* red_ghost_texture = NULL;
SDL_Texture* pink_ghost_texture = NULL;
SDL_Texture* blue_ghost_texture = NULL;
SDL_Texture* bg_texture = NULL;
SDL_Texture* yellow_ghost_texture = NULL;
SDL_Texture* brain_texture = NULL;
SDL_Texture* pause_texture;

SDL_Texture* pacman_back_texture = NULL;

SDL_Texture* background;
SDL_Texture* background_S;
SDL_Texture* scared_texture = NULL;



SDL_Texture* button_start;
SDL_Texture* button_exit;
SDL_Texture* button_start_pr;
SDL_Texture* button_exit_pr;


SDL_Texture* title;
SDL_Texture* text1;
SDL_Texture* text2;

SDL_Texture* loadTexture(char *path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool loadMedia()
{
    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer) {
        printf("%s\n", SDL_GetError());
    }
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //Loading success flag
    bool success = true;

    //Load splash image
    brain_texture = loadTexture("resource/img/brain.png");
    wall_texture = loadTexture("resource/img/Wall.png" );

    pacman_open_right_texture = loadTexture("resource/img/Pacman_open_right.png");
    pacman_close_right_texture = loadTexture("resource/img/Pacman_close_right.png");

    pacman_open_left_texture = loadTexture("resource/img/Pacman_open_left.png");
    pacman_close_left_texture = loadTexture("resource/img/Pacman_close_left.png");

    coin_texture = loadTexture("resource/img/coin.png");
    blue_ghost_texture = loadTexture("resource/img/blue_ghost.png");
    red_ghost_texture = loadTexture("resource/img/red_ghost.png");
    pink_ghost_texture = loadTexture("resource/img/pink_ghost.png");
    yellow_ghost_texture = loadTexture("resource/img/yellow_ghost.png");
    button_start = loadTexture("resource/img/button_start.png");
    button_exit = loadTexture("resource/img/button_exit.png");
    button_start_pr = loadTexture("resource/img/button_start_pressed.png");
    button_exit_pr = loadTexture("resource/img/button_exit_pressed.png");
    background = loadTexture("resource/img/background.png");
    background_S = loadTexture("resource/img/smile.bmp");
    text1 = loadTexture("resource/img/wake_up.bmp");
    text2 = loadTexture("resource/img/segm.bmp");
    title = loadTexture("resource/img/PACMAN.png");
    scared_texture = loadTexture("resource/img/white_ghost.png");
    pacman_back_texture = loadTexture("resource/img/Pacman_back.png");

    button_retry = loadTexture("resource/img/RETRY.png");
    button_finish = loadTexture("resource/img/finish.png");

    pause_texture = loadTexture("resource/img/pause.png");

    pacman_open_front_texture = loadTexture("resource/img/Pacman_open_front.png");
    pacman_close_front_texture = loadTexture("resource/img/Pacman_close_front.png");

    heart = loadTexture("resource/img/Heart.png");

    intro = Mix_LoadMUS("resource/music/pacman_beginning.wav");
    eat_wav = Mix_LoadMUS("resource/music/pacman_chomp.wav");
    death_wav = Mix_LoadMUS("resource/music/pacman_death.wav");
    win_wav = Mix_LoadMUS("resource/music/win.wav");
    
    

    if( wall_texture == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/wall.png", SDL_GetError() );
        success = false;
    }
    if( background == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/wall.png", SDL_GetError() );
        success = false;
    }
    if( coin_texture == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }


    
    return success;
}
