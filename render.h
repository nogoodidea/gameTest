#ifndef RENDER_H
#define RENDER_H

#include "screen.h"

#include <stdbool.h>

// int the rendering window
screenBuffer *renderInit();	

// stop the rendering
void renderStop();

// render the next frame
void renderFrame();

// checks if the render wants to stop 
bool renderCheckStop();
#endif //RENDER_H
