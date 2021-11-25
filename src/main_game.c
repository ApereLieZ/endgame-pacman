#include "../inc/header.h"

SDL_Surface* gScreenSurface;

SDL_Texture* wall_texture;
SDL_Texture* coin_texture;

SDL_Texture* pacman_open_right_texture;
SDL_Texture* pacman_close_left_texture;

SDL_Texture* pacman_open_left_texture;
SDL_Texture* pacman_close_right_texture;

SDL_Texture* pacman_open_front_texture;
SDL_Texture* pacman_close_front_texture;

SDL_Texture* red_ghost_texture;
SDL_Texture* pink_ghost_texture;
SDL_Texture* pink_ghost_texture;
SDL_Texture* yellow_ghost_texture;
SDL_Texture* pause_texture;

SDL_Texture* heart;

SDL_Texture* scared_texture;

SDL_Renderer* renderer;



Mix_Music *win_wav;
Mix_Music *death_wav;
bool WIN;

char red_ghost_surface = ' ', pink_ghost_surface = ' ', blue_ghost_surface = ' ', yellow_ghost_surface = ' ';

struct queue *create_queue(int size) {
    struct queue *q = malloc(sizeof(*q));
    q->nodes = malloc(sizeof(struct node) * size);
    q->head = -1;
    q->tail = -1;
    return q;
}

bool queue_is_empty(struct queue *q) {
    if (q->tail == -1) {
        return true;
    }
    return false;
}

void push_queue(struct queue *q, struct node n) {
    if (q->head == -1) {
        q->head = 0;
    }
    q->tail++;
    q->nodes[q->tail].pt = n.pt;
    q->nodes[q->tail].dist = n.dist;
}

void pop_queue(struct queue *q) {
    q->head++;
    if (q->head > q->tail) {
        q->head = q->tail = -1;
    }
}

bool isValid(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

int max_dist = -1;

point *push_point(point *path, int *size, point pt) {
    point *new_path = malloc(sizeof(point) * (*size + 1));
    
    for (int i = 0; i < *size; i++) {
        new_path[i].x = path[i].x;
        new_path[i].y = path[i].y;
    }
    
    new_path[*size].x = pt.x;
    new_path[*size].y = pt.y;
    (*size)++;
    
    free(path);
    return new_path;
}

void reverse_path(point *path, int path_size) {
    for (int i = 0, j = path_size - 1; i < path_size / 2; i++, j--) {
        point tmp = path[i];
        path[i] = path[j];
        path[j] = tmp;
    }
}

point *get_path(char **map, point entry, point exit, int rows, int cols, int *path_size) {
    if (map[entry.x][entry.y] == '#' || map[exit.x][exit.y] == '#') {
        return NULL;
    }
    
    int d[rows][cols];
    bool visited[rows][cols];
    point *path = malloc(sizeof(point*));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
            d[i][j] = -1;
        }
    }
    
    visited[entry.x][entry.y] = true;
    d[entry.x][entry.y] = 0;
   
    struct queue *q = create_queue(rows * cols);
     
    struct node s = {entry, 0};
    push_queue(q, s);
 
    while (!queue_is_empty(q)) {
        struct node curr = q->nodes[q->head];
        point pt = curr.pt;
        
        if (pt.x == exit.x && pt.y == exit.y) {
            int xx = pt.x, yy = pt.y;
            int dist = curr.dist;
            
            d[pt.x][pt.y] = dist;
            path = push_point(path, path_size, pt);
            
            while (xx != entry.x || yy != entry.y) {
                if (xx == entry.x && yy == entry.y) {
                    break;
                }
                
                if (xx > 0 && d[xx - 1][yy] == dist - 1) {
                    point pt = {xx - 1, yy};
                    path = push_point(path, path_size, pt);
                    xx--;
                }
                else if (xx < rows - 1 && d[xx + 1][yy] == dist - 1) {
                    point pt = {xx + 1, yy};
                    path = push_point(path, path_size, pt);
                    xx++;
                }
                else if (yy > 0 && d[xx][yy - 1] == dist - 1) {
                    point pt = {xx, yy - 1};
                    path = push_point(path, path_size, pt);
                    yy--;
                }
                else if (yy < cols - 1 && d[xx][yy + 1] == dist - 1) {
                    point pt = {xx, yy + 1};
                    path = push_point(path, path_size, pt);
                    yy++;
                }
                dist--;
            }
            reverse_path(path, *path_size);
            
            free(q->nodes);
            free(q);
            return path;
        }
 
        pop_queue(q);
 
        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col) && map[row][col] != '#' && !visited[row][col]) {
                visited[row][col] = true;
                struct node Adjcell = { {row, col}, curr.dist + 1 };
                push_queue(q, Adjcell);
                d[row][col] = curr.dist + 1;
            }
        }
    }
    
    free(path);
    free(q->nodes);
    free(q);
    return NULL;
}

point *search_empty_cell(char **map, point entry) {
    bool visited[ROWS][COLS];
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            visited[i][j] = false;
        }
    }
    
    visited[entry.x][entry.y] = true;
   
    struct queue *q = create_queue(ROWS * COLS);
     
    struct node s = {entry, 0};
    push_queue(q, s);
 
    while (!queue_is_empty(q)) {
        struct node curr = q->nodes[q->head];
        point pt = curr.pt;
        
        if (map[pt.x][pt.y] == ' ' || map[pt.x][pt.y] == '.' || map[pt.x][pt.y] == '+') {
            point *result_pt = malloc(sizeof(point*));
            result_pt->x = pt.x;
            result_pt->y = pt.y;
            free(q->nodes);
            free(q);
            return result_pt;
        }
 
        pop_queue(q);
 
        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col) && !visited[row][col]) {
                visited[row][col] = true;
                struct node Adjcell = { {row, col}, curr.dist + 1 };
                push_queue(q, Adjcell);
            }
        }
    }
    
    free(q->nodes);
    free(q);
    return NULL;
}

void move_red_ghost(char **map, point pacman_pt, RedGhost *red_ghost) {
    int path_size = 0;
    point *path = get_path(map, red_ghost->coord, pacman_pt, ROWS, COLS, &path_size);
    
    if (!path)
        return;
    
    if (red_ghost_surface != 'b' && red_ghost_surface != 'p' && red_ghost_surface != 'y') {
        map[path[0].x][path[0].y] = red_ghost_surface;
    }
    red_ghost_surface = map[path[1].x][path[1].y];
    red_ghost->coord = path[1];
    map[red_ghost->coord.x][red_ghost->coord.y] = 'r';
    
    if (path[1].x - path[0].x > 0)
        red_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        red_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        red_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        red_ghost->direction = LEFT;
    
    free(path);
}

void move_pink_ghost(char **map, point pacman_pt, PinkGhost *pink_ghost, int direction) {
    point *path = NULL;
    int i = 0, path_size;
    while (!path && i++ <= 4) {
        point pt = {pacman_pt.x, pacman_pt.y};
        path_size = 0;

        switch (direction) {
        case LEFT:
            pt.y -= 4 - i;
                
            if(!isValid(pt.x, pt.y))
                continue;
                
            break;
        case RIGHT:
            pt.y += 4 - i;
                
            if(!isValid(pt.x, pt.y))
                continue;
                
            break;
        case UP:
            pt.x -= 4 - i;
                
            if(!isValid(pt.x, pt.y))
                continue;
                
            break;
        case DOWN:
            pt.x += 4 - i;
                
            if(!isValid(pt.x, pt.y))
                continue;
                
            break;
        }

        if (pt.x == pink_ghost->coord.x && pt.y == pink_ghost->coord.y)
            continue;

        path = get_path(map, pink_ghost->coord, pt, ROWS, COLS, &path_size);
    }
    
    if (!path)
        return;
    
    if (pink_ghost_surface != 'b' && pink_ghost_surface != 'r' && pink_ghost_surface != 'y') {
        map[path[0].x][path[0].y] = pink_ghost_surface;
    }
    pink_ghost_surface = map[path[1].x][path[1].y];
    pink_ghost->coord = path[1];
    map[pink_ghost->coord.x][pink_ghost->coord.y] = 'p';
    
    if (path[1].x - path[0].x > 0)
        pink_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        pink_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        pink_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        pink_ghost->direction = LEFT;
    
    free(path);
}

void move_blue_ghost(char **map, point pacman_pt, point red_ghost_pt, BlueGhost *blue_ghost, int direction) {
    point pt = pacman_pt;
    switch (direction) {
    case LEFT:
        pt.y -= 2;
        break;
    case RIGHT:
        pt.y += 2;
        break;
    case UP:
        pt.x -= 2;
        break;
    case DOWN:
        pt.x += 2;
        break;
    }
    
    point dst;
    dst.x = (pt.x - red_ghost_pt.x) * 2 + red_ghost_pt.x;
    dst.y = (pt.y - red_ghost_pt.y) * 2 + red_ghost_pt.y;
    
    if (dst.x < 0)
        dst.x = 0;
    
    if (dst.x >= ROWS)
        dst.x = ROWS - 1;
    
    if (dst.y < 0)
        dst.y = 0;
    
    if (dst.y >= COLS)
        dst.y = COLS - 1;
    
    if (map[dst.x][dst.y] == '#' || map[dst.x][dst.y] == 'b') {
        point *tmp = search_empty_cell(map, dst);
        if (tmp) {
            dst.x = tmp->x;
            dst.y = tmp->y;
            free(tmp);
        }
        else {
            dst.x = pacman_pt.x;
            dst.y = pacman_pt.y;
        }
    }
    
    int path_size = 0;
    point *path = get_path(map, blue_ghost->coord, dst, ROWS, COLS, &path_size);
    
    if (!path) {
        dst.x = pacman_pt.x;
        dst.y = pacman_pt.y;
        path = get_path(map, blue_ghost->coord, dst, ROWS, COLS, &path_size);
        if (!path)
            return;
    }
    
    if (blue_ghost_surface != 'p' && blue_ghost_surface != 'r' && blue_ghost_surface != 'y' && blue_ghost_surface != '+') {
        map[path[0].x][path[0].y] = blue_ghost_surface;
    }
    blue_ghost_surface = map[path[1].x][path[1].y];
    blue_ghost->coord = path[1];
    map[blue_ghost->coord.x][blue_ghost->coord.y] = 'b';
    
    if (path[1].x - path[0].x > 0)
        blue_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        blue_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        blue_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        blue_ghost->direction = LEFT;
    
    free(path);
}

void move_yellow_ghost(char **map, YellowGhost *yellow_ghost) {
    while (map[yellow_ghost->dst.x][yellow_ghost->dst.y] == '#' || isalpha(map[yellow_ghost->dst.x][yellow_ghost->dst.y])) {
        yellow_ghost->dst.x = rand() % ROWS;
        yellow_ghost->dst.y = rand() % COLS;
    }

    int path_size = 0;
    point *path = get_path(map, yellow_ghost->coord, yellow_ghost->dst, ROWS, COLS, &path_size);
    
    if (!path)
        return;
    
    if (yellow_ghost_surface != 'b' && yellow_ghost_surface != 'p' && yellow_ghost_surface != 'r') {
        map[path[0].x][path[0].y] = yellow_ghost_surface;
    }
    yellow_ghost_surface = map[path[1].x][path[1].y];
    yellow_ghost->coord = path[1];
    map[yellow_ghost->coord.x][yellow_ghost->coord.y] = 'y';
    
    if (path[1].x - path[0].x > 0)
        yellow_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        yellow_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        yellow_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        yellow_ghost->direction = LEFT;
    
    free(path);
}

void move_scared_red_ghost(char **map, RedGhost *red_ghost) {
    while (map[red_ghost->dst.x][red_ghost->dst.y] == '#' || isalpha(map[red_ghost->dst.x][red_ghost->dst.y])) {
        red_ghost->dst.x = rand() % ROWS;
        red_ghost->dst.y = rand() % COLS;
    }

    int path_size = 0;
    point *path = get_path(map, red_ghost->coord, red_ghost->dst, ROWS, COLS, &path_size);
    
    if (!path)
        return;
    
    if (red_ghost_surface != 'b' && red_ghost_surface != 'p' && red_ghost_surface != 'y') {
        map[path[0].x][path[0].y] = red_ghost_surface;
    }
    red_ghost_surface = map[path[1].x][path[1].y];
    red_ghost->coord = path[1];
    map[red_ghost->coord.x][red_ghost->coord.y] = 'r';
    
    if (path[1].x - path[0].x > 0)
        red_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        red_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        red_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        red_ghost->direction = LEFT;
    
    free(path);
}

void move_scared_pink_ghost(char **map, PinkGhost *pink_ghost) {
    while (map[pink_ghost->dst.x][pink_ghost->dst.y] == '#' || isalpha(map[pink_ghost->dst.x][pink_ghost->dst.y])) {
        pink_ghost->dst.x = rand() % ROWS;
        pink_ghost->dst.y = rand() % COLS;
    }

    int path_size = 0;
    point *path = get_path(map, pink_ghost->coord, pink_ghost->dst, ROWS, COLS, &path_size);
    
    if (!path)
        return;
    
    if (pink_ghost_surface != 'b' && pink_ghost_surface != 'r' && pink_ghost_surface != 'y') {
        map[path[0].x][path[0].y] = pink_ghost_surface;
    }
    pink_ghost_surface = map[path[1].x][path[1].y];
    pink_ghost->coord = path[1];
    map[pink_ghost->coord.x][pink_ghost->coord.y] = 'p';
    
    if (path[1].x - path[0].x > 0)
        pink_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        pink_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        pink_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        pink_ghost->direction = LEFT;
    
    free(path);
}

void move_scared_blue_ghost(char **map, BlueGhost *blue_ghost) {
    while (map[blue_ghost->dst.x][blue_ghost->dst.y] == '#' || isalpha(map[blue_ghost->dst.x][blue_ghost->dst.y])) {
        blue_ghost->dst.x = rand() % ROWS;
        blue_ghost->dst.y = rand() % COLS;
    }

    int path_size = 0;
    point *path = get_path(map, blue_ghost->coord, blue_ghost->dst, ROWS, COLS, &path_size);
    
    if (!path)
        return;
    
    if (blue_ghost_surface != 'p' && blue_ghost_surface != 'r' && blue_ghost_surface != 'y') {
        map[path[0].x][path[0].y] = blue_ghost_surface;
    }
    blue_ghost_surface = map[path[1].x][path[1].y];
    blue_ghost->coord = path[1];
    map[blue_ghost->coord.x][blue_ghost->coord.y] = 'b';
    
    if (path[1].x - path[0].x > 0)
        blue_ghost->direction = DOWN;
    else if (path[1].x - path[0].x < 0)
        blue_ghost->direction = UP;
    else if (path[1].y - path[0].y > 0)
        blue_ghost->direction = RIGHT;
    else if (path[1].y - path[0].y < 0)
        blue_ghost->direction = LEFT;
    
    free(path);
}

bool isPacmanFacedGhost(point pacman_pt, point red_ghost_pt, point pink_ghost_pt, point blue_ghost_pt, point yellow_ghost_pt) {
    return (pacman_pt.x == red_ghost_pt.x && pacman_pt.y == red_ghost_pt.y) ||
    (pacman_pt.x == pink_ghost_pt.x && pacman_pt.y == pink_ghost_pt.y) ||
    (pacman_pt.x == blue_ghost_pt.x && pacman_pt.y == blue_ghost_pt.y) ||
    (pacman_pt.x == yellow_ghost_pt.x && pacman_pt.y == yellow_ghost_pt.y);
}

bool isPacmanDied(char **map, Pacman *pacman, RedGhost *redGhost, PinkGhost *pinkGhost, BlueGhost *blueGhost, YellowGhost *yellowGhost) {
    if (isPacmanFacedGhost(pacman->coord, redGhost->coord, pinkGhost->coord, blueGhost->coord, yellowGhost->coord)) {

        if(pacman->is_angry){
            if (pacman->coord.x == redGhost->coord.x && pacman->coord.y == redGhost->coord.y) {
                
                map[redGhost->coord.x][redGhost->coord.y] = '+';
                map[redGhost->coord.x][redGhost->coord.y] = red_ghost_surface;
                
                redGhost->coord.x = RED_POS_X;
                redGhost->coord.y = RED_POS_Y;
                map[redGhost->coord.x][redGhost->coord.y] = 'r';
                
            }
            if(pacman->coord.x == yellowGhost->coord.x && pacman->coord.y == yellowGhost->coord.y){
                map[yellowGhost->coord.x][yellowGhost->coord.y] = '+';
                map[yellowGhost->coord.x][yellowGhost->coord.y] = yellow_ghost_surface;
                yellowGhost->coord.x = YELLOW_POS_X;
                yellowGhost->coord.y = YELLOW_POS_Y;
                map[yellowGhost->coord.x][yellowGhost->coord.y] = 'y';
                
            }
            if(pacman->coord.x == blueGhost->coord.x && pacman->coord.y == blueGhost->coord.y){
                map[blueGhost->coord.x][blueGhost->coord.y] = '+';
                map[blueGhost->coord.x][blueGhost->coord.y] = blue_ghost_surface;
                blueGhost->coord.x = BLUE_POS_X;
                blueGhost->coord.y = BLUE_POS_Y;
                map[blueGhost->coord.x][blueGhost->coord.y] = 'b';
                
                
            }
            
            if(pacman->coord.x == pinkGhost->coord.x && pacman->coord.y == pinkGhost->coord.y) {
                map[pinkGhost->coord.x][pinkGhost->coord.y] = '+';
                map[pinkGhost->coord.x][pinkGhost->coord.y] = pink_ghost_surface;
                pinkGhost->coord.x = PINK_POS_X;
                pinkGhost->coord.y = PINK_POS_Y;
                map[pinkGhost->coord.x][pinkGhost->coord.y] = 'p';
                //pink_ghost_surface = ' ';
            }
            return false;
        }else {
            Mix_PlayMusic(death_wav,1);
            SDL_Delay(200);
            map[redGhost->coord.x][redGhost->coord.y] = red_ghost_surface;
            redGhost->coord.x = RED_POS_X;
            redGhost->coord.y = RED_POS_Y;
            map[redGhost->coord.x][redGhost->coord.y] = 'r';

            map[pinkGhost->coord.x][pinkGhost->coord.y] = pink_ghost_surface;
            pinkGhost->coord.x = PINK_POS_X;
            pinkGhost->coord.y = PINK_POS_Y;
            map[pinkGhost->coord.x][pinkGhost->coord.y] = 'p';

            map[blueGhost->coord.x][blueGhost->coord.y] = blue_ghost_surface;
            blueGhost->coord.x = BLUE_POS_X;
            blueGhost->coord.y = BLUE_POS_Y;
            map[blueGhost->coord.x][blueGhost->coord.y] = 'b';

            map[yellowGhost->coord.x][yellowGhost->coord.y] = yellow_ghost_surface;
            yellowGhost->coord.x = YELLOW_POS_X;
            yellowGhost->coord.y = YELLOW_POS_Y;
            map[yellowGhost->coord.x][yellowGhost->coord.y] = 'y';

            red_ghost_surface = ' ';
            pink_ghost_surface = ' ';
            blue_ghost_surface = ' ';
            yellow_ghost_surface = ' ';
            
            pacman->hp--;
            pacman->direction = LEFT;
            map[pacman->coord.x][pacman->coord.y] = '.';
            pacman->coord.x = ROWS - 2;
            pacman->coord.y = 1;
            map[pacman->coord.x][pacman->coord.y] = '+';
            return true;
        }
        
    }
    return false;
}
Pacman pacman;
void main_game(char **map) {

    
    RedGhost redGhost;
    PinkGhost pinkGhost;
    BlueGhost blueGhost;
    YellowGhost yellowGhost;
    SDL_Texture* score_texture;
    SDL_Texture* text_score_texture;
    SDL_Texture* cur_yelllow_texture = yellow_ghost_texture;
    SDL_Texture* cur_blue_texture = blue_ghost_texture;
    SDL_Texture* cur_red_texture = red_ghost_texture;
    SDL_Texture* cur_pink_texture = pink_ghost_texture;
    char bs[] = "SCORE:";
    SDL_Texture* cur_pacman_texture = pacman_close_left_texture;
    
    bool quit = false;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == '+') {
                pacman.coord.x = i;
                pacman.coord.y = j;
                pacman.is_angry = false;
                pacman.direction = LEFT;
                
                if(!WIN){
                    pacman.hp = 3;
                    
                    pacman.score = 0;
                }
                
            }
            else if (map[i][j] == 'r') {
                redGhost.coord.x = i;
                redGhost.coord.y = j;
                redGhost.dst.x = rand() % ROWS;
                redGhost.dst.y = rand() % COLS;
                redGhost.direction = PAUSE;
            }
            else if (map[i][j] == 'p') {
                pinkGhost.coord.x = i;
                pinkGhost.coord.y = j;
                pinkGhost.dst.x = rand() % ROWS;
                pinkGhost.dst.y = rand() % COLS;
                pinkGhost.direction = PAUSE;
            }
            else if (map[i][j] == 'b') {
                blueGhost.coord.x = i;
                blueGhost.coord.y = j;
                blueGhost.dst.x = rand() % ROWS;
                blueGhost.dst.y = rand() % COLS;
                blueGhost.direction = PAUSE;
            }
            else if (map[i][j] == 'y') {
                yellowGhost.coord.x = i;
                yellowGhost.coord.y = j;
                yellowGhost.dst.x = rand() % ROWS;
                yellowGhost.dst.y = rand() % COLS;
                yellowGhost.direction = PAUSE;
            }
        }
    }
    SDL_Color color = {250, 250, 250, 0};
    //SDL_Event e;
    int tick = 0;
    int tick_to_be_angry = 0;
    int tick_ghost = 0;
    int animframe = 0;

    

    bool firstRun = true;  
    bool pause = false;                                 

    while (!quit) { 
        if(pacman.hp <= 0) {
            WIN = false;
            break;
        }
        if(check_win(map)){
            Mix_PlayMusic(win_wav,1);
            SDL_Delay(5000);
            WIN = true;
            break;
        }
        int key = key_press(pacman.direction);
        if (key == PAUSE) 
            pause = (pause == true ? false  : true);
        else if ((key == UP && map[pacman.coord.x - 1][pacman.coord.y] != '#') || 
            (key == DOWN && map[pacman.coord.x + 1][pacman.coord.y] != '#') || 
            (key == LEFT && map[pacman.coord.x][pacman.coord.y - 1] != '#') || 
            (key == RIGHT && map[pacman.coord.x][pacman.coord.y + 1] != '#'))
            pacman.direction = key;
        if (!pause) {
            
            SDL_SetRenderDrawColor(renderer, 30,30,30, 255);                                   
            SDL_RenderClear(renderer);

            
            if (!(tick % 2)) {
                char temptext[4];
                SDL_itoa(pacman.score, temptext,10);
                score_texture = renderText(temptext,"resource/ttf/mat.ttf", color, 30, renderer);
                move_pacman(map, &pacman);
                if(tick_to_be_angry > 12){
                    pacman.is_angry = false;
                    tick_to_be_angry = 0;
                    
                }
                if (isPacmanDied(map, &pacman, &redGhost, &pinkGhost, &blueGhost, &yellowGhost)) {
                    firstRun = true;
                    tick_ghost = 0;
                    continue;
                }
            }
            if(tick > 4) {
                if(!pacman.is_angry) {
                    cur_yelllow_texture = yellow_ghost_texture;
                    cur_blue_texture = blue_ghost_texture;
                    cur_red_texture = red_ghost_texture;
                    cur_pink_texture = pink_ghost_texture;
                    
                    if (tick_ghost > 5) {
                        move_red_ghost(map, pacman.coord, &redGhost);
                        
                    }

                    if (isPacmanDied(map, &pacman, &redGhost, &pinkGhost, &blueGhost, &yellowGhost)) {
                        firstRun = true;
                        tick_ghost = 0;
                        continue;
                    }
                    
                    if (tick_ghost > 8) {
                        move_pink_ghost(map, pacman.coord, &pinkGhost, pacman.direction);
                    }
                    
                    if (isPacmanDied(map, &pacman, &redGhost, &pinkGhost, &blueGhost, &yellowGhost)) {
                        firstRun = true;
                        tick_ghost = 0;
                        continue;
                    }
                    
                    if (tick_ghost > 25) {
                        move_blue_ghost(map, pacman.coord, redGhost.coord, &blueGhost, pacman.direction);
                    }
                    
                    if (isPacmanDied(map, &pacman, &redGhost, &pinkGhost, &blueGhost, &yellowGhost)) {
                        firstRun = true;
                        tick_ghost = 0;
                        continue;
                    }
                    
                    tick_ghost++;
                }
                else {
                    cur_yelllow_texture = scared_texture;
                    cur_blue_texture = scared_texture;
                    cur_red_texture = scared_texture;
                    cur_pink_texture = scared_texture;

                    move_scared_blue_ghost(map, &blueGhost);
                    move_scared_red_ghost(map, &redGhost);
                    move_scared_pink_ghost(map, &pinkGhost);
                    tick_to_be_angry++;
                }

                if (tick_ghost > 40) {
                    move_yellow_ghost(map, &yellowGhost);
                    firstRun = false;
                }
                
                if (isPacmanDied(map, &pacman, &redGhost, &pinkGhost, &blueGhost, &yellowGhost)) {
                    firstRun = true;
                    tick_ghost = 0;
                    continue;
                }
                
                
                if(tick_ghost > 45) tick_ghost = 45;
                tick = 0;
            }

            if(animframe == 0) {
                if(pacman.direction == LEFT)
                    cur_pacman_texture = pacman_close_left_texture;
                else if(pacman.direction == RIGHT)
                    cur_pacman_texture = pacman_close_right_texture;
                else if(pacman.direction == DOWN)
                    cur_pacman_texture = pacman_close_front_texture;
                else if(pacman.direction == UP)
                    cur_pacman_texture = pacman_back_texture;
                animframe = 1;
            }else {
                if(pacman.direction == LEFT)
                    cur_pacman_texture = pacman_open_left_texture;
                else if(pacman.direction == RIGHT)
                    cur_pacman_texture = pacman_open_right_texture;
                else if(pacman.direction == DOWN)
                    cur_pacman_texture = pacman_open_front_texture;
                else if(pacman.direction == UP)
                    cur_pacman_texture = pacman_back_texture;
                animframe = 0;
            }
        }
        bool in_game = false;
        for(int i = 0; i < 19; i++) {
            for(int j = 0; j < 22; j++) {
                SDL_Rect stretcRect = {50 * i,50 * j, 50, 50};
            
                if(map[j][i] == '#') {                        
                    SDL_RenderCopy(renderer, wall_texture, NULL, &stretcRect);
                }
                else if (i == pacman.coord.y && j == pacman.coord.x) {
                    SDL_Rect stretcRect = {50 * pacman.coord.y,50 * pacman.coord.x, 50, 50};
                    SDL_RenderCopy(renderer, cur_pacman_texture, NULL, &stretcRect);
                    in_game = true;
                }
                else if (i == redGhost.coord.y && j == redGhost.coord.x) {
                    SDL_Rect stretcRect = {50 * redGhost.coord.y,50 * redGhost.coord.x, 50, 50};
                    SDL_RenderCopy(renderer, cur_red_texture, NULL, &stretcRect);
                }
                else if (i == pinkGhost.coord.y && j == pinkGhost.coord.x) {
                    SDL_Rect stretcRect = {50 * pinkGhost.coord.y,50 * pinkGhost.coord.x, 50, 50};
                    SDL_RenderCopy(renderer, cur_pink_texture, NULL, &stretcRect);
                }
                else if (i == blueGhost.coord.y && j == blueGhost.coord.x) {
                    SDL_Rect stretcRect = {50 * blueGhost.coord.y,50 * blueGhost.coord.x, 50, 50};
                    SDL_RenderCopy(renderer, cur_blue_texture, NULL, &stretcRect);
                }
                else if (i == yellowGhost.coord.y && j == yellowGhost.coord.x) {
                    SDL_Rect stretcRect = {50 * yellowGhost.coord.y,50 * yellowGhost.coord.x, 50, 50};
                    SDL_RenderCopy(renderer, cur_yelllow_texture, NULL, &stretcRect);
                }
                else if (map[j][i] == 'O') {
                    SDL_RenderCopy(renderer, brain_texture, NULL, &stretcRect);

                }
                else if (map[j][i] != '.'){
                    SDL_Rect coin_cord = {50 * i + 25,50 * j + 25, 12, 12};
                    SDL_RenderCopy(renderer, coin_texture, NULL, &coin_cord);
                }
                
            }
            SDL_Rect score_text = {165, 0, 50, 50};
            SDL_RenderCopy(renderer, score_texture,NULL, &score_text);
            text_score_texture = renderText(bs,"resource/ttf/mat.ttf", color, 60, renderer);
            SDL_Rect score_text_text = {20, 0, 150, 50};
            SDL_RenderCopy(renderer, text_score_texture,NULL, &score_text_text);

            
            
        }
        if (pause)
            SDL_RenderCopy(renderer, pause_texture, NULL, NULL);
            for(int k = 0; k < pacman.hp; k++) {
                SDL_Rect rectHeart = {750 + 50*k, 0,50, 50 };
                SDL_RenderCopy(renderer, heart, NULL, &rectHeart);
            }
        SDL_RenderPresent(renderer);
        
        SDL_Delay(100);
        
        tick++;
    }
}


