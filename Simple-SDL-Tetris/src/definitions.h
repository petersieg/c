#ifndef DEFINITIONS_N
#define DEFINITIONS_N
#include "SDL.h"
#include "SDL_timer.h"
//#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

#define BLOCK_SIZE 40
#define GRID_WIDTH 10
#define GRID_HEIGHT 20
static uint32_t score = 0;
char progname[255];
#endif