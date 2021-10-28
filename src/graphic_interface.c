#include "graphic_interface.h"

void through_tree(cell* c,SDL_Renderer* p_renderer,int k,int orig_x,int orig_y){
    if(c->children == NULL){
        if(!c->alive){
            return;
        }
        int size = k*pow(2,c->level);
        SDL_Rect rect = {k * (c->x - orig_x), k * (c->y - orig_y), size, size};
        SDL_RenderFillRect(p_renderer,&rect);
        return;
    }
    through_tree(c->children[0],p_renderer,k, orig_x, orig_y);
    through_tree(c->children[1],p_renderer,k, orig_x, orig_y);
    through_tree(c->children[2],p_renderer,k, orig_x, orig_y);
    through_tree(c->children[3],p_renderer,k, orig_x, orig_y);
}

void render_universe(world W, SDL_Renderer* p_renderer, int w, int h, int* _exit){
    if(h!=w){
        fprintf(stderr, "Screen isn't a square !\n");
        *_exit = EXIT_FAILURE;
        return;
    }
    int k = w/(W.limits.x1-W.limits.x0+1); //factor to fit in the screen's size

    through_tree(W.root, p_renderer, k, W.limits.x0, W.limits.y0);
    return;
}

void _initialize(SDL_Window** p_app_window, SDL_Renderer** p_renderer, char title[], int SCREEN_WIDTH, int SCREEN_HEIGHT, Uint8 FPS, Uint16 DELAY, int* _exit){
    //init msg
    printf("\nStarting app.c ...\nParameters:\n  Initial screen Width: %d   Height: %d\n\
  FPS: %d  Delay between frames: %dms\n-------------------------------------\n",SCREEN_WIDTH,SCREEN_HEIGHT,FPS,DELAY);

    //SDL Init
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
        *_exit = -1;
        return;
    }

    *p_app_window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
    ,SCREEN_WIDTH,SCREEN_HEIGHT ,
    SDL_WINDOW_SHOWN); //a window ratio 1:1

    if (*p_app_window == NULL){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        *_exit = EXIT_FAILURE;
        return;
    }

    *p_renderer = SDL_CreateRenderer(*p_app_window,-1,SDL_RENDERER_ACCELERATED);

    if (*p_renderer == NULL){         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();
        *_exit = EXIT_FAILURE;
        return;
    } 

    return;
}

void modify(world* p_w){
    int x = 0;
    int y = 0;
    printf("change_state interface:\n  x: ");
    if(scanf("%d",&x) != 1) {
        fputs("error: invalid input\n", stderr);
        return;
    }
    printf("  y: ");
    if(scanf("%d",&y) != 1) {
        fputs("error: invalid input\n", stderr);
        return;
    }
    //!!!          'true' \/            !!!!
    change_state(p_w,x,y,true);
}

void _event(SDL_Event* p_events, bool* p_isOpen, bool* p_pause, world* p_w){
    while (SDL_PollEvent(p_events)){
        switch (p_events->type)
        {
            case SDL_MOUSEBUTTONUP:
                printf("mouse clicked\n"); //testing events
                break;
            case SDL_QUIT:
                *p_isOpen = false;
                break;
            case SDL_KEYUP:
                switch (p_events->key.keysym.sym)
                {
                    case SDLK_SPACE:
                        *p_pause = !(*p_pause);
                        break;
                    case SDLK_m:
                        modify(p_w);
                        break;
                    case SDLK_q:
                        *p_isOpen = false;
                    default:
                        break;
                }
        }
    }
}

void _init_drawing(SDL_Window* app_window, SDL_Renderer* renderer, int* p_w, int* p_h){
    //clear the screen:
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_GetWindowSize(app_window,p_w,p_h);
    return;
}

void _draw(SDL_Renderer* renderer, int W_WIDTH, int W_HEIGHT, world W, int* _exit){   
    //cells drawing
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    render_universe(W, renderer, W_WIDTH, W_HEIGHT, _exit);

    if(*_exit != 0){
        printf("%d\n",*_exit);
        return;
    }

    //test
    /*
    SDL_Rect rect = {100,100,50,50};
    SDL_RenderFillRect(renderer,&rect);*/

    return;
}

void _quit(SDL_Window* app_window, SDL_Renderer* renderer){
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(app_window);
    SDL_Quit();
    return;
}
