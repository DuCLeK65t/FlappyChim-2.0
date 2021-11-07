#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
class State;
extern State* options;
extern State* menu;
extern State* current;
static int n = SDL_Init(SDL_INIT_EVERYTHING);
extern SDL_Window* win;
extern SDL_Renderer* ren;