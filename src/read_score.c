#include "../inc/header.h"

int read_score() {
    FILE *file = fopen ("resource/score.txt", "r");
    if (!file) {
        file = fopen ("resource/score.txt", "w");
        fprintf(file, "0");
        fclose(file);
        return 0;
    }
    else {
        int a;
        fscanf(file, "%d", &a);
        fclose(file);
        return a;
    }
}

