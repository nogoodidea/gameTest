#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define MAXPRESISION 0.00000001

typedef struct vector_s {
	double X;
	double Y;
	double Z;
} vector;
// colors for objects

typedef struct {
	unsigned int R;
	unsigned int G;
	unsigned int B;
} color;

// square objects
typedef struct subObject_s{
	vector *vec[3]; // triangle
	color colors;
} subObject;

// object in area, used 
typedef struct object_s {
	subObject **obj;
	unsigned int count;
} object;

typedef struct {
	object **obj;
	unsigned int count;
}objectArray;

// vector helper functions

void vectorSet(vector *vec,double X,double Y,double Z){
	vec->X = X;
	vec->Y = Y;
	vec->Z = Z;
}

void vectorCopy(vector *vecOut,vector vec){
	vecOut->X = vec.X;
	vecOut->Y = vec.Y;
	vecOut->Z = vec.Z;
}

bool vectorCompare(vector vec0,vector vec1){
	if(vec0.X==vec1.X && vec0.Y==vec1.Y && vec0.Z==vec1.Z){
		return true;
	}else{
		return false;
	}
}

// math ahead
void vectorCrossProduct(vector *vecOut,vector vec0,vector vec1){
	//https://www.mathsisfun.com/algebra/vectors-cross-product.html
	vecOut->X=(((vec0.Y)*(vec1.Z))-((vec0.Z)*(vec1.Y)));
	vecOut->Y=(((vec0.Z)*(vec1.X))-((vec0.X)*(vec1.Z)));
	vecOut->Z=(((vec0.X)*(vec1.Y))-((vec0.Y)*(vec1.X)));
}

void vectorScaler(vector *vecOut,vector vec0,double scaler){
	vecOut->X = vec0.X*scaler;
	vecOut->Y = vec0.Y*scaler;
	vecOut->Z = vec0.Z*scaler;
}

void vectorAdd(vector *vecOut,vector vec0,vector vec1){
	vecOut->X = vec0.X+vec1.X;
	vecOut->Y = vec0.Y+vec1.Y;
	vecOut->Z = vec0.Z+vec1.Z;
}

void vectorSub(vector *vecOut,vector vec0,vector vec1){
	vecOut->X = vec0.X-vec1.X;
	vecOut->Y = vec0.Y-vec1.Y;
	vecOut->Z = vec0.Z-vec1.Z;
}

void vectorMult(vector *vecOut,vector vec0,vector vec1){
	vecOut->X = vec0.X*vec1.X;
	vecOut->Y = vec0.Y*vec1.Y;
	vecOut->Z = vec0.Z*vec1.Z;
}

void vectorNormal(vector *vec){
	double sum = sqrt((pow(vec->X,2))+(pow(vec->Y,2))+(pow(vec->Z,2)));
	vec->X /= sum;
	vec->Y /= sum;
	vec->Z /= sum;
};

void vectorRotate(vector *vec,vector line,vector point,double theta){
	// vec is the vector to rotate, line is the axes to rotate it around, point is the point to rotate it around, theta is the amount of radions to rotate 
	double oldX = vec->X-point.X;
	double oldY = vec->Y-point.Y;
	double oldZ = vec->Z-point.Z;
	
	double cosT = cos(theta), sinT = sin(theta);
	double T = 1.0-cosT;

	vec->X = (cosT+pow(line.X,2)*T)*oldX+(line.X*line.Y*T-line.Z*sinT)*oldY +(line.X*line.Z*T+line.Y*sinT)*oldZ + point.X;
	vec->Y = (line.X*line.Y*T+line.Z*sinT)*oldX+(cosT+pow(line.Y,2)*T)*oldY+(line.Y*line.Z*T-line.X*sinT)*oldZ + point.Y;
	vec->Z = (line.Z*line.X-line.Y*sinT)*oldX+(line.Z*line.Y*T+line.X*sinT)*oldY+(cosT+pow(line.Z,2)*T)*oldZ + point.Z;
}

double vectorDotProduct(vector vec0,vector vec1){
	double out=0.0f;
	out += vec0.X*vec1.X;
	out += vec0.Y*vec1.Y;
	out += vec0.Z*vec1.Z;
	return out;
}

// object manipulation

void objectRotate(object obj,vector line,vector point,double theta){
	for(unsigned int i=0;i<obj.count;i+=1){
		for(unsigned int v=0;v<2;v+=1){
			vectorRotate(obj.obj[i]->vec[v],line,point,theta);
		}
	}
}

void objectScaler(object obj,double scaler){
	for(unsigned int i=0;i<obj.count;i+=1){
		for(unsigned int v=0;v<2;v+=1){
			vectorScaler(obj.obj[i]->vec[v],*obj.obj[i]->vec[v],scaler);
		}
	}
}


//object int/add/free
subObject *initSubObject(){
	vector zero;
	vectorSet(&zero,0.0f,0.0f,0.0f);
	subObject *object = malloc(sizeof(subObject));
	// allways has 3 vectors
	for(int i=0;i<3;i+=1){
		vectorCopy(object->vec[i],zero);
		//TODO error check for malloc calls
	}
	return object;
}

object *initObject(unsigned int amt){
	object *obj=malloc(sizeof(object));	
	//TODO same here
	obj->count = amt;
	obj->obj = malloc(sizeof(subObject*)*amt);
	return obj;
}

void addSubObject(object *obj,subObject *objAdd){
	obj->count +=1;
	obj->obj = realloc(obj->obj,sizeof(subObject*)*obj->count);
	// unchecked realloc
	obj->obj[obj->count-1] = objAdd;	
}

void addObject(objectArray *obj,object *objAdd){
	obj->count +=1;
	obj->obj = realloc(obj->obj,sizeof(subObject*)*obj->count);
	// unchecked realloc
	obj->obj[obj->count-1] = objAdd;	
}

void freeSubObject(subObject **obj){
	for(unsigned int i=0;i<3;i+=1){
		free((*obj)->vec[i]);
	}
	free((*obj));
	*obj = NULL;
}

void freeObject(object **obj){
	for(unsigned int i=0;i<(*obj)->count;i+=1){
		freeSubObject(&((*obj)->obj[i]));
		(*obj)->obj[i]=NULL;
	}
	free(*obj);
	*obj = NULL;
}
