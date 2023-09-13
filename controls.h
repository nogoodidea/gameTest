#ifndef CONTROLS_GAME_TEST_H
#define CONTROLS_GAME_TEST_H
// gets the user inputs
#include<stdbool.h>

#include "raytracer.h"


// input types
enum inputType {QUIT,MOVE,NONE};


// union that holds the user input/SDL events for shutdown 
typedef struct playerInput {
	enum inputType type;
	vector moves; 	
} playerInput;


// int 
bool controlsInit();

void controlsHandleInput(playerInput *input);

#endif //CONTROLS_GAME_TEST_H
