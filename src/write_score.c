#include "../inc/header.h"

void write_score(int score) {
    FILE *file = fopen ("resource/score.txt", "w");
    fprintf(file, "%d", score);
    fclose(file);
}

