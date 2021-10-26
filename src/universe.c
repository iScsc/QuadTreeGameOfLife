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

    children[0] = new_cell(lvl, xs[0], ys[0], parent.alive);
    children[1] = new_cell(lvl, xs[1], ys[0], parent.alive);
    children[2] = new_cell(lvl, xs[0], ys[1], parent.alive);
    children[3] = new_cell(lvl, xs[1], ys[1], parent.alive);

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

cell* find_cell_by_lvl(world w, int x, int y, int lvl){
    if(off_limits(w,x,y)){
        return NULL;
    }
    cell* next = w.root;
    while(next->children != NULL){
        if(lvl == next->level){
            return next;
        }
        int index = (x < (next->children[3])->x ? 0 : 1) + (y < (next->children[3])->y ? 0 : 2);
        //printf("Lvl: %d ; Index: %d\n",next->level,index);
        next = next->children[index];
    }
    return next;
}

cell* find_cell(world w, int x, int y){
    return find_cell_by_lvl(w,x,y,-1);
}

cell* find_and_create_cell(world w, int x, int y){
    cell* c = find_cell(w,x,y);
    while(c!=NULL &&(c->x != x || c->y != y || c->level != 0)){
        c->children = make_children(*c);
        int index = (x < (c->children[3])->x ? 0 : 1) + (y < (c->children[3])->y ? 0 : 2);
        c = c->children[index];
    }
    return c;
}

void change_state(world* p_w, int x, int y, bool new_state){
    cell* c = find_and_create_cell(*p_w,x,y);
    while(c==NULL){
        //RQ: in the case of a GoL, the while is useless, the changed 
        //cells will always be neighboors of world bounds so change state while never have to be recursive

        cell old_root = *(p_w->root); //NO POINTER, only get not set
        int old_root_location = (x < old_root.x ? 1 : 0) + (y < old_root.y ? 2 : 0);
        
        change_root(p_w,old_root_location);
        //display_universe(*p_w);
        c = find_and_create_cell(*p_w,x,y);
        
        /*
        if(c==NULL){
            fprintf(stderr, "change_root didn't worked !\n\tCan't find the cell %d,%d\
 after changing root from %d,%d lvl%d to %d,%d lvl%d\n", x, y,\
  old_root.x, old_root.y, old_root.level,\
  p_w->root->x, p_w->root->y, p_w->root->level);
            exit(EXIT_FAILURE);
            return;
        }
        */
    }
    c->alive = new_state;

    //compressibility(p_w,x,y,1);
    return;
}

void change_root(world* p_w, int old_root_location){
    cell* old_root = p_w->root;
    int new_x = (old_root_location % 2 == 0 ? old_root->x : old_root->x - pow(2,old_root->level));
    int new_y = (old_root_location < 2 ? old_root->y : old_root->y - pow(2,old_root->level));

    cell* new_root = new_cell(old_root->level+1, new_x, new_y,false);

    new_root->children = make_children(*new_root);
    free(new_root->children[old_root_location]);
    new_root->children[old_root_location] = old_root;

    p_w->root = new_root;

    update_bounds(p_w);
    return;
}

void update_bounds(world* p_w){
    cell root = *(p_w->root);
    int size = pow(2,root.level);
    p_w->limits.x0 = root.x;
    p_w->limits.y0 = root.y;
    p_w->limits.x1 = root.x+size-1;
    p_w->limits.y1 = root.y+size-1;
    return;
}

//cleaning:

void rec_freeing(cell* c){
    if(c->children == NULL){
        free(c);
        return;
    }
    for(int i = 0;i<4;i++){
        rec_freeing(c->children[i]);
    }
    free(c->children);
    free(c);
    return;
}

//remove_descendants delete every descendants (of level = lvl-1, lvl-2 ..., 0) of the node x,y,lvl but keep this node 
void remove_descendants(world w,int x,int y, int lvl){
    cell* to_free = find_cell_by_lvl(w,x,y,lvl);
    if(to_free->children == NULL){
        return;
    }
    for (int i = 0; i < 4; i++){
        rec_freeing(to_free->children[i]);
    }
    free(to_free->children);
    return;
}

//free_cell has a security to not-free a parent cell AND to free the cell.children before freeing the cell
void free_cell(world w,int x,int y){
    cell* to_free = find_cell(w,x,y);
    if(to_free->children == NULL){
        free(to_free);
        return;
    }
    else if(to_free->children[0] != NULL || to_free->children[1] != NULL || to_free->children[2] != NULL || to_free->children[3] != NULL){
        fprintf(stderr, "ERROR : Attempt to free a parent-cell !\n       Cell(%d,%d) has children !\n",to_free->x,to_free->y);
        return;
    }
    free(to_free->children);
    free(to_free);
    return;
}