#include<SDL2/SDL.h>
#include<SDL2/SDL_video.h>
#include<SDL2/SDL_image.h>

#include<stdbool.h>
#include<stdint.h>

#include "screen.h" // all common functions for screen buffer handling

const char *ASCII_PATH[]={"1.png","2.png","3.png","4.png","5.png","6.png","7.png"};

// core SDL stuff
SDL_Window *window = NULL;
SDL_Surface  *surf = NULL;
SDL_Renderer *rend = NULL;
screenBuffer *screen = NULL;
SDL_Surface **ASCII_SURF;

// char hight/width
#define TEXT_HIGHT 30
#define TEXT_WIDTH 30

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
	SDL_CreateWindowAndRenderer(display.w,display.h,SDL_WINDOW_FULLSCREEN,&window,&rend);
	if(window == NULL){
		fprintf(stderr,"ERROR: SDL failed to make a window.\n %s",SDL_GetError());
		return screen;
	}

	rend = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
	// open font file
	//makes the main textures from the font
	ASCII_SURF = malloc(sizeof(SDL_Surface *)*7);
	for(unsigned int x = 0;x<7;x+=1){
		ASCII_SURF[x] = IMG_Load(ASCII_PATH[x]);
	}
	//render color
	SDL_SetRenderDrawColor(rend,0,0,0,SDL_ALPHA_OPAQUE);
	
	// sdl is up now make the screen buffer
	int w,h;
	SDL_GetWindowSize(window,&w,&h);
	screen = genScreenBuffer(w/TEXT_WIDTH,h/TEXT_HIGHT);
	// now that we got a buffer return it
	return screen; 
}


// render the screen
void renderFrame(){
	// does stuff with the screen
	SDL_RenderClear(rend);

	//SDL_RenderFillRect(rend,NULL);
	SDL_Rect textPos = {0,0,0,0};

	for(unsigned int y=0;y<screen->y;y+=1){
		for(unsigned int x=0;x<screen->x;x+=1){
			// texture offset
			if(screen->buffer[y][x].bright>0){
				SDL_Texture *text = SDL_CreateTextureFromSurface(rend,ASCII_SURF[(screen->buffer[y][x].bright-1)]); // gets the texture
				SDL_SetTextureColorMod(text,(screen->buffer[y][x].red/7)*255,(screen->buffer[y][x].green/7)*255,(screen->buffer[y][x].blue/7)*255); // change the color
				// sets the text pos
				textPos.x = TEXT_WIDTH*x;
				textPos.y = TEXT_HIGHT*y;
				textPos.w = TEXT_WIDTH;
				textPos.h = TEXT_HIGHT;
				
				SDL_RenderCopy(rend,text,NULL,&textPos);
				SDL_DestroyTexture(text); // remove the old texture
			}
			// colors later
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
	for(unsigned int i=0;i<7;i+=1){
		SDL_FreeSurface(ASCII_SURF[i]);// frees the surfaces
	}
	free(ASCII_SURF);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
