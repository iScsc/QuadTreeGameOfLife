#include "app.h"

void _init(SDL_Window** p_app_window, SDL_Renderer** p_renderer, char title[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //SDL Init
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        return -1;
    }

    *p_app_window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
    ,SCREEN_WIDTH/2,SCREEN_WIDTH/2 ,
    SDL_WINDOW_SHOWN); //a window ratio 1:1

    if (*p_app_window == NULL){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return EXIT_FAILURE;     
    }

    *p_renderer = SDL_CreateRenderer(*p_app_window,-1,SDL_RENDERER_ACCELERATED);

    if (*p_renderer == NULL){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();
        return EXIT_FAILURE;     
    } 

    return;
}

void update(){
    return;
}

void _draw(SDL_Window* app_window, SDL_Renderer* renderer, world W){
    //clear the screen:
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    //cells drawing
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int W_WIDTH = -1;
    int W_HEIGHT = -1;
    SDL_GetWindowSize(app_window,&W_WIDTH,&W_HEIGHT);
    render_universe(W,renderer,W_WIDTH,W_HEIGHT);

    //test
    SDL_Rect rect = {100,100,50,50};
    SDL_RenderFillRect(renderer,&rect);

    return;
}

void _quit(SDL_Window* app_window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(app_window);
    SDL_Quit();
    return;
}

int main(int argc, char* argv[]){

    const int SCREEN_WIDTH = 1980;
    const int SCREEN_HEIGHT = 1080;

    char title[] = "QuadTree Conway's Game Of Life";

    SDL_Window* app_window;  //we neglect the pointer nature of window and renderer in the namae
    SDL_Renderer* renderer;
    SDL_Event events;

    _init(&app_window,&renderer,title,SCREEN_WIDTH,SCREEN_HEIGHT);

    //Universe Init:
    world W = {new_cell(2,0,0,false),{0,0,3,3}};
    W.root->children = make_children(*W.root);
    W.root->children[3]->alive = true; //diff from W in test-universe

    //gameLoop:
    bool isOpen = true;

    while (isOpen){
        while (SDL_PollEvent(&events)){
            switch (events.type)
            {
                case SDL_MOUSEBUTTONUP:
                    printf("mouse clicked\n"); //testing events
                    break;
                case SDL_QUIT:
                    isOpen = false;
                    break;
            }
        }
        update();

        _draw(app_window, renderer, W);

        /*
        GUI: 
        */       

        //displaying:
        SDL_RenderPresent(renderer);
    }

    _quit(app_window,renderer);
    return EXIT_SUCCESS;
}
