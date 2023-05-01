#pragma once

// --------------------------------- External Variables --------------------------------- //
extern char *string_msg1, *string_msg2;

// ---------------------------------- Global Variables ---------------------------------- //
// SDL Video
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

// SDL Font
TTF_Font *font;
SDL_Surface *text;