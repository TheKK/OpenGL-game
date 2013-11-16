/*
basicFunctions.cpp
*/

#include "basicFunctions.h"

SDL_Texture* loadTexture ( string fileName, SDL_Renderer* renderer )
{
	//Create two surface for oringinal and optimized image
	SDL_Surface* loaded = NULL;
	SDL_Texture* tex = NULL;

	//Load original picture	
	loaded = SDL_LoadBMP( fileName.c_str() ); 
	if( loaded == NULL ){
		cout << "Error while loading:" << fileName << " Error: " << SDL_GetError() << endl;
		tex = NULL;
	}
	else{
		//Set color key
		SDL_SetColorKey( loaded, SDL_TRUE, SDL_MapRGB( loaded->format, 0X00, 0XFF, 0XFF ) );
		
		//Covert surface into texture
		tex = SDL_CreateTextureFromSurface( renderer, loaded );
		
		SDL_FreeSurface( loaded );
		loaded = NULL;
	}

	return tex;
}
