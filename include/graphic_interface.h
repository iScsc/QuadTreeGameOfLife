#ifndef GRAPHIC_INTERFACE_H
#define GRAPHIC_INTERFACE_H

#include <SDL2/SDL.h>
#include "universe.h"

void _initialize(SDL_Window** p_app_window, SDL_Renderer** p_renderer, char title[],\
 int SCREEN_WIDTH, int SCREEN_HEIGHT, Uint8 FPS, Uint16 DELAY, int* _exit);

void _event(SDL_Event* p_events, bool* p_isOpen, bool* pause, world* w);

void _init_drawing(SDL_Window* app_window, SDL_Renderer* renderer, int* p_w, int* p_h);

void _draw(SDL_Renderer* renderer, int W_WIDTH, int W_HEIGHT, world W, int* _exit);

void _quit(SDL_Window* app_window, SDL_Renderer* renderer);

#endif