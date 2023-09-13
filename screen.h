#ifndef SCREEN_GAME_TEST_H
#define SCREEN_GAME_TEST_H

#include<stdint.h>


//
typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t bright;
} pixelColor;


//holds common data structures and functions needed for packing and unpacking data from the render and the raytraser
typedef struct screenBuffer_S{
	unsigned int x;
	unsigned int y;
	pixelColor **buffer;//
} screenBuffer;


// makes a new screen buffer
screenBuffer *genScreenBuffer(unsigned int width,unsigned int hight);

// does the converse and frees the screen buffer
void freeScreenBuffer(screenBuffer **screen);

// the screen buffer has 16 bits per screen section
// the first 4 are for the bightness (the ASCII char used)
// the next 4 are for RED
// the next 4 are for GREEN
// the next 4 are for BLUE
//uint16_t encodeScreenData(int light,int red, int green,int blue);

#endif //SCREEN_GAME_TEST_H
