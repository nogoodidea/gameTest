#include<SDL2/SDL.h>
#include<SDL2/SDL_video.h>
#include<SDL2/SDL_image.h>

#include<stdbool.h>
#include<stdint.h>

#include "screen.h" // all common functions for screen buffer handling


// core SDL stuff
SDL_Window *window = NULL;
SDL_Surface  *surf = NULL;
SDL_Renderer *rend = NULL;
screenBuffer *screen = NULL;
SDL_Texture *textures = NULL;



// char hight/width
#define TEXT_HIGHT 10
#define TEXT_WIDTH 10

// text on the screen
#define SCREEN_TEXT_HIGHT 20
#define SCREEN_TEXT_WIDTH 20
// texture path
#define TEXT_PATH "textures/glyphs.png"

//render int setup the render
screenBuffer *renderInit(){
	// sdl start/error check block
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		fprintf(stderr,"ERROR: SDL failed to init.\n %s",SDL_GetError());
		return screen;
	}
	// get screen size
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	// make a window
	window = SDL_CreateWindow("gameTest",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,display.w,display.h,SDL_WINDOW_FULLSCREEN|SDL_WINDOW_SHOWN);
	if(window == NULL){
		fprintf(stderr,"ERROR: SDL failed to make a window.\n %s",SDL_GetError());
		return screen;
	}

	rend = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(rend == NULL){
		fprintf(stderr,"ERROR: SDL failed to make a render.\n %s",SDL_GetError());
		return screen;
	}

	// temp var for surface
	SDL_Surface *charSurf = IMG_Load(TEXT_PATH);
	if(charSurf==NULL){
		fprintf(stderr,"ERROR: SDL_img failed to load texture: %s.\n %s",TEXT_PATH,IMG_GetError());
	}
	
	textures = SDL_CreateTextureFromSurface(rend,charSurf);
	
	if(textures == NULL){
		fprintf(stderr,"ERROR SDL failed to convert image surfrace into a texture.\n %s",SDL_GetError());
	}
	SDL_FreeSurface(charSurf);
	//render color
	SDL_SetRenderDrawColor(rend,0,0,0,SDL_ALPHA_OPAQUE);

	// sdl is up now make the screen buffer
	int w,h;
	SDL_GetWindowSize(window,&w,&h);
	screen = genScreenBuffer(w/SCREEN_TEXT_WIDTH,h/SCREEN_TEXT_HIGHT);
	// now that we got a buffer return it
	return screen; 
}


// render the screen
void renderFrame(){
	// does stuff with the screen
	SDL_RenderClear(rend);

	for(unsigned int y=0;y<screen->y;y+=1){
		for(unsigned int x=0;x<screen->x;x+=1){
			// texture offset
			if(screen->buffer[y][x].bright>0){
				SDL_SetTextureColorMod(textures,(screen->buffer[y][x].red/7)*255,(screen->buffer[y][x].green/7)*255,(screen->buffer[y][x].blue/7)*255); // change the color
				// sets the text pos
				SDL_Rect screenPos = {SCREEN_TEXT_WIDTH*x,SCREEN_TEXT_HIGHT*y,SCREEN_TEXT_WIDTH,SCREEN_TEXT_HIGHT}; // position of the texture on the screen
				
				SDL_Rect textPos = {TEXT_WIDTH*(screen->buffer[y][x].bright-1),0,TEXT_WIDTH,TEXT_HIGHT}; // position of the texture in the texture file	
				
				SDL_RenderCopy(rend,textures,&textPos,&screenPos);
			}
		}
	}
	SDL_RenderPresent(rend);// update screen
}


// check if the render should stop
bool renderCheckStop(){
	if(window == NULL){
		return true; // if the window is gone stop rendering
	}
	return false;
}	

// shutdown the render
void renderStop(){
	SDL_DestroyTexture(textures);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
