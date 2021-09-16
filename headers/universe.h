#ifndef UNIV_H
#define UNIV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct cell cell;
typedef struct world world;

struct cell{ //origin top left, y increasing down, x incr. right 
    int level;
    int x;
    int y;
    bool alive;
    cell** children; //children is either NULL or a 4 not-NULL-pointers array can't be [NULL,cell,cell,NULL]
    //format: [top left, tr, bl, br]
};

struct world{
    cell* root;
};

/*
PLAN:

*/

//init:

cell* new_cell(int level,int x,int y,bool alive);

//!!! to be deleted :!!!
cell** make_children(cell);

//display:

void display_cell(cell);

void display_universe(world);

//checks:
/*
    check if a cell is alive

    returns: 
    0 no
    1 yes
    2 outside borders so no
*/

int is_alive(world w, int x, int y); 

//accesses and changes:

cell* find_cell(world w, int x, int y);

void change_state(world w, int x, int y, bool new_state);







#endif