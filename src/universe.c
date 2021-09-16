#include "universe.h"

//init:

cell* new_cell(int level,int x,int y,bool alive){
    cell* n_c = malloc(sizeof(cell));
    *n_c = (cell) {.x = x, .y = y, .level = level, .alive = alive, .children = NULL};
    return n_c;
}

cell** make_children(cell parent){
    if(parent.level <= 0){
        fprintf(stderr, "ERROR : Lvl cannot go below 0 !\n       Cell(%d,%d) cannot have children !\n",parent.x,parent.y);
        return NULL;
    }
    int lvl = parent.level-1;
    int xs[2] = {parent.x,parent.x+pow(2,lvl)};
    int ys[2] = {parent.y,parent.y+pow(2,lvl)};

    cell **children = malloc(sizeof(cell*)*4);

    children[0] = new_cell(parent.level-1, xs[0], ys[0], parent.alive);
    children[1] = new_cell(parent.level-1, xs[1], ys[0], parent.alive);
    children[2] = new_cell(parent.level-1, xs[0], ys[1], parent.alive);
    children[3] = new_cell(parent.level-1, xs[1], ys[1], parent.alive);

    return children;
}

//display:

void display_cell(cell c){
    printf("Cell (%d,%d):\n\tPosition: X: %d   Y: %d\n\tLevel: %d\n\tAlive: %s\n\tChildren: %s\n",
    c.x, c.y, c.x, c.y, c.level, (c.alive ? "YES" : "NO"), (c.children==NULL ? "NO" : "YES"));
}

int* real_bounds(world w){ //NOT H DECLARED

    //int bounds[4]; //bounds are top left and bottom right points
    return NULL;
}

void display_universe(world w){
    printf("WORLD:\n\tTop level: %d\n\tBounds: %s\n",w.root->level,"TO BE FILLED");
}

//checks:
/*
int is_alive(world w, int x, int y){
    int size = (int)pow(2,w.root->level);
    if(x < w.root->x || x > w.root->x+size-1 || y < w.root->y || y > w.root->y+size-1){
        return 2;
    }
    cell* next = w.root;
    while(next->children != NULL){
        int index = (x < (next->children+3)->x ? 0 : 1) + (y < (next->children+3)->y ? 0 : 2); //à tester mdr
        next = next->children+index;
    }
    return next->alive;
}
*/
//use: 

