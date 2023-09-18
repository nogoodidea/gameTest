#include<stdbool.h>

// math time :(
typedef struct vector_S {
	double X;
	double Y;
	double Z;
} vector;


//going to need a linked list for every object and a linked list for every object rendered in a given area

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
