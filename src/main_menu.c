#include "../inc/header.h"

SDL_Window* gWindow ;
    
//The surface contained by the window
SDL_Texture* background;
SDL_Texture* background_S;

Mix_Music *intro;
//The image we will load and show on the screen


SDL_Texture* button_start;
SDL_Texture* button_exit;
SDL_Texture* button_start_pr;
SDL_Texture* button_exit_pr;

SDL_Texture* title;
SDL_Texture* text1;
SDL_Texture* text2;

SDL_Renderer* renderer;

int Mouse_X, Mouse_Y;

void mouse_event(SDL_Event *event){
    if(event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP){
        SDL_GetMouseState(&Mouse_X, &Mouse_Y);
    }
}

void main_menu(bool *_START_SCREEN) {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255);
    SDL_Rect butS_cord = {60, 950, 200, 75};
    SDL_Rect butE_cord = {680, 950, 200, 75};
    SDL_Rect butSP_cord = {60, 950, 200, 75};
    SDL_Rect butEP_cord = {680, 950, 200, 75};
    SDL_Rect back_cord = {349, 302, 230, 275};
    SDL_Rect title_cord = {80, 100, 800, 200};
    SDL_Rect text1_cord = {75, 300, 250, 70}; 
    SDL_Rect text2_cord = {583, 305, 300, 70};
    SDL_Rect morpheus_cord = {0, 300, 930, 800};
    char score[3]; char bs [17] = "BEST SCORE   ";
    SDL_itoa(read_score(), score, 10);
    SDL_Rect best_score_cord = {360, 960, 200, 60};
    SDL_Color color = {0, 255, 29, 255};
    SDL_Texture *best_score = renderText(strcat(bs , score), "resource/ttf/ARCADECLASSIC.TTF", color, 62, renderer);
    
    Mix_PlayMusic(intro, -1);
    bool quit = false;
    SDL_Event e;                                            
    while (!quit) {                                         
        while (SDL_PollEvent(&e)) {                         
            if (e.type == SDL_QUIT) {                       
                quit = true;                                
            }
            else{
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, background, NULL, &morpheus_cord);
                SDL_RenderCopy(renderer, title, NULL, &title_cord);
                SDL_RenderCopy(renderer, button_start, NULL, &butS_cord);
                SDL_RenderCopy(renderer, button_exit, NULL, &butE_cord);
                SDL_RenderCopy(renderer, text1, NULL, &text1_cord);
                SDL_RenderCopy(renderer, text2, NULL, &text2_cord);
                SDL_RenderCopy(renderer, best_score, NULL, &best_score_cord);
                mouse_event(&e);
                
                if(Mouse_X > 64 && Mouse_X < 256 && Mouse_Y > 953 && Mouse_Y < 1024){ //start button
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        butSP_cord.w = 150;
                        butSP_cord.h = 50;
                        butSP_cord.x = 90;
                        butSP_cord.y = 950;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, background, NULL, &morpheus_cord);
                        SDL_RenderCopy(renderer, button_exit, NULL, &butE_cord);
                        SDL_RenderCopy(renderer, title, NULL, &title_cord);
                        SDL_RenderCopy(renderer, text1, NULL, &text1_cord);
                        SDL_RenderCopy(renderer, text2, NULL, &text2_cord);
                        SDL_RenderCopy(renderer, best_score, NULL, &best_score_cord);
                    }
                    if(e.type == SDL_MOUSEBUTTONUP){
                        *_START_SCREEN = false;
                        quit = true;
                        SDL_RenderClear(renderer);
                        break;
                        
                    }
                    SDL_RenderCopy(renderer, background_S, NULL, &back_cord);
                    SDL_RenderCopy(renderer, button_start_pr, NULL, &butSP_cord);
                }
                else{
                    SDL_RenderCopy(renderer, background, NULL, &morpheus_cord);
                    SDL_RenderCopy(renderer, button_start, NULL, &butS_cord);
                    SDL_RenderCopy(renderer, best_score, NULL, &best_score_cord);
                }
                if(Mouse_X > 684 && Mouse_X < 877 && Mouse_Y > 953 && Mouse_Y < 1024){ //exit button
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        butEP_cord.w = 150;
                        butEP_cord.h = 50;
                        butEP_cord.x = 710;
                        butEP_cord.y = 950;
                        exit(1);
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, background, NULL, &morpheus_cord);
                        SDL_RenderCopy(renderer, button_start, NULL, &butS_cord);
                        SDL_RenderCopy(renderer, title, NULL, &title_cord);
                        SDL_RenderCopy(renderer, text1, NULL, &text1_cord);
                        SDL_RenderCopy(renderer, text2, NULL, &text2_cord);
                        SDL_RenderCopy(renderer, best_score, NULL, &best_score_cord);
                    }
                    SDL_RenderCopy(renderer, button_exit_pr, NULL, &butEP_cord);
                    if(e.type == SDL_MOUSEBUTTONUP)
                        
                        quit = true;
                }
                else{
                    SDL_RenderCopy(renderer, button_exit, NULL, &butE_cord);

                }
                SDL_RenderPresent(renderer);

            }                                               
        }                                                          
    } 
}
