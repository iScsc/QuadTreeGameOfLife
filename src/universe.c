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

void display_universe(world W){
    printf("WORLD:\n\tTop level: %d\n\tBounds:\n\t%3d\n\t_____\n   |\t\t|\n%3d|\t\t|%3d\n   |\t\t|\n\t_____\n\t%3d\n",
    W.root->level,W.limits.y0,W.limits.x0,W.limits.x1,W.limits.y1);
}

//checks:

int off_limits(world w, int x, int y){
    if(x < w.limits.x0 || x > w.limits.x1 || y < w.limits.y0 || y > w.limits.y1){
        return 1;
    }
    return 0;
}

int get_state(world w, int x, int y){
    cell* c = find_cell(w,x,y);
    return (c==NULL ? 2 : c->alive);
}

//accesses and changes:

cell* find_cell(world w, int x, int y){
    if(off_limits(w,x,y)){
        return NULL;
    }
    cell* next = w.root;
    while(next->children != NULL){
        int index = (x < (next->children[3])->x ? 0 : 1) + (y < (next->children[3])->y ? 0 : 2);
        next = next->children[index];
    }
    return next;
}

void change_state(world w, int x, int y, bool new_state){
    cell* c = find_cell(w,x,y);
    if(c==NULL){
        //introducing future change_root
        return;
    }
    c->alive = new_state;
    return;
}
