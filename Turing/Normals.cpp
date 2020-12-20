#include <stdlib.h>
#include <math.h>
#include "Normals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Function to calculate normals from earlier in the semester
float* calculateNormal(float p1[3], float p2[3], float p3[3]) {
	float u[3];
	u[0] = p1[0] - p3[0];
	u[1] = p1[1] - p3[1];
	u[2] = p1[2] - p3[2];

	float v[3];
	v[0] = p2[0] - p3[0];
	v[1] = p2[1] - p3[1];
	v[2] = p2[2] - p3[2];

	float normal[3];
	normal[0] = u[1] * v[2] - u[2] * v[1];
	normal[1] = u[0] * v[2] - u[2] * v[0];
	normal[2] = u[0] * v[1] - u[1] * v[0];

	float length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	for (int i = 0; i < 3; i++) {
		normal[i] = normal[i] / length;
	}

	return normal;

}