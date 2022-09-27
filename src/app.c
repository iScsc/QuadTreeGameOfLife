#include "app.h"

int main(int argc,char* argv[]){
    //SDL Init
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        return -1;
    }

    const int SCREEN_WIDTH = 1980;
    const int SCREEN_HEIGHT = 1080;

    char title[] = "QuadTree Conway's Game Of Life";
    SDL_Window* app_window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
    ,SCREEN_WIDTH/2,SCREEN_WIDTH/2 ,
    SDL_WINDOW_SHOWN); //a window ratio 1:1

    if (app_window == NULL){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return EXIT_FAILURE;     
    }  

    SDL_Renderer* p_renderer= SDL_CreateRenderer(app_window,-1,SDL_RENDERER_ACCELERATED);

    if (p_renderer == NULL){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();
        return EXIT_FAILURE;     
    } 
    
    SDL_Event events;

    bool isOpen = true;

    //Universe Init:
    world W = {new_cell(2,0,0,false),{0,0,3,3}};
    W.root->children = make_children(*W.root);
    W.root->children[3]->alive = true; //diff from W in test-universe

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
        /*
        update the univ
        */

        //clear the screen:
        SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);
        SDL_RenderClear(p_renderer);
        
        //cells drawing
        SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
        int W_WIDTH = -1;
        int W_HEIGHT = -1;
        SDL_GetWindowSize(app_window,&W_WIDTH,&W_HEIGHT);
        render_universe(W,p_renderer,W_WIDTH,W_HEIGHT);

        //test
        SDL_Rect rect = {100,100,50,50};
        SDL_RenderFillRect(p_renderer,&rect);

        
        /*
        GUI: step
        */       

        SDL_RenderPresent(p_renderer);
    }



    SDL_DestroyRenderer(p_renderer);
    SDL_DestroyWindow(app_window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
