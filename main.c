//ascii render?
#include "render.h"
#include "screen.h"
#include "controls.h"
#include "raytracer.h"
#include "world.h"

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

//main kickoff function does stuff
int main(int argc,char **argv){	
	screenBuffer *screen = renderInit();
	if(screen == NULL){fprintf(stderr,"ERROR: render init failed\n");exit(1);}
	if(controlsInit()==false){fprintf(stderr,"ERROR: controls init failed\n");exit(1);}
	if(raytracerInit()==false){fprintf(stderr,"ERROR: raytracer init falled\n");exit(1);}
	objectArray *world = worldInit();
	if(world == NULL){fprintf(stderr,"ERROR: world init failed\n");exit(1);}

	bool stopMainLoop = false;  //shutdown var, i don't know how we need to shutdown the program so we need a few checks from multable sections	
	

	playerInput input;
	while(!stopMainLoop){
		raytrace(screen,*world);
		renderFrame();// render the next frame	
		
		// handle the userinput
		controlsHandleInput(&input);
		switch(input.type){
			case QUIT: // exit main loop
				stopMainLoop = true;
				continue;
			case MOVE: // move
				cameraMove(input.moves);	
				break;
			case ANGLE:
				cameraAngle(input.moves);
				break;
			default:
				break;
		}

		stopMainLoop = renderCheckStop(); // does the render want to stop
		
	}
	// cleanup functions
	freeWorld(&world);
	freeScreenBuffer(&screen);	
	renderStop();
}
