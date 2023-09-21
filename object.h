// math time :(
typedef struct vector_s {
	double X;
	double Y;
	double Z;
} vector;

// vector array for objects
typedef struct sub_object_s {
	vector *point;
	unsigned int count;
} subObject;

// object in area, used 
typedef struct object_s {
	vector *bounding;
	unsigned int bCount;
	subObject *s
} object;
