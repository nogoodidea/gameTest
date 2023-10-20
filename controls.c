#include<SDL2/SDL.h>
#include<SDL2/SDL_keyboard.h>
#include<SDL2/SDL_video.h>

#include<stdbool.h>


#include "raytracer.h"
#include "object.h"

// input types
enum inputType {QUIT,MOVE,NONE};


// union that holds the user input/SDL events for shutdown 
typedef struct playerInput {
	enum inputType type;
	vector moves; 	
} playerInput;



// set stuff up before the main loop
bool controlsInit(){
	return true;
}

void controlsHandleInput(playerInput *input){
	static SDL_Event event;
	input->type = NONE;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			input->type = QUIT;
		}
		if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
			// exit the program on ESC
			switch(event.key.keysym.sym){
				case SDL_SCANCODE_ESCAPE:
					input->type = QUIT;
					break;
			}
		}
	}
}
