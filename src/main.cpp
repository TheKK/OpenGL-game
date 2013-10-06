/*
main.cpp
*/
#include <cstdio>
#include <iostream>
#include "basicFunctions.h"
#include "timer.h"
#include "gameMenu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;
/*
#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720
#define SCREEN_BPP	32
#define FPS		60
*/
SDL_Surface* screen = NULL;

bool init ()
{
	//Init SDL libery
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )	return false;

	//Setup screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	if( screen == NULL )	return false;

	//Setup window caption
	SDL_WM_SetCaption( "SNAKE", NULL );

	return true;
}
/*
void applySurface ( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Create offset
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface* loadImage ( string fileName )
{
	//Create two surface for oringinal and optimized image
	SDL_Surface* oringinal = NULL;
	SDL_Surface* optimized = NULL;

	oringinal = IMG_Load( fileName.c_str() ); 
	if( oringinal == NULL )		return NULL;

	optimized = SDL_DisplayFormat( oringinal );
	if( optimized == NULL ){
		SDL_FreeSurface( oringinal );	
		return NULL;
	}

	SDL_SetColorKey( optimized, SDL_SRCCOLORKEY,
		SDL_MapRGB( optimized->format, 0x00, 0xFF, 0xFF ) );

	return optimized;
}
*/
void cleanUp()
{
}

void gameStartScreen()
{
	SDL_Event event;
	SDL_Surface* logo = loadImage( "./game/img/logo.png" );
	if( logo == NULL )	exit( 1 );

	Timer fps;
	short int frameCount = 0;
	short int alpha = SDL_ALPHA_TRANSPARENT;

	do{
		fps.start();
		
		//Event handle		
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_KEYDOWN ){
				if( event.key.keysym.sym == SDLK_RETURN ||
					event.key.keysym.sym == SDLK_ESCAPE ){
					
					frameCount = FPS * 4;	
				}
			}
		}	

		//Fill the background with white color	
		SDL_FillRect( screen, &screen->clip_rect,
			SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
		//fade in and fade out animation	
		if( frameCount <= 60 && alpha <= SDL_ALPHA_OPAQUE )
			alpha += SDL_ALPHA_OPAQUE / 60;

		else if( frameCount >= 180 && alpha >= SDL_ALPHA_TRANSPARENT )
			alpha -= SDL_ALPHA_OPAQUE / 60;
		
		//set the alpha
		SDL_SetAlpha( logo, SDL_SRCALPHA, alpha );

		applySurface( ( SCREEN_WIDTH - logo->w )/2, ( SCREEN_HEIGHT - logo->h )/2,
			logo, screen );

		if( SDL_Flip( screen ) == -1 )	exit( 1 );

		if( fps.getTicks() < 1000 / FPS )
			SDL_Delay( ( 1000 / FPS ) - fps.getTicks() );

	}while( ++frameCount < FPS * 4 );

	SDL_FreeSurface( logo );
}
 
int main ( int argc, char* argv[] )
{
	if( init() == false ){
		perror( "Initialization faled" );
		return 1;
	}

	gameStartScreen();

	if( gameMenu( screen ) == 1 )	return 1;
	
	//Clean surface and something else
	cleanUp();

	return 0;
}

