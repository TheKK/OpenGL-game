/*
main.cpp
*/

#include "basicFunctions.h"
#include "gameStart.h"

using namespace std;

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;

bool init ()
{
	//Init SDL libery
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )	return false;

	//Set texture filtering to linear 
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ) ){
		cout << "Warning: linear texture filtering not enabled" << endl;
	}

	//Create window
	mainWindow = SDL_CreateWindow( 
			"SNAKE",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
			);	
	if( mainWindow == NULL ){
		cout << "Could not create SDL window! error: " << SDL_GetError() << endl;
		return false;
	}

	//Create renderer
	mainRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED );
	if( mainRenderer == NULL ){
		cout << "Could not create SDL renderer! error: " << SDL_GetError() << endl;
		return false;
	}
	else{
		//Set renderer draw color
		SDL_SetRenderDrawColor( mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	}

	//Init random seed
	srand( time( NULL ) );

	return true;
}

void cleanUp()
{
	//Free up mainWindow
	SDL_DestroyWindow( mainWindow );
	mainWindow = NULL;
	
	//Free up mainRenderer
	SDL_DestroyRenderer( mainRenderer );
	mainRenderer = NULL;
	
	//Exit SDL subsystem
	SDL_Quit();
}

int main ( int argc, char* argv[] )
{
	if( init() == false ){
		perror( "Initialization faled" );
		cleanUp();
		return 1;
	}

	gameStartScreen( mainRenderer );

	//Clean surface and something else
	cleanUp();

	return 0;
}

