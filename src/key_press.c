#include "../inc/header.h"

int key_press(int direction) {
        SDL_Event e; 
        while( SDL_PollEvent( &e ) != 0 ) {
            if(e.type == SDL_QUIT){
                exit(-1);
            }
            if( e.type == SDL_KEYDOWN ) {
                //Select surfaces based on key press
                switch( e.key.keysym.sym ) {
                    case SDLK_UP:
                            return UP;
                            break;

                    case SDLK_DOWN:
                            return DOWN;
                            break;

                    case SDLK_LEFT:
                            return LEFT;
                            break;

                    case SDLK_RIGHT:
                            return RIGHT;
                            break;

                    case ' ':
                            return PAUSE;
                            break;

                    default:
                            return direction;
                            break;
                }
            }
        }
        return direction;

}



