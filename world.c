#include <stdbool.h>
#include <stdlib.h>

#include "object.h"

typedef struct {
	object **obj;
	unsigned int count;
}objectArray;

objectArray *worldInit(){
	objectArray *world=malloc(sizeof(objectArray));
	world->count = 1;
	world->obj = malloc(sizeof(object*)*1);
	world->obj[0] = initObject(1);
	vector vec0={1.0,0.5,0.0},vec1={1.0,-0.5,0.0},vec2={1.0,0.5,0.5};
	subObjectSet((world->obj[0]->obj[0]),vec0,vec1,vec2);
	return world;
}

void freeWorld(objectArray **world){
	for(unsigned int i=0;i<(*world)->count;i+=1){
		freeObject(&((*world)->obj[i]));
	}
	free(*world);
	*world=NULL;
}

void worldAddObject(objectArray *world,object *objAdd){
	world->count +=1;
	world->obj = realloc(world->obj,sizeof(object*)*world->count);
	// unchecked realloc
	world->obj[world->count-1] = objAdd;	
}
