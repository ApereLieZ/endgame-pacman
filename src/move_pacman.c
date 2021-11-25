#include "../inc/header.h"

Mix_Music *eat_wav;

void move_pacman (char **map, Pacman *pacman) {      
    
    if (pacman->direction == RIGHT) {
        if (pacman->coord.y < 18 && map[pacman->coord.x][pacman->coord.y + 1] != '#')
            (pacman->coord.y)++;
        else if (pacman->coord.y == 18 && map[pacman->coord.x][0] != '#')
            pacman->coord.y = 0;
        else return;
    
            
            if (map[pacman->coord.x][pacman->coord.y] == ' ') {
                pacman->score++;
                Mix_PlayMusic(eat_wav,1);
            }
            if (map[pacman->coord.x][pacman->coord.y] == 'O') {
                pacman->is_angry = true;
            }
            if (pacman->coord.y != 0) {
                map[pacman->coord.x][pacman->coord.y] = map[pacman->coord.x][pacman->coord.y - 1];
                map[pacman->coord.x][pacman->coord.y - 1] = '.';

            }
            else {
                map[pacman->coord.x][pacman->coord.y] = map[pacman->coord.x][18];
                map[pacman->coord.x][18] = '.';
            }
    }
    else if (pacman->direction == LEFT) {
        
        if (pacman->coord.y > 0 && map[pacman->coord.x][pacman->coord.y - 1] != '#')
            (pacman->coord.y)--;
        else if (pacman->coord.y == 0 && map[pacman->coord.x][18] != '#')
            pacman->coord.y = 18;
        else return;

            
            if (map[pacman->coord.x][pacman->coord.y] == ' ') {
                pacman->score++;
                Mix_PlayMusic(eat_wav,1);
            }
            if (map[pacman->coord.x][pacman->coord.y] == 'O') {
                pacman->is_angry = true;
            }
            if (pacman->coord.y != 18) {
                map[pacman->coord.x][pacman->coord.y] = map[pacman->coord.x][pacman->coord.y + 1];
                map[pacman->coord.x][pacman->coord.y + 1] = '.';

            }
            else {
                map[pacman->coord.x][pacman->coord.y] = map[pacman->coord.x][0];
                map[pacman->coord.x][0] = '.';
            }

    }      
    else if (pacman->direction == UP && pacman->coord.x - 1 > 0 && map[pacman->coord.x - 1][pacman->coord.y] != '#') {
        
        if (map[pacman->coord.x - 1][pacman->coord.y] == ' ') {
            pacman->score++;
            Mix_PlayMusic(eat_wav,1);
        }
        if (map[pacman->coord.x - 1][pacman->coord.y] == 'O') {
                pacman->is_angry = true;
            }
        map[pacman->coord.x - 1][pacman->coord.y] = map[pacman->coord.x][pacman->coord.y];
        map[pacman->coord.x][pacman->coord.y] = '.';
        (pacman->coord.x)--;
    }
    else if (pacman->direction == DOWN && pacman->coord.x + 1 < 22 && map[pacman->coord.x + 1][pacman->coord.y] != '#') {
        
        if (map[pacman->coord.x + 1][pacman->coord.y] == ' ') {
            pacman->score++;
            Mix_PlayMusic(eat_wav,1);
        }
            if (map[pacman->coord.x + 1][pacman->coord.y] == 'O') {
                pacman->is_angry = true;
            }
        map[pacman->coord.x + 1][pacman->coord.y] = map[pacman->coord.x][pacman->coord.y];
        map[pacman->coord.x][pacman->coord.y] = '.';
        (pacman->coord.x)++;
    }
    

    if (read_score() < pacman->score)
        write_score(pacman->score);
    else
        write_score(read_score());

    
    
}

