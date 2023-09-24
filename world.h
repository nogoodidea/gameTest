#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

#include "object.h"

typedef struct {
	object **obj;
	unsigned int count;
}objectArray;

objectArray *worldInit();

void freeWorld(objectArray **world);

void worldAddObject(objectArray *obj,object *objAdd);
#endif //WORLD_H
