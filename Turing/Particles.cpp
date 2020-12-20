#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Normals.h"

//Initialize particles with random coordiantes
float** initParticles() {
	float **particles;
	particles = new float* [100];
	for (int i = 0; i < 100; i++) {
		particles[i] = new float[3];
		float x = (float)(rand() % 21) - 10;
		float y = (float)(rand() % 21) - 10;
		float z = (float)(rand() % 21) - 10;
		particles[i][0] = x;
		particles[i][1] = y;
		particles[i][2] = z;
	}
	return particles;
}

//Draw the particles by translating by the random amounts defined in the initParticle function
void drawParticles(float** pArray, float scale, float height , float r, float g, float b) {
	for (int i = 0; i < 100; i++) {
		glPushMatrix();

		//Translate to random postion and modify the height by the animation timer set in Turing.cpp in the timer function
		glTranslatef(pArray[i][0], pArray[i][1] + height, pArray[i][2]);
		
		float rectColor[] = { r, g, b, 1.0f };

		glMaterialfv(GL_FRONT, GL_DIFFUSE, rectColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rectColor);
		glMaterialfv(GL_FRONT, GL_AMBIENT, rectColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

		float pos[][3] = {
			{-1 * scale, 1 * scale, 1 * scale},
			{-1 * scale, -1 * scale, 1 * scale},
			{1 * scale, -1 * scale, 1 * scale},
			{1 * scale, 1 * scale, 1 * scale},

			{-1 * scale, 1 * scale, -1 * scale},
			{-1 * scale, -1 * scale, -1 * scale}, 
			{1 * scale, -1 * scale, -1 * scale},
			{1 * scale, 1 * scale, -1 * scale},

			{-1 * scale, 1 * scale, -1 * scale},
			{-1 * scale, -1 * scale, -1 * scale},
			{-1 * scale, -1 * scale, 1 * scale},
			{-1 * scale, 1 * scale, 1 * scale},

			{1 * scale, 1 * scale, -1 * scale},
			{1 * scale, -1 * scale, -1 * scale},
			{1 * scale, -1 * scale, 1 * scale},
			{1 * scale, 1 * scale, 1 * scale},
		};

		//Draw the particles and apply textures with the texture height being changed by the height value in the timer funciton
		glBegin(GL_TRIANGLES);

		float* normal = calculateNormal(pos[0], pos[1], pos[2]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(pos[0][0], pos[0][1] + height);
		glVertex3fv(pos[0]);
		glTexCoord2f(pos[1][0], pos[1][1] + height);
		glVertex3fv(pos[1]);
		glTexCoord2f(pos[2][0], pos[2][1] + height);
		glVertex3fv(pos[2]);

		normal = calculateNormal(pos[3], pos[0], pos[2]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(pos[3][0], pos[3][1] + height);
		glVertex3fv(pos[3]);
		glTexCoord2f(pos[0][0], pos[0][1] + height);
		glVertex3fv(pos[0]);
		glTexCoord2f(pos[2][0], pos[2][1] + height);
		glVertex3fv(pos[2]);

		normal = calculateNormal(pos[4], pos[5], pos[6]);
		glNormal3f(-normal[0], -normal[1], -normal[2]);
		glTexCoord2f(pos[4][0], pos[4][1] + height);
		glVertex3fv(pos[4]);
		glTexCoord2f(pos[5][0], pos[5][1] + height);
		glVertex3fv(pos[5]);
		glTexCoord2f(pos[6][0], pos[6][1] + height);
		glVertex3fv(pos[6]);

		normal = calculateNormal(pos[7], pos[4], pos[6]);
		glNormal3f(-normal[0], -normal[1], -normal[2]);
		glTexCoord2f(pos[7][0], pos[7][1] + height);
		glVertex3fv(pos[7]);
		glTexCoord2f(pos[4][0], pos[4][1] + height);
		glVertex3fv(pos[4]);
		glTexCoord2f(pos[6][0], pos[6][1] + height);
		glVertex3fv(pos[6]);

		normal = calculateNormal(pos[8], pos[9], pos[10]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(pos[8][2], pos[8][1] + height);
		glVertex3fv(pos[8]);
		glTexCoord2f(pos[9][2], pos[9][1] + height);
		glVertex3fv(pos[9]);
		glTexCoord2f(pos[10][2], pos[10][1] + height);
		glVertex3fv(pos[10]);

		normal = calculateNormal(pos[11], pos[8], pos[10]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(pos[11][2], pos[11][1] + height);
		glVertex3fv(pos[11]);
		glTexCoord2f(pos[8][2], pos[8][1] + height);
		glVertex3fv(pos[8]);
		glTexCoord2f(pos[10][2], pos[10][1] + height);
		glVertex3fv(pos[10]);

		normal = calculateNormal(pos[12], pos[13], pos[14]);
		glNormal3f(-normal[0], -normal[1], -normal[2]);
		glTexCoord2f(pos[12][2], pos[12][1] + height);
		glVertex3fv(pos[12]);
		glTexCoord2f(pos[13][2], pos[13][1] + height);
		glVertex3fv(pos[13]);
		glTexCoord2f(pos[14][2], pos[14][1] + height);
		glVertex3fv(pos[14]);

		normal = calculateNormal(pos[15], pos[12], pos[14]);
		glNormal3f(-normal[0], -normal[1], -normal[2]);
		glTexCoord2f(pos[15][2], pos[15][1] + height);
		glVertex3fv(pos[15]);
		glTexCoord2f(pos[12][2], pos[12][1] + height);
		glVertex3fv(pos[12]);
		glTexCoord2f(pos[14][2], pos[14][1] + height);
		glVertex3fv(pos[14]);

		glEnd();
		

		glPopMatrix();
		
	}
}