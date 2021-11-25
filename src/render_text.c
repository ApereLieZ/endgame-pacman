#include "../inc/header.h"

SDL_Texture* renderText(const char* message, const char *fontFile,
        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
        //Открываем шрифт
        TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
        if (font == NULL){
                printf("Error open font\n");
                return NULL;
        }       
        //Сначала нужно отобразить на поверхность с помощью TTF_RenderText,
        //затем загрузить поверхность в текстуру
        SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
        if (surf == NULL){
                TTF_CloseFont(font);
                printf("Error open surface text\n");
                return NULL;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == NULL){
                printf("Error make texture\n");
        }
        //Очистка поверхности и шрифта
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        return texture;
}
