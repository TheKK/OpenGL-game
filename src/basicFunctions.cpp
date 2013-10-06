
#include "basicFunctions.h"

void applySurface ( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
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
