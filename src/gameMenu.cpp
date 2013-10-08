
#include "gameMenu.h"
#define PI	3.1415

enum Direction{ RIGHT, LEFT, UP, DOWN };

typedef struct{
	SDL_Surface* surface;
	int x;
	int y;
	int alpha;
	int direction;
}decoration;

const short int NUMBER_OF_SQUARE = 8;

inline void decorationMove( decoration* square )
{
	switch( square->direction ){
	case RIGHT:
		if( square->x < SCREEN_WIDTH )
			square->x += 2;
		else
			square->x = -1 * square->surface->w;

		if( square->alpha == SDL_ALPHA_TRANSPARENT ){
			square->x = rand()%SCREEN_WIDTH;
			square->y = rand()%SCREEN_HEIGHT;
			square->direction = rand()%4;
		}
		
		if( square->alpha < SDL_ALPHA_OPAQUE )
			square->alpha += 1;
		else
			square->alpha = -1 * SDL_ALPHA_OPAQUE;

		break;
	case LEFT:
		if( square->x > ( -1 * square->surface->w ) )
			square->x -= 2;
		else
			square->x = SCREEN_WIDTH + square->surface->w;
		
		if( square->alpha == SDL_ALPHA_TRANSPARENT ){
			square->x = rand()%SCREEN_WIDTH;
			square->y = rand()%SCREEN_HEIGHT;
			square->direction = rand()%4;
		}
		
		if( square->alpha < SDL_ALPHA_OPAQUE )
			square->alpha += 1;
		else
			square->alpha = -1 * SDL_ALPHA_OPAQUE;

		break;
	case UP:
		if( square->y > ( -1 * square->surface->h ) )
			square->y -= 2;
		else
			square->y = SCREEN_HEIGHT;
		
		if( square->alpha == SDL_ALPHA_TRANSPARENT ){
			square->x = rand()%SCREEN_WIDTH;
			square->y = rand()%SCREEN_HEIGHT;
			square->direction = rand()%4;
		}

		if( square->alpha < SDL_ALPHA_OPAQUE )
			square->alpha += 1;
		else
			square->alpha = -1 * SDL_ALPHA_OPAQUE;

		break;
	case DOWN:
		if( square->y < SCREEN_HEIGHT )
			square->y += 2;
		else
			square->y = -1 * square->surface->h;
		
		if( square->alpha == SDL_ALPHA_TRANSPARENT ){
			square->x = rand()%SCREEN_WIDTH;
			square->y = rand()%SCREEN_HEIGHT;
			square->direction = rand()%4;
		}

		if( square->alpha < SDL_ALPHA_OPAQUE )
			square->alpha += 1;
		else
			square->alpha = -1 * SDL_ALPHA_OPAQUE;

		break;
	};
}

int gameMenu( SDL_Surface* screen )
{
	bool quit = false;
	short int frameCount = 0;
	SDL_Event event;
	Timer fps;
	
	SDL_Surface* logo = loadImage( "./game/img/menuLogo.png" );		if( logo == NULL )	return 1;
	SDL_Surface* squareSmall = loadImage( "./game/img/menuDeco1.png" );	if( squareSmall == NULL )	return 1;
	SDL_Surface* squareBig = loadImage( "./game/img/menuDeco2.png" );	if( squareBig == NULL )	return 1;
		
	decoration deco[ NUMBER_OF_SQUARE ];
	for( int i = 0; i < NUMBER_OF_SQUARE; i++ ){
		if( i%2 == 1 )
			deco[ i ].surface = squareBig;
		else
			deco[ i ].surface = squareSmall;
		deco[ i ].x = rand()%SCREEN_WIDTH;
		deco[ i ].y = rand()%SCREEN_HEIGHT;
		deco[ i ].alpha = rand()%SDL_ALPHA_OPAQUE;
		deco[ i ].direction = rand()%4;
	}


	/*Transform animation*/
	do{
		fps.start();

		//Event handle for skip
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_KEYDOWN ){
				if( event.key.keysym.sym == SDLK_RETURN ||
					event.key.keysym.sym == SDLK_ESCAPE ){
				
						frameCount = FPS * 1.5;
				}
			}
		}

		//Background
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xB3, 0x5C ) );

		//Decorations
		for( int i = 0; i < NUMBER_OF_SQUARE; i++ ){
			decorationMove( &deco[ i ] );	
			SDL_SetAlpha( deco[ i ].surface, SDL_SRCALPHA, abs( deco[ i ].alpha ) );
			applySurface( deco[ i ].x, deco[ i ].y, deco[ i ].surface, screen );
		}
			
		//Logo fadein
		SDL_SetAlpha( logo, SDL_SRCALPHA, ( frameCount * ( SDL_ALPHA_OPAQUE - 55 ) / 90 ) );
		applySurface( ( SCREEN_WIDTH - logo->w ) / 2, ( 50 + frameCount * 50 / 90 ), logo, screen );

		//Refresh screen
		if( SDL_Flip( screen ) == -1 )	return 1;
	
		//Keep frame rate
		if( ( fps.getTicks() < 1000 / FPS ) )
			SDL_Delay( ( 1000 / FPS ) - fps.getTicks() );

	}while( ++frameCount <= FPS * 1.5 );	//Keep for 1.5 seconds

	/*Main loop*/
	while( quit == false ){
		fps.start();

		//handle events
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT )	quit = true;
			if( event.type == SDL_KEYDOWN)	if( event.key.keysym.sym == SDLK_ESCAPE )	quit = true;
		}

		//Background
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xB3, 0x5C ) );

		//Decorations
		for( int i = 0; i < NUMBER_OF_SQUARE; i++ ){
			decorationMove( &deco[ i ] );	
			SDL_SetAlpha( deco[ i ].surface, SDL_SRCALPHA, abs( deco[ i ].alpha ) );
			applySurface( deco[ i ].x, deco[ i ].y, deco[ i ].surface, screen );
		}

		//Logo
		SDL_SetAlpha( logo, SDL_SRCALPHA, 200 );	
		applySurface( ( SCREEN_WIDTH - logo->w ) / 2, 100, logo, screen );
	
		//Refresh screen	
		if( SDL_Flip( screen ) == -1 )	return 1;

		//Keep the frame rate
		if( fps.getTicks() < 1000 / FPS )	
			SDL_Delay( ( 1000 / FPS ) - fps.getTicks() );
	}
	
	SDL_FreeSurface( squareSmall );
	SDL_FreeSurface( squareBig );
	SDL_FreeSurface( logo );
	
	return 0;
}
