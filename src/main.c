#include "../inc/header.h"

bool RETRY;
bool WIN;
int main()
{
    bool _START_SCREEN = true;
    bool _SMERT_SCREEN = false;
    RETRY = true;
    WIN = false;
    char **map = get_map();
    srand(time(NULL));
    //Start up SDL and create window
    if(!init()) {
        printf( "Failed to initialize!\n" );
    }
    else {
        //Load media
        if(!loadMedia() ) {
            printf( "Failed to load media!\n" );
        }
        
        else {
            
             //Apply the image
            if(_START_SCREEN){
                main_menu(&_START_SCREEN);
            }
            while(RETRY){
                if(!_START_SCREEN) {
                    Mix_PauseMusic();
                    map = get_map();
                    main_game(map);
                    if(!WIN){
                        _SMERT_SCREEN = true;
                    }
                    
                }
                
                if(_SMERT_SCREEN){
                    main_finish();
                    _SMERT_SCREEN = false;
            }
            }

         
        }
        closeWIN();
    }
    for (int i = 0; i < 22; i++) {
        free(map[i]);
        map[i] = NULL;
    }
    free(map);
}



