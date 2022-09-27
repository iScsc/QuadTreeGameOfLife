#include "app.h"

void update(){
    return;
}

int main(int argc, char* argv[]){

    const int SCREEN_WIDTH = 1980;
    const int SCREEN_HEIGHT = 1080;

    char title[] = "QuadTree Conway's Game Of Life";

    SDL_Window* app_window;  //we neglect the pointer nature of window and renderer in the name
    SDL_Renderer* renderer;
    SDL_Event events;

    int e = EXIT_SUCCESS;
    int* _exit = &e;



    _initialize(&app_window,&renderer,title,SCREEN_WIDTH,SCREEN_HEIGHT, _exit);
    if(e != EXIT_SUCCESS){
        printf("%d\n",e);
        return e;
    }

    //Universe Init:
    world W = {new_cell(2,0,0,false),{0,0,3,3}};
    W.root->children = make_children(*W.root);
    W.root->children[3]->alive = true; //diff from W in test-universe

    //gameLoop:
    bool isOpen = true;

    while (isOpen){
        _event(&events, &isOpen);

        update();

        _draw(app_window, renderer, W, _exit);
        if(e != EXIT_SUCCESS){
            printf("%d\n",e);
            return e;
        }


        /*
        GUI: 
        */       

        //displaying:
        SDL_RenderPresent(renderer);
    }

    _quit(app_window,renderer);
    return EXIT_SUCCESS;
}
