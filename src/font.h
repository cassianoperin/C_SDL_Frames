#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
extern TTF_Font *font;
extern SDL_Surface *text;
extern Scene scene;
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
extern unsigned char display_SCALE;

// ---------------------------------- Global Variables ---------------------------------- //
SDL_Color font_foreground_color;
SDL_Color font_background_color;
TextRenderMethod rendermethod;
RenderType rendertype;
int ptsize;
int renderstyle;
int outline;
int hinting;
int kerning;
char *string_msg1, *string_msg2, *font_path;

// -------------------------------------- Functions ------------------------------------- //
bool font_init(SDL_Renderer* renderer);
void font_update_msg1(SDL_Renderer* renderer);
void font_update_msg2(SDL_Renderer* renderer);