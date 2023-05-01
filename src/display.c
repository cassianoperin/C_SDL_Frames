#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "display.h"

void display_init()
{
	// Screen Variables
	display_SCREEN_WIDTH_X	= 64;
	display_SCREEN_HEIGHT_Y	= 32;
	display_SCALE			= 20;
	display_pixel_ON_color	= 0xFFFFFFFF;
	display_pixel_OFF_color	= 0xFF000000;

	// SDL INIT
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        SDL_Quit();
		exit(2);
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "C_SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE, SDL_WINDOW_SHOWN );
		
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_Quit();
			exit(2);
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				SDL_Quit();
				exit(2);
			} else {
				//Create texture
				texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, display_SCREEN_WIDTH_X, display_SCREEN_HEIGHT_Y);
				if( renderer == NULL )
				{
					printf( "Texture could not be created! SDL Error: %s\n", SDL_GetError() );
					SDL_Quit();
					exit(2);
				}
			}
		}
	}
};

bool display_draw(unsigned int frame, Scene *scene)
{
	//Initialization flag
	bool success = true;

	// Initialization - Clean pixels array
	for ( int i = 0 ; i < (int)( sizeof(pixels) / sizeof(pixels[0])) ; i++ ) {
			pixels[i] = display_pixel_OFF_color;
	}

	// Test turn on some pixels
	pixels[frame] = display_pixel_ON_color;
	pixels[2048-frame] = display_pixel_ON_color;

    /* Clear the background to background color */
    // SDL_SetRenderDrawColor(renderer, 0x33, 0x00, 0x40, 0xFF);
    SDL_RenderClear(renderer);

    // Update game texture
	SDL_UpdateTexture(texture, NULL, pixels, display_SCREEN_WIDTH_X * sizeof(uint32_t));
	SDL_RenderCopy(renderer, texture, NULL, NULL);

    // ----- Update Text Messages ----- //
	// Message Slot 1
	if ( string_msg1 != NULL && strcmp( string_msg1, "") != 0 ) {
		    SDL_RenderCopy(renderer, scene->message1, NULL, &scene->message1_Rect);
	}
	// Message Slot 2
	if ( string_msg2 != NULL && strcmp( string_msg2, "") != 0 ) {
    	SDL_RenderCopy(renderer, scene->message2, NULL, &scene->message2_Rect);
	}

    // Update the Screen
	SDL_RenderPresent(renderer);

	return success;
}

void SDL_close()
{
	// Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

    // Destroy font
    TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}