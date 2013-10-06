
#include "gameMenu.h"

int gameMenu( SDL_Surface* screen )
{
	bool quit = false;
	SDL_Event event;
	short int frameCount = 0;
	Timer fps;
	
	SDL_Surface* logo = loadImage( "./game/img/menuLogo.png" );
	if( logo == NULL )	return 1;

	do{
		//Fadein the background
			
		//Refresh screen
		if( SDL_Flip( screen ) == -1 )	return 1;

	}while( ++frameCount <= FPS * 1.5 );

	//Main loop
	while( quit == false ){
		fps.start();

		//handle events
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT )	quit = true;
		}

		//drawing	
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xB3, 0x5C ) );

		applySurface( ( SCREEN_WIDTH - logo->w ) / 2, 100,
			logo, screen );
	
		//Refresh screen	
		if( SDL_Flip( screen ) == -1 )	return 1;

		//Keep the frame rate
		if( fps.getTicks() < 1000 / FPS )	
			SDL_Delay( ( 1000 / FPS ) - fps.getTicks() );
	}

	SDL_FreeSurface( logo );
	
	return 0;
}
