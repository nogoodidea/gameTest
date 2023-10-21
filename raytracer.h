#ifndef RAYTRACER_GAME_TEST_H
#define RAYTRACER_GAME_TEST_H

#include "screen.h"
#include "object.h"
#include "world.h"

typedef struct {
	vector pos;
	vector dir;
} camera;

//
bool raytracerInit();

// camera functions 
void cameraMove(vector dir);

void cameraAngle(vector dir);
//// does the raytraser stuff
bool raytrace(screenBuffer *screen,objectArray world);


#endif //RAYTRACER_GAME_TEST_H
