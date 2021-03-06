#ifndef UNIV_H
#define UNIV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct cell cell;
typedef struct world world;
typedef struct bounds bounds;

struct cell{ //origin top left, y increasing down, x incr. right 
    int level;
    int x;
    int y;
    bool alive;
    cell** children; //children is either NULL or a 4 not-NULL-pointers array can't be [NULL,cell,cell,NULL]
    //format: [top left, tr , bl , br ]
    //coord : [   0 0  , 1 0, 0 1, 1 1]
};

struct bounds{
    int x0;
    int y0;
    int x1;
    int y1;
};

struct world{
    cell* root;
    bounds limits;
};

/*
PLAN:

get the state of a cell (get_state --> 0 1 or 2)
check if she will change (not in this file)
change is state 
    - (change_state)
    - can need to expand bounds (change_root) then change_state
*/


//init:

cell* new_cell(int level,int x,int y,bool alive); //TESTED

//!!! only for test-universe: !!!
cell** make_children(cell); //TESTED

//display:

void display_cell(cell); //TESTED

void display_universe(world); //TESTED

//checks:
/*
    check if a cell is alive

    returns: 
    0 no
    1 yes
    2 outside borders so no
*/

int off_limits(world w, int x, int y); //TESTED

int get_state(world w, int x, int y); //TESTED

void compressibility(world* p_w, int x,int y,int lvl);

//accesses and changes:

cell* find_cell(world w, int x, int y); //TESTED

cell* find_and_create_cell(world w, int x, int y); //TESTED

void change_state(world* p_w, int x, int y, bool new_state); //TESTED

void change_root(world* p_w, int old_root_location); //TESTED

void update_bounds(world* p_w);  //TESTED

//cleaning :

void rec_freeing(cell* c); //TESTED

void remove_descendants(world w,int x,int y, int lvl);  //TESTED

void free_cell(world w,int x,int y);

#endif