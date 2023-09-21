//ascii render?
#include "render.h"
#include "screen.h"
#include "controls.h"
#include "raytracer.h"

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

//main kickoff function does stuff
int main(int argc,char **argv){	
	screenBuffer *screen = renderInit();
	if(screen == NULL){fprintf(stderr,"ERROR: screen alloc failed");exit(1);}
	if(controlsInit()==false){fprintf(stderr,"ERROR: controls start failled");exit(1);}

	bool stopMainLoop = false;  //shutdown var, i don't know how we need to shutdown the program so we need a few checks from multable sections	

	playerInput input;
	while(!stopMainLoop){
		raytrace(screen);
		renderFrame();// render the next frame	
		
		// handle the userinput
		controlsHandleInput(&input);
		if(input.type == QUIT){
			stopMainLoop = true;
			continue;
		}

		

		stopMainLoop = renderCheckStop(); // does the render want to stop
		
	}
	// cleanup functions
	freeScreenBuffer(&screen);	
	renderStop();
}
