# C SDL2: Frame Based

Basic implementation of SDL, SDL_TTF anc C for emulators, optimized to execute all operations between the 50 or 60 frames of the second and sleep the remaing of the time.

It willavoid unnecessary use of cpu in the infinite loop to measure time each cycle.

**Window with game running (white squares) and messages being showed over the screen** |
:-------------------------:|
<img alt="C_SDL_TTF" src="https://github.com/cassianoperin/C_SDL/blob/main/src/Images/C_SDL_TTF.png">  |

## Docs

### SDL2-Starter

https://github.com/codingwithjulio/sdl2-starter

### MACOS SDL2 / SDL2_Image instructions

- Install SDL2 Framework:

https://www.libsdl.org/

- Install SDL2_Image (dmg) from:

http://www.libsdl.org/projects/SDL_image/

- Install SDL_TTF:

https://www.libsdl.org/projects/SDL_ttf/release/


All to /Library/Frameworks

Link the SDL_Image.h inside SDL2:

`cd /Library/Frameworks/SDL2.framework/Headers`

`ln -s /Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h`
