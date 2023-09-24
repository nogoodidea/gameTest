#ifndef RAYTRACER_GAME_TEST_H
#define RAYTRACER_GAME_TEST_H

#include "screen.h"
#include "object.h"

typedef struct {
	vector pos;
	vector dir;
} camera;

//
bool raytracerInit();


//// does the raytraser stuff
bool raytrace(screenBuffer *screen);


#endif //RAYTRACER_GAME_TEST_H
