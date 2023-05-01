#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
extern char *string_msg1, *string_msg2; 

// -------------------------------------- Functions ------------------------------------- //

// Use with actions that should be executed each second
bool ticker_second(unsigned int lastTime, unsigned int currentTime);

// Use with actions that should be executed 60 times per second
bool ticker_fps(unsigned int lastTime, unsigned int currentTime);

// Load rom into memory
void load_rom(char* filename, unsigned char *mem, unsigned int mem_size);

// Print Frames and Cycles per second on screen
void showCPS( long long unsigned int n);
void showFPS( int number );