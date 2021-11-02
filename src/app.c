#include "app.h"

void update(){
    //update the universe
    return;
}

int main(int argc, char* argv[]){

    //Window var & const
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    const Uint8 FPS = 1; //FPS --> [1;255] 
    const Uint16 DELAY = (Uint16)(1000/FPS);

    char title[] = "QuadTree Conway's Game Of Life";

    //window def
    SDL_Window* app_window;  //we neglect the pointer nature of window and renderer in the name
    SDL_Renderer* renderer;
    SDL_Event events;

    //system var def
    int e = EXIT_SUCCESS;
    int* _exit = &e;

    bool DEBUG = false;

    int W_WIDTH = -1;
    int W_HEIGHT = -1;

    //initializing window
    _initialize(&app_window,&renderer,title,SCREEN_WIDTH,SCREEN_HEIGHT,FPS,DELAY, _exit);
    if(e != EXIT_SUCCESS){
        printf("%d\n",e);
        return e;
    }

    //initializing Universe:
    world W = {new_cell(2,0,0,false),{0,0,3,3}};
    W.root->children = make_children(*W.root);
    W.root->children[3]->alive = true; //diff from W in test-universe

    //initializing gameLoop:
    bool isOpen = true;
    bool pause = true;
    int mouse_mode = 0;
        //FPS sys init
    int frame = -1;
    Uint32 last_frame = 0;
    Uint32 cur_frame = SDL_GetTicks();

    while (isOpen){
        frame++;
        last_frame = cur_frame;
        cur_frame = SDL_GetTicks();
        if(cur_frame-last_frame < DELAY){
            SDL_Delay(DELAY+last_frame-cur_frame);
            cur_frame = SDL_GetTicks();
        }
        if(DEBUG){
            printf("Frame: %d    Time: %d\n",frame,cur_frame);
        }
                

        //events:
        _event(&events, &isOpen, &pause,&mouse_mode, &W);

        //init the drawing (clear the screen and set up W_WIDTH and W_HEIGHT
        _init_drawing(app_window, renderer, &W_WIDTH,&W_HEIGHT);
        
        //update:
        if(!pause){
            //update:
            update();

            //pause indic drawing:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            draw_circle(renderer,W_WIDTH/20,W_HEIGHT/20,W_WIDTH/25);
        }

        //drawing and exit if pb:
        _draw(renderer, W_WIDTH,W_HEIGHT,W, _exit);
        if(*_exit != EXIT_SUCCESS){  //*_exit = e !!
            printf("%d\n",*_exit);
            return *_exit;
        }
        
        //GUI:
        /*
        GUI 
        */       

        //displaying:
        SDL_RenderPresent(renderer);
    }

    _quit(app_window,renderer);
    return EXIT_SUCCESS;
}
