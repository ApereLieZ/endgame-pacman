#include "../inc/header.h"

bool check_win (char **map) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == ' ') 
                return false;
        }        
    }
    return true;
}

