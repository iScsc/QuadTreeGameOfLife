#include "sdl_lib.h"

void draw_circle(SDL_Renderer* renderer,int c_x,int c_y,int d){
    for(int x = -d;x <= d;x++){
        int lim_y = (int)sqrt(d*d-x*x);
        for(int y = -lim_y;y <= lim_y; y++){
            SDL_RenderDrawPoint(renderer,c_x+x,c_y+y);
        }
    }
    return;
}