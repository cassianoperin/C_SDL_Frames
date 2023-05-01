#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

// ---------------------------- Tickers ---------------------------- //

// Use with actions that should be executed each second
bool ticker_second(unsigned int lastTime, unsigned int currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second
	if (currentTime > lastTime + (1000)) {
		success = true;
	}
	
	return success;
}

// Use with actions that should be executed 60 times per second
bool ticker_fps(unsigned int lastTime, unsigned int currentTime)
{

	unsigned int FPS  = 60;

	//Initialization flag
	bool success = false;


	// Check if it passed one second / FPS
	if (currentTime > lastTime + (1000/FPS)) {
	// if (currentTime > lastTime + (16)) {
		success = true;
	}

	return success;
}

// --------------------------- File load --------------------------- //

// Load rom into memory
void load_rom(char* filename, unsigned char *mem, unsigned int mem_size)
{
	int PC = 0x200;

	// ----------------- Read File ----------------- //

	FILE* rom = fopen(filename, "rb");
	if (!rom) {
		fprintf(stderr, "Unable to open file '%s'!\n", filename);
		exit(1);
	}
	fread(&mem[PC], 1, mem_size - PC, rom);
	fclose(rom);

	// Print Memory
	for(int i = 0; i < mem_size; i++)
		printf("%02X ", mem[i]);
	
	printf("\n\n");
}


// Show Cycles Per Second
void showCPS( long long unsigned int number) 
{
	// Variables
    char nstring[30];
	int str_size, ptr, i , j = 0;

	// Allocate memory for the pointer
	int length = snprintf( NULL, 0, "%llu", number );
	string_msg1 = malloc( length + 30 );

	// Convert the integer into a string
    sprintf(nstring, "%llu", number);
	// Size of string
	str_size = strlen(nstring);

	// Label
	strcat(string_msg1, "Cycles per second: ");

	// Work with First 3 digits
	ptr = str_size % 3;
	if (ptr) {
		 // Print first digits before point
		for ( i = 0 ; i < ptr ; i++ ) {      
			// printf("%c", nstring[i]); 
			strncat(string_msg1, &nstring[i], 1);
		}

		// Just print the point if number is bigguer than 3
		if ( str_size > 3) {
			// printf(".");
			strcat(string_msg1, ".");
		}
	}


	for ( i = ptr ; i < str_size ; i++ ) {      // print the rest inserting points
		// printf("%c", nstring[i]);
		strncat(string_msg1, &nstring[i], 1);
		j++;
		if ( j % 3 == 0 ) {
			if( i < (str_size-1) ) {
				strcat(string_msg1, ".");
				// printf(".");
			} 
		}
	}

	// printf("\n");

}

// Show Frames Per Second
void showFPS( int number ) 
{
	int length = snprintf( NULL, 0, "%d", number );
	string_msg2 = malloc( length + 10);

	char temp[20];
	char fps_count[10];
	char fps_text[6] = "FPS: ";
	snprintf( fps_count, length + 1, "%d", number );


	memcpy(temp,fps_count,sizeof(fps_count));
	memcpy(fps_count,fps_text,strlen(fps_text));
	memcpy(fps_count+strlen(fps_text),temp,strlen(temp)+1);


	strcpy(string_msg2, fps_count);
}

