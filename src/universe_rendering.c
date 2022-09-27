#include "universe_rendering.h"

void through_tree(cell* c,SDL_Renderer* p_renderer,int k){
    if(c->children == NULL){
        if(!c->alive){
            return;
        }
        int size = k*pow(2,c->level);
        SDL_Rect rect = {k * c->x, k * c->y, size, size};
        SDL_RenderFillRect(p_renderer,&rect);
        return;
    }
    through_tree(c->children[0],p_renderer,k);
    through_tree(c->children[1],p_renderer,k);
    through_tree(c->children[2],p_renderer,k);
    through_tree(c->children[3],p_renderer,k);
}

void render_universe(world W,SDL_Renderer* p_renderer,int w,int h){
    if(h!=w){
        fprintf(stderr, "Screen isn't a square !\n");
        return EXIT_FAILURE;
    }
    int k = w/(W.limits.x1-W.limits.x0+1); //factor to fit in the screen's size

    through_tree(W.root,p_renderer,k);
}