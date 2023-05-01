#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// SDL Font
extern char *string_msg1, *string_msg2;
// SDL Video
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;

// ---------------------------------- Global Variables ---------------------------------- //

// Display
Scene scene;
unsigned char display_SCREEN_WIDTH_X;
unsigned char display_SCREEN_HEIGHT_Y;
unsigned char display_SCALE;
unsigned int  display_pixel_ON_color;
unsigned int  display_pixel_OFF_color;

// Display Array
unsigned int pixels[2048];

// -------------------------------------- Functions ------------------------------------- //
void display_init();
bool display_draw(unsigned int frame, Scene *scene);
void SDL_close();