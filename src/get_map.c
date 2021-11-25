#include "../inc/header.h"

char ** get_map(){
    srand(time(NULL));
    char **map; 
    int map_choice = rand() % 3;
    switch (map_choice) {
    case 0:
        map = read_map("resource/maps/map1.txt");
        break;
    case 1:
        map = read_map("resource/maps/map2.txt");
        break;
    case 2:
        map = read_map("resource/maps/map3.txt");
        break;
    }
    return map;
}
