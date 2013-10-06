#ifndef BASICFUNCTION_H
#define BASICFUNCTION_H

#include <cstdio>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

const short int SCREEN_WIDTH = 1280;
const short int SCREEN_HEIGHT = 720;
const short int SCREEN_BPP = 32;

const short int FPS = 60;

using namespace std;

void applySurface ( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

SDL_Surface* loadImage ( string fileName );

#endif
