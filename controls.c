#include<SDL2/SDL.h>
#include<SDL2/SDL_keyboard.h>
#include<SDL2/SDL_video.h>

#include<stdbool.h>


#include "raytracer.h"
#include "object.h"

// input types
enum inputType {QUIT,ANGLE,MOVE,NONE};
//QUIT, exits game
//ANGLE, changes the carmera angle (turn camera)
//MOVE, moves
//NONE, none


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
	vectorSet(&(input->moves),0.0,0.0,0.0); // zero out the vector :) 
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			input->type = QUIT;
		}
		if(event.type == SDL_KEYDOWN){
			// exit the program on ESC
			switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					input->type = QUIT;
					break;
				case SDLK_w:
					input->type = MOVE;
					input->moves.X = 1.0;
					break;
				case SDLK_s:
					input->type = MOVE;
					input->moves.X = -1.0;
					break;
				case SDLK_a:
					input->type = MOVE;
					input->moves.Y = 1.0;
					break;
				case SDLK_d:
					input->type = MOVE;
					input->moves.Y = -1.0;
					break;
			}
		}
	}
}
