#define _HEADER_
#ifdef _HEADER_

#define BLACK_COLOR 0,0,0
#define WHITE_COLOR 255,255,255
#define RED_COLOR 255,0,0
#define BLUE_COLOR 0,0,255
#define GREEN_COLOR 0,250,0
#define ROWS 22
#define COLS 19
#define RED_POS_X 7
#define RED_POS_Y 9
#define PINK_POS_X 9
#define PINK_POS_Y 9
#define BLUE_POS_X 9
#define BLUE_POS_Y 8
#define YELLOW_POS_X 9
#define YELLOW_POS_Y 10


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

extern SDL_Window* gWindow;
    
//The surface contained by the window
extern Mix_Music *intro;
extern Mix_Music *eat_wav;
extern Mix_Music *death_wav;
extern Mix_Music *win_wav;
//The image we will load and show on the screen


extern SDL_Texture* button_start;
extern SDL_Texture* button_exit;
extern SDL_Texture* button_start_pr;
extern SDL_Texture* button_exit_pr;

extern SDL_Texture* title;
extern SDL_Texture* text1;
extern SDL_Texture* text2;
extern SDL_Texture* pause_texture;

extern SDL_Renderer* renderer;

enum direction {PAUSE, RIGHT, LEFT, UP, DOWN};

extern SDL_Texture* pause_texture;
extern SDL_Texture* wall_texture;
extern SDL_Texture* coin_texture;
extern SDL_Texture* red_ghost_texture;
extern SDL_Texture* pink_ghost_texture;
extern SDL_Texture* blue_ghost_texture;
extern SDL_Texture* yellow_ghost_texture;
extern SDL_Texture* brain_texture;
extern SDL_Texture* button_retry;
extern SDL_Texture* button_finish;
extern SDL_Texture* heart;

extern SDL_Texture* scared_texture;

extern SDL_Texture* pacman_open_left_texture;
extern SDL_Texture* pacman_close_left_texture;

extern SDL_Texture* pacman_open_right_texture;
extern SDL_Texture* pacman_close_right_texture;

extern SDL_Texture* pacman_open_front_texture;
extern SDL_Texture* pacman_close_front_texture;

extern SDL_Texture* pacman_back_texture;

extern bool RETRY;
extern bool WIN;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int Mouse_X, Mouse_Y;

char **read_map(const char *file);
int read_score();
void write_score(int score);
int key_press();


typedef struct t_point {
    int x;
    int y;
}               point;

struct node {
    point pt;
    int dist;
};

struct queue {
    struct node *nodes;
    int head;
    int tail;
};

typedef struct t_pacman {
    point coord;
    int direction;
    int hp;
    bool is_angry;
    int score;

}               Pacman;

typedef struct t_red_ghost {
    point coord;
    point dst;
    int direction;
}               RedGhost;

typedef struct t_pink_ghost {
    point coord;
    point dst;
    int direction;
}               PinkGhost;

typedef struct t_blue_ghost {
    point coord;
    point dst;
    int direction;
}               BlueGhost;

typedef struct t_yellow_ghost {
    point coord;
    point dst;
    int direction;
}               YellowGhost;

void move_pacman (char **map, Pacman *pacman);

bool check_win (char **map);
char **read_map(const char *file);
char** get_map();
void main_menu(bool *_START_SCREEN);
void main_game(char **map);
bool init();
bool loadMedia();
void closeWIN();
void main_finish();
void mouse_event(SDL_Event *event);
SDL_Texture* renderText(const char* message, const char *fontFile,
        SDL_Color color, int fontSize, SDL_Renderer *renderer);
#endif
