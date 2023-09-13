#include<stdlib.h>
#include<stdbool.h>

#include<stdint.h>
#include<stdio.h>

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t bright;
} pixelColor;

// video buffer
typedef struct {
	unsigned int x;
	unsigned int y;
	pixelColor **buffer;//
} screenBuffer;

// checks if malloc returned null
// false no error
// true error
bool checkMalloc(void *prt){
	if(prt == NULL){
		return true;
	}
	else{
		return false;
	}
}

// sets the pixel to zero
void screenZeroPixel(pixelColor *pixel){
	pixel->red=0;
	pixel->blue=0;
	pixel->green=0;
	pixel->bright=0;
}
// sets the pixel to one
void screenOnePixel(pixelColor *pixel){
	pixel->red=7;
	pixel->blue=7;
	pixel->green=7;
	pixel->bright=7;
}

// genarates a new screen buffer struct and alacates 
screenBuffer *genScreenBuffer(unsigned int width,unsigned int hight){
	screenBuffer *screen = malloc(sizeof(screenBuffer));
	screen->x = width;
	screen->y = hight;
	
	// y first 
	screen->buffer = malloc(sizeof(pixelColor *)*screen->y);
	if(checkMalloc(screen->buffer)){return NULL;}
	
	// then x
	for(unsigned int y=0;y<screen->y;y+=1){
		screen->buffer[y] = malloc(sizeof(pixelColor)*screen->x);
		for(unsigned int x=0;x<screen->x;x+=1){
			screenOnePixel(&(screen->buffer[y][x]));	
		}
		if(checkMalloc(screen->buffer[y])){return NULL;}
	}
	return screen;
}

// free function for the screen
void freeScreenBuffer(screenBuffer **screen){ // ** so we can null the pointer
	for(unsigned int i=0;i<(*screen)->y;i+=1){
		free((*screen)->buffer[i]);
		(*screen)->buffer[i] = NULL; // not realy needed but id rather be safe
	}
	free((*screen)->buffer);
	(*screen)->buffer = NULL;	
	free((*screen));
	(*screen) = NULL;
}

