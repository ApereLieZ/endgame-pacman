#include "../inc/header.h"

char **read_map(const char *file){
    char **map = malloc(22 * sizeof(char*));
    char symb;
    for (int i = 0; i < 22; i++) {
        map[i] = malloc(19 * sizeof(char));
    }
    int file_r = open(file, O_RDONLY);
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 19; j++) {
            read(file_r, &symb, 1);
            map[i][j] = symb;
        }
        read(file_r, &symb, 1);
        
    }
    close(file_r);
    return map;
}

