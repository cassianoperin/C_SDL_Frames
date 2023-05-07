#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "main.h"
#include "lib.h"
#include "display.h"
#include "font.h"

int main( int argc, char* args[] )
{

	// ------------ Constants ------------ //
	const int   pal_freq   = 60;					// NTSC: 60hz, PAL: 50HZ
	const float msPerFrame =  1 / (float) pal_freq; // 16 ms per frame (0.016667) on NTSC, 20ms (0,02) on PAL

	// ------------ Variables ------------ //
	// SDL Event handler
	SDL_Event event;

	// Counters
	unsigned int cycle = 0;
	unsigned int frame = 0;

	// Main loop flag
	bool quit = false;

	// Timing
	uint64_t perfFrequency        = SDL_GetPerformanceFrequency();		// Platform independent frequency
	uint64_t msPerFrameInt        = msPerFrame * perfFrequency;			// Time per frame in the deltas format
	uint64_t timeFrameStartCount  = 0;									// Start of frame counter
	uint64_t timeFrameLastCount   = SDL_GetPerformanceCounter();		// End of frame counter
	uint64_t timeFrameDuration    = 0;									// Duration of a frame
	uint64_t timeFrameDurationSum = 0;									// Sum of all frames into a second
	uint64_t timeDeltaOperations  = 0;									// Time spent into the operations (part 1)
	uint64_t timeDeltaSleep       = 0;									// Time spent sleeping (part 2)
	int      timeFrameSleep       = 0;									// Time in ms to sleep after all frame executions
	// FPS
	uint64_t timeSecondStart      = 0;									// Measurement of time spent on last frame
	uint64_t timeSecondLast       = 0;									// Measurement of time spent on last frame

	// On screen messages
	// string_msg1 = malloc( length + 30 );
	string_msg1 = (char *)malloc(sizeof(char) * (30 + 1));
	string_msg2 = (char *)malloc(sizeof(char) * (9 + 1));



	// Timing debug
	bool debug_timing = false;


	// -------------------------- SDL Init -------------------------- //
	display_init();

	// ------------------------- Font Init -------------------------- //
	font_init(renderer);

	// Seconds Counter
	timeSecondStart = SDL_GetPerformanceCounter();

	// ----------------------- Infinite Loop  ----------------------- //
	while( !quit )
	{
		// Timing: Start frame
		timeFrameStartCount = SDL_GetPerformanceCounter();

		// --------------------------- P1: START OF FRAME OPERATIONS  --------------------------- //

		// Handle events on queue
			while( SDL_PollEvent( &event ) != 0 )
			{
				if (event.type == SDL_KEYDOWN)
				{
					const char* key = SDL_GetKeyName(event.key.keysym.sym);
					if (strcmp(key,"Q") == 0 || strcmp(key,"Escape") == 0)
					{
						quit = true;
					}
				}
				else if (event.type == SDL_QUIT)
				{
					quit = true;
				}

			}

			// Draw screen (game and text messages)
			display_draw(frame, &scene);

		// ---------------------------- P1: END OF FRAME OPERATIONS  ---------------------------- //


		// ------------------- P2: START OF FRAME OPERATIONS TIME MEASUREMENT  ------------------ //
		// Timing: Update timeFrameLastCount adding the time spent on operations
		timeFrameLastCount = SDL_GetPerformanceCounter();
		timeDeltaOperations = timeFrameLastCount - timeFrameStartCount;
		// Timing: Transform operations delta into seconds view
		float timeFrameSecondsOperations = timeDeltaOperations / (float) perfFrequency;

		// Debug Timing
		if ( debug_timing ) {
			printf("Frame: %02d OPERATIONS:\tperfFrequency: %llu\ttimeFrameStartCount: %llu\ttimeDeltaOperations: %llu\ttimeFrameDuration: %llu\ttimeFrameSecondsOperations: %fs\tmsPerFrame:%fms\n",
				frame, perfFrequency, timeFrameStartCount, timeDeltaOperations, timeFrameLastCount, timeFrameSecondsOperations, msPerFrame );
		}
		
		
		// ------------------------------ P3: START OF FRAME SLEEP  ----------------------------- //

		// if we have time remaining on this frame, sleep
		if ( timeFrameSecondsOperations <= msPerFrame ) {

			// Get the integer part of the remaining time
			timeFrameSleep = 1000 * (msPerFrame - timeFrameSecondsOperations);
			
			// I've reduced 2 ms from the sleep due to its imprecision, to avoid sleep more than the time of the frame
			// and later sleep more with fine adjustment
			if ( timeFrameSleep > 2 ) {
				SDL_Delay(timeFrameSleep - 2);

				// Count the exact ammount of time spent for the sleep function	
				uint64_t timeFrameSleepCount = SDL_GetPerformanceCounter();
				timeDeltaSleep = timeFrameSleepCount - timeFrameLastCount;
				if ( debug_timing ) {
					printf("SLEEP:\t\ttimeFrameSleep: %dms\ttimeDeltaSleep(real time spent on sleep): %llu\tTotal frame time: %llu\n",
						timeFrameSleep-2, timeDeltaSleep, timeDeltaOperations + timeDeltaSleep);
				}
			} else {
				if ( debug_timing ) {
					printf("SLEEP:\t\tNo time added\n");
				}
			}

			// If entered here, update the last frame count
			timeFrameLastCount = SDL_GetPerformanceCounter();
		}
		
		// Sum the time spent in operation + sleep to have the total cycle time
		timeFrameDuration = timeDeltaOperations + timeDeltaSleep;


		// ------------------------------ P4: START OF FINE SLEEP  ------------------------------ //
		while (timeFrameDuration < msPerFrameInt ) {
			timeFrameStartCount = SDL_GetPerformanceCounter();
			timeDeltaOperations = timeFrameStartCount - timeFrameLastCount;
			timeFrameDuration += timeDeltaOperations;
			// If entered here, update the last frame count
			timeFrameLastCount = timeFrameStartCount;

			// It will generate a LOT of logs, take care
			// if ( debug_timing ) {
			// 	// printf("FINE: Loop to spent cycle %d time: %llu\t\tTotal frame time: %llu\n", counterFrames, timeDeltaOperations, timeFrameDuration);
			// }

			// If entered here, update the cycle counter
			cycle ++;
		}

		// Debug Timing
		if ( debug_timing ) {
			printf("Final frame time: %llu\n\n", timeFrameDuration);
		}

		// Update the timeFrameDuration with the timing of the last cycle
		timeFrameDurationSum += timeFrameDuration;

		// Increment frame counter
		frame ++;

		// Increment CPU Cycle
		cycle++;

		// Seconds Counter
		timeSecondLast = SDL_GetPerformanceCounter();

		// ------------------------------- P5: START OF SECONDs COUNTER  ------------------------------- //
		if ( timeSecondLast - timeSecondStart > 1000000000 ){ 

			// Window Title Message update
			char title_msg[80];
			sprintf(title_msg, "Cycles per sec.: %d\t\tFPS: %d\t\tFreq: %dhz        ms: %llu", cycle, frame, pal_freq, timeFrameDurationSum);
			SDL_SetWindowTitle(window, title_msg);

			// -------- Message slot 1 -------- //
			showCPS(cycle);
			font_update_msg1(renderer);

			// -------- Message slot 2 -------- //
			showFPS(frame);
			font_update_msg2(renderer);

			if ( debug_timing ) {
				printf("\nSecond counter effective time: %llu\n\n", timeSecondLast - timeSecondStart);
			}

			// Reset counters
			cycle = 0;
			frame = 0;
			timeFrameDurationSum = 0;
			timeSecondStart = SDL_GetPerformanceCounter(); // Reset second counter
		}
	}

	//Free resources and close SDL
	SDL_close();


	free(string_msg1);
	free(string_msg2);


	return 0;
}