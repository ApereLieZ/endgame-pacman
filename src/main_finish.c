#include "../inc/header.h"

SDL_Texture* button_retry;
SDL_Texture* button_finish;
bool RETRY;

void main_finish(){
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
    SDL_Rect end_cord = {340, 400, 300, 80};
    SDL_Rect retc = {235, 500, 260, 140};
    SDL_Rect finc = {550, 520, 100, 100};
    SDL_Color color = {0, 255, 29, 255};
    SDL_Texture *end_game = renderText("GAME OVER", "resource/ttf/mat.TTF", color, 62, renderer);
    bool quit = false;
    SDL_Event e;                                            
    while (!quit) {                                         
        while (SDL_PollEvent(&e)) {                         
            if (e.type == SDL_QUIT) {                       
                quit = true;                                
            }
            else{
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, end_game, NULL, &end_cord);
                SDL_RenderCopy(renderer, button_retry, NULL, &retc);
                SDL_RenderCopy(renderer, button_finish, NULL, &finc);
                SDL_RenderPresent(renderer);
                mouse_event(&e);
                if(Mouse_X > 552 && Mouse_X < 647 && Mouse_Y > 525 && Mouse_Y < 618 && e.type == SDL_MOUSEBUTTONDOWN){
                    RETRY = false;
                    quit = true;
                    break;
                }
                if(Mouse_X > 326 && Mouse_X < 420 && Mouse_Y > 525 && Mouse_Y < 618 && e.type == SDL_MOUSEBUTTONDOWN){
                    quit = true;
                    break;
                }
            }

            
        }
    }
}

