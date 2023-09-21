#include<stdbool.h>

#include "screen.h"
#include "objects.h"




//going to need a list for every object and a linked list for every object rendered in a given area

bool compareVecX(vector vec0,vector vec1){
	if(vec0.X <= vec1.X){return false;}
	else{return true;}
}

bool compareVecY(vector vec0,vector vec1){
	if(vec0.Y <= vec1.Y){return false;}
	else{return true;}
}

bool compareVecZ(vector vec0,vector vec1){
	if(vec0.Z <= vec1.Z){return false;}
	else{return true;}
}

bool checkIntersect(vector ray,object obj){
	// for every index of the array
	for(unsigned int i=0;i<=obj.count;i+=1){
		compareVecX(ray,obj.point[i]); // vector 1
		compareVecY(ray,obj.point[i]);
		compareVecZ(ray,obj.point[i]);
	}
	return false;
}

// does the raytraceing
bool raytrace(screenBuffer *screen){
	for(unsigned int y=0;y<screen->y;y+=1){
		for(unsigned int x=0;x<screen->x;x+=1){
			screenZeroPixel(&(screen->buffer[y][x]));	
		}
	}
	return true;
}
