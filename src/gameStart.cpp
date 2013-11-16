/*
	gameStart.cpp
*/

#include "gameStart.h"

using namespace std;
bool gameStartScreen( SDL_Renderer* renderer )
{
	SDL_Event event;
	SDL_Texture* logo;
	logo = loadTexture( "./game/img/logo.bmp", renderer ); 
	if( logo == NULL )	return false;

	Timer fps;
	short int frameCount = 0;
	short int alpha = SDL_ALPHA_TRANSPARENT;
	SDL_Rect pos;
	pos.x = ( SCREEN_WIDTH - 640 )/2;
	pos.y = ( SCREEN_HEIGHT - 360 )/2;
	pos.w = 640;	
	pos.h = 360;	

	do{
		fps.start();
		
		//Event handle for skip
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_KEYDOWN ){
				if( event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_ESCAPE ){
					frameCount = FPS * 4;        
				}
			}
		}        

		//Fade in and fade out animation        
		if( frameCount <= FPS && alpha <= SDL_ALPHA_OPAQUE )
			alpha += SDL_ALPHA_OPAQUE / FPS;
		else if( frameCount >= 3*FPS && alpha >= SDL_ALPHA_TRANSPARENT )
			alpha -= SDL_ALPHA_OPAQUE / FPS;
		
		//Set the alpha
		SDL_SetTextureAlphaMod( logo, alpha );

		//Fill the background with white color        
		SDL_RenderClear( renderer );

		//Draw logo
		SDL_RenderCopy( renderer, logo, NULL, &pos );

		//Update window
		SDL_RenderPresent( renderer );

		if( fps.getTicks() < 1000 / FPS )
			SDL_Delay( ( 1000 / FPS ) - fps.getTicks() );

	}while( ++frameCount < FPS * 4 );

	SDL_DestroyTexture( logo );
	logo = NULL;

	return true;
}

