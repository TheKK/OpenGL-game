#ifndef BASICFUNCTION_H
#define BASICFUNCTION_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "timer.h"

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720
#define FPS		60

using namespace std;

SDL_Texture* loadTexture ( string fileName, SDL_Renderer* renderer );

#endif
