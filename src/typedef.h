#pragma once
#include <SDL2/SDL.h>

// ---------------------------------- Type Definitions ---------------------------------- //

// Boolean type
typedef int bool;
#define true 1
#define false 0

// Struct to render Text Messages
typedef struct {
    // Message 01
    SDL_Texture *message1;
    SDL_Rect message1_Rect;
    // Message 02
    SDL_Texture *message2;
    SDL_Rect message2_Rect;
} Scene;

// Text Render Methods for text messages
typedef enum {
    TextRenderSolid,
    TextRenderShaded,
    TextRenderBlended
} TextRenderMethod;

// Text Render Type for text messages
typedef enum {
    RENDER_LATIN1,
    RENDER_UTF8,
    RENDER_UNICODE
} RenderType;