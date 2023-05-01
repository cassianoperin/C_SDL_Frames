#include "font.h"

bool font_init(SDL_Renderer* renderer){

    // ------------------ Variables ------------------ //

    // Font Path
    // font_path = "../../src/Fonts/src/Fonts/Lazy.ttf";
    // font_path = "../../src/Fonts/src/Fonts/Zack and Sarah.ttf";
    // font_path = "../../src/Fonts/src/Fonts/39335_UniversCondensed.ttf";
    // font_path = "../../src/Fonts/src/Fonts/07558_CenturyGothic.ttf";
    // font_path = "../../src/Fonts/src/Fonts/16020_FUTURAM.ttf";
    // font_path = "../../src/Fonts/16020_FUTURAM.ttf";
    font_path = "Fonts/16020_FUTURAM.ttf";

    // Colors
    // font_foreground_color = { 0x87, 0xCE, 0xFA, 0 }; // Blue
    font_foreground_color.a = 0;
    font_foreground_color.r = 0x87;
    font_foreground_color.g = 0xCE;
    font_foreground_color.b = 0xFA;

	// font_background_color = { 0xFF, 0xFF, 0xFF, 1 }; // White
    font_background_color.a = 1;
    font_background_color.r = 0xFF;
    font_background_color.g = 0xFF;
    font_background_color.b = 0xFF;

    // Font Point Size
    ptsize = 16;

    // Render Method
    // rendermethod = TextRenderSolid;
    // rendermethod = TextRenderShaded;
    rendermethod = TextRenderBlended;

    // Render Style
    renderstyle = TTF_STYLE_NORMAL;
    // renderstyle |= TTF_STYLE_BOLD;
    // renderstyle |= TTF_STYLE_ITALIC;
    // renderstyle |= TTF_STYLE_UNDERLINE;
    // renderstyle |= TTF_STYLE_STRIKETHROUGH;

    // Render Type
    // Used in Render Method
    // rendertype = RENDER_LATIN1;
    // rendertype = RENDER_UTF8;
    rendertype = RENDER_UNICODE;

    // Hinting
    // hinting = TTF_HINTING_NORMAL;
    // hinting = TTF_HINTING_LIGHT;
    // hinting = TTF_HINTING_MONO;
    hinting = TTF_HINTING_NONE;

    // Kerning
    kerning = 1;
    // kerning = 0;

    // Outline
    outline = 0;

    // ---------- Initialize the TTF library --------- //

    /* Initialize the TTF library */
    if (TTF_Init() < 0) {
        SDL_Log("Couldn't initialize TTF: %s\n",SDL_GetError());
        SDL_Quit();
		exit(2);
    }

    font = TTF_OpenFont(font_path, ptsize);
    if (font == NULL) {
        SDL_Log("Couldn't load %d pt font from %s: %s\n",
                    ptsize, font_path, SDL_GetError());
        SDL_Quit();
		exit(2);
    }

    // Configuration
    TTF_SetFontStyle(font, renderstyle);
    TTF_SetFontOutline(font, outline);
    TTF_SetFontKerning(font, kerning);
    TTF_SetFontHinting(font, hinting);

    return(0);
}

void font_update_msg1(SDL_Renderer* renderer){

    // Initial message
    // SDL_snprintf(string_msg1, sizeof(string_msg1), "OOOOP MESSAGE!");
    // string_msg1 = "FIRST SLOT MESSAGE";

    if ( string_msg1 != NULL && strcmp( string_msg1, "") != 0  ) {

        // Font Color
        font_foreground_color.a = 0;
        font_foreground_color.r = 0xFF;
        font_foreground_color.g = 0x00;
        font_foreground_color.b = 0x00;

        text = TTF_RenderText_Blended(font, string_msg1, font_foreground_color);

        switch (rendertype) {
        case RENDER_LATIN1:
            switch (rendermethod) {
            case TextRenderSolid:
                text = TTF_RenderText_Solid(font, string_msg1, font_foreground_color);
                break;
            case TextRenderShaded:
                text = TTF_RenderText_Shaded(font, string_msg1, font_foreground_color, font_background_color);
                break;
            case TextRenderBlended:
                text = TTF_RenderText_Blended(font, string_msg1, font_foreground_color);
                break;
            }
            break;

        case RENDER_UTF8:
            switch (rendermethod) {
            case TextRenderSolid:
                text = TTF_RenderUTF8_Solid(font, string_msg1, font_foreground_color);
                break;
            case TextRenderShaded:
                text = TTF_RenderUTF8_Shaded(font, string_msg1, font_foreground_color, font_background_color);
                break;
            case TextRenderBlended:
                text = TTF_RenderUTF8_Blended(font, string_msg1, font_foreground_color);
                break;
            }
            break;

        case RENDER_UNICODE: {
            Uint16 *unicode_text = SDL_iconv_utf8_ucs2(string_msg1);
            switch (rendermethod) {
            case TextRenderSolid:
                text = TTF_RenderUNICODE_Solid(font, unicode_text, font_foreground_color);
                break;
            case TextRenderShaded:
                text = TTF_RenderUNICODE_Shaded(font, unicode_text, font_foreground_color, font_background_color);
                break;
            case TextRenderBlended:
                text = TTF_RenderUNICODE_Blended(font, unicode_text, font_foreground_color);
                break;
            }
            SDL_free(unicode_text);
            }

        break;
        }

        if (text == NULL) {
            SDL_Log("Couldn't render text: %s\n", SDL_GetError());
            TTF_CloseFont(font);
            exit(2);
        }
            
        // Draw Message 1
        if (text != NULL) {
            scene.message1_Rect.x = 10;
            scene.message1_Rect.y = 10;
            scene.message1_Rect.w = text->w;
            scene.message1_Rect.h = text->h;
            scene.message1 = SDL_CreateTextureFromSurface(renderer, text);
            SDL_FreeSurface(text);
        } else { // text == NULL
            SDL_Log("Draw Message 1: Couldn't render text: %s\n", SDL_GetError());
            TTF_CloseFont(font);
            SDL_Quit();
            exit(2);
        }
    }
}


void font_update_msg2(SDL_Renderer* renderer){

    // Initial message
    // string_msg2 = "SECOND SLOT MESSAGE";

    if ( string_msg2 != NULL && strcmp( string_msg2, "") != 0  ) {

        // Font Color
        font_foreground_color.a = 0;
        font_foreground_color.r = 0x87;
        font_foreground_color.g = 0xCE;
        font_foreground_color.b = 0xFA;

        text = TTF_RenderText_Blended(font, string_msg2, font_foreground_color);

        switch (rendertype) {
            case RENDER_LATIN1:
                switch (rendermethod) {
                case TextRenderSolid:
                    text = TTF_RenderText_Solid(font, string_msg2, font_foreground_color);
                    break;
                case TextRenderShaded:
                    text = TTF_RenderText_Shaded(font, string_msg2, font_foreground_color, font_background_color);
                    break;
                case TextRenderBlended:
                    text = TTF_RenderText_Blended(font, string_msg2, font_foreground_color);
                    break;
                }
                break;

            case RENDER_UTF8:
                switch (rendermethod) {
                case TextRenderSolid:
                    text = TTF_RenderUTF8_Solid(font, string_msg2, font_foreground_color);
                    break;
                case TextRenderShaded:
                    text = TTF_RenderUTF8_Shaded(font, string_msg2, font_foreground_color, font_background_color);
                    break;
                case TextRenderBlended:
                    text = TTF_RenderUTF8_Blended(font, string_msg2, font_foreground_color);
                    break;
                }
                break;

            case RENDER_UNICODE:
            {
                Uint16 *unicode_text = SDL_iconv_utf8_ucs2(string_msg2);
                switch (rendermethod) {
                case TextRenderSolid:
                    text = TTF_RenderUNICODE_Solid(font, unicode_text, font_foreground_color);
                    break;
                case TextRenderShaded:
                    text = TTF_RenderUNICODE_Shaded(font, unicode_text, font_foreground_color, font_background_color);
                    break;
                case TextRenderBlended:
                    text = TTF_RenderUNICODE_Blended(font, unicode_text, font_foreground_color);
                    break;
                }
                SDL_free(unicode_text);
            }
            break;
        }
        if (text == NULL) {
            SDL_Log("Couldn't render text: %s\n", SDL_GetError());
            TTF_CloseFont(font);
            exit(2);
        }
            
        // Draw Message 1
        if (text != NULL) {
            scene.message2_Rect.x = 10;
            scene.message2_Rect.y = ((display_SCREEN_HEIGHT_Y * display_SCALE) - text->h - 10);
            scene.message2_Rect.w = text->w;
            scene.message2_Rect.h = text->h;
            scene.message2 = SDL_CreateTextureFromSurface(renderer, text);
            SDL_FreeSurface(text);
        } else { // text == NULL
            SDL_Log("Draw Message 2: Couldn't render text: %s\n", SDL_GetError());
            TTF_CloseFont(font);
            SDL_Quit();
            exit(2);
        }
    }
}