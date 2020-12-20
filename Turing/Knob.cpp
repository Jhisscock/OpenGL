#include <stdlib.h>
#include <math.h>
#include "Knob.h"
#include "Normals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define M_PI 3.14159265358979323846

//define knob postions
float knobPos[][3] = { 
	{-5.0f, 5.0f, 0},
	{-5.0f, 4.25f, 0},
	{-5.0f, 3.5f, 0},
	{-5.0f, 2.25f, 0},
	{-5.0f, 1.5f, 0},
	{-5.0f, 0.75f, 0},
	{-5.0f, -0.5f, 0},
	{-5.0f, -1.25f, 0},
	{-5.0f, -2.0f, 0},
};

//Draw a cylinder, this is used multiple times to create three cylinders for the knob
void drawCylinder(float radius, float height, float scale, float r, float g, float b) {
	float cylinderColor[] = { r, g, b, 1.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, cylinderColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cylinderColor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cylinderColor);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricDrawStyle(quadratic, GLU_FILL);

	//Draw cylinder
	radius *= scale;
	height *= scale;
	glPushMatrix();
	gluCylinder(quadratic, radius, radius, height, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	gluDisk(quadratic, 0.0, radius, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(quadratic, 0.0, radius, 32, 32);
	glPopMatrix();
}

//Draw a chord, uses a sin wave to draw spheres in a wavy pattern to look like a chord
void drawChord(float radius, float scale, float r, float g, float b, float size, float x, float y, float z, int startPos, bool horiz , float xMod, float yMod) {
	glPushMatrix();
	float x1, x2, y1, y2;
	for (int i = startPos; i < size; i++)
	{
		//Calculate sin wave
		x1 = (float)i / size;
		y1 = sin(x1 * 5 * M_PI);

		//Choose whether or not the chord will be horizontal or vertical by translating it by the x and y calulated for the sin wave
		if (horiz) {
			glTranslatef(x1 * scale * xMod, y1 * scale * yMod, 0);
		}
		else {
			glTranslatef(y1 * scale * xMod, x1 * scale * yMod, 0);
		}
		

		//Draw chord
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(scale, scale, scale);
		float chordColor[] = { r, g, b, 1.0f };

		glMaterialfv(GL_FRONT, GL_DIFFUSE, chordColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chordColor);
		glMaterialfv(GL_FRONT, GL_AMBIENT, chordColor);
		glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		gluQuadricDrawStyle(quadratic, GLU_FILL);

		glPushMatrix();
		gluSphere(quadratic, radius, 32, 32);
		glPopMatrix();

		glPopMatrix();
	}
	glPopMatrix();

	
}

//Draw the machine
void drawRectangularPrism(float x, float y, float z, float scale, float r, float g, float b, float xMod) {
	float rectColor[] = { r, g, b, 1.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, rectColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, rectColor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, rectColor);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

	//Define coordiantes for the machine
	scale = scale / 2;
	float pos[][3] = {
		{x - scale, y + scale * 4 ,z - scale}, //top-left-back
		{x - scale, y + scale * 4 ,z + scale}, //top-left-front
		{x + scale * xMod , y + scale * 4,z - scale}, //top-right-back
		{x + scale * xMod , y + scale * 4,z + scale}, //top-right-front

		{x - scale, y - scale,z - scale}, //bottom-left-back
		{x - scale, y - scale,z + scale}, //bottom-left-front
		{x + scale * xMod , y - scale,z - scale}, //bottom-right-back
		{x + scale * xMod , y - scale,z + scale}, //bottom-right-front

		{x + scale * xMod , y + scale * 4 ,z + scale}, //right-front-top
		{x + scale * xMod , y - scale ,z + scale}, //right-front-bottom
		{x + scale * xMod , y - scale ,z - scale}, //right-back-bottom
		{x + scale * xMod , y + scale * 4 ,z - scale}, //right-back-top

		{x - scale, y + scale * 4 ,z + scale}, //left-front-top
		{x - scale, y - scale ,z + scale}, //left-front-bottom
		{x - scale, y - scale ,z - scale}, //left-back-bottom
		{x - scale, y + scale * 4 ,z - scale}, //left-back-top

		{x - scale, y + scale * 4 ,z + scale}, //front-left-top
		{x - scale, y - scale ,z + scale}, //front-left-bottom
		{x + scale * xMod , y - scale ,z + scale}, //front-right-bottom
		{x + scale * xMod , y + scale * 4 ,z + scale}, //front-right-top

		{x - scale, y + scale * 4 ,z - scale}, //back-left-top
		{x - scale, y - scale ,z - scale}, //back-left-bottom
		{x + scale * xMod , y - scale ,z - scale}, //back-right-bottom
		{x + scale * xMod , y + scale * 4 ,z - scale}, //back-right-top
	};

	//Draw the machine while calulating the normals and applying textures to each triangle
	glBegin(GL_TRIANGLES);
	//Draw Top
	float* normal = calculateNormal(pos[0], pos[1], pos[2]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[0][0], pos[0][1]);
	glVertex3fv(pos[0]);
	glTexCoord2f(pos[1][0], pos[1][1]);
	glVertex3fv(pos[1]);
	glTexCoord2f(pos[2][0], pos[2][1]);
	glVertex3fv(pos[2]);

	normal = calculateNormal(pos[2], pos[1], pos[3]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[2][0], pos[2][1]);
	glVertex3fv(pos[2]);
	glTexCoord2f(pos[1][0], pos[1][1]);
	glVertex3fv(pos[1]);
	glTexCoord2f(pos[3][0], pos[3][1]);
	glVertex3fv(pos[3]);

	//Draw Bottom
	normal = calculateNormal(pos[4], pos[5], pos[6]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[4][0], pos[4][1]);
	glVertex3fv(pos[4]);
	glTexCoord2f(pos[5][0], pos[5][1]);
	glVertex3fv(pos[5]);
	glTexCoord2f(pos[6][0], pos[6][1]);
	glVertex3fv(pos[6]);

	normal = calculateNormal(pos[6], pos[5], pos[7]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[6][0], pos[6][1]);
	glVertex3fv(pos[6]);
	glTexCoord2f(pos[5][0], pos[5][1]);
	glVertex3fv(pos[5]);
	glTexCoord2f(pos[7][0], pos[7][1]);
	glVertex3fv(pos[7]);

	//Draw right
	normal = calculateNormal(pos[8], pos[9], pos[10]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[8][0], pos[9][1]);
	glVertex3fv(pos[8]);
	glTexCoord2f(pos[9][0], pos[9][1]);
	glVertex3fv(pos[9]);
	glTexCoord2f(pos[10][0], pos[10][1]);
	glVertex3fv(pos[10]);

	normal = calculateNormal(pos[10], pos[11], pos[8]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[10][0], pos[10][1]);
	glVertex3fv(pos[10]);
	glTexCoord2f(pos[11][0], pos[11][1]);
	glVertex3fv(pos[11]);
	glTexCoord2f(pos[8][0], pos[8][1]);
	glVertex3fv(pos[8]);

	//Draw left
	normal = calculateNormal(pos[12], pos[13], pos[14]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glTexCoord2f(pos[12][0], pos[12][1]);
	glVertex3fv(pos[12]);
	glTexCoord2f(pos[13][0], pos[13][1]);
	glVertex3fv(pos[13]);
	glTexCoord2f(pos[14][0], pos[14][1]);
	glVertex3fv(pos[14]);

	normal = calculateNormal(pos[14], pos[15], pos[12]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glTexCoord2f(pos[14][0], pos[14][1]);
	glVertex3fv(pos[14]);
	glTexCoord2f(pos[15][0], pos[15][1]);
	glVertex3fv(pos[15]);
	glTexCoord2f(pos[12][0], pos[12][1]);
	glVertex3fv(pos[12]);

	//Draw front
	normal = calculateNormal(pos[16], pos[17], pos[18]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[16][0], pos[16][1]);
	glVertex3fv(pos[16]);
	glTexCoord2f(pos[17][0], pos[17][1]);
	glVertex3fv(pos[17]);
	glTexCoord2f(pos[18][0], pos[18][1]);
	glVertex3fv(pos[18]);

	normal = calculateNormal(pos[18], pos[16], pos[19]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glTexCoord2f(pos[18][0], pos[18][1]);
	glVertex3fv(pos[18]);
	glTexCoord2f(pos[16][0], pos[16][1]);
	glVertex3fv(pos[16]);
	glTexCoord2f(pos[19][0], pos[19][1]);
	glVertex3fv(pos[19]);

	//Draw back
	normal = calculateNormal(pos[20], pos[21], pos[22]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glTexCoord2f(pos[20][0], pos[20][1]);
	glVertex3fv(pos[20]);
	glTexCoord2f(pos[21][0], pos[21][1]);
	glVertex3fv(pos[21]);
	glTexCoord2f(pos[22][0], pos[22][1]);
	glVertex3fv(pos[22]);

	normal = calculateNormal(pos[18], pos[16], pos[19]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glTexCoord2f(pos[22][0], pos[22][1]);
	glVertex3fv(pos[22]);
	glTexCoord2f(pos[20][0], pos[20][1]);
	glVertex3fv(pos[20]);
	glTexCoord2f(pos[23][0], pos[23][1]);
	glVertex3fv(pos[23]);
	glEnd();
}

//Draw the smaller rectangle contained within the knob
void drawKnobRect(float x, float y, float z, float scale, float r, float g, float b, float xMod) {
	float rectColor[] = { r, g, b, 1.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, rectColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, rectColor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, rectColor);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

	scale = scale / 2;
	float pos[][3] = {
		{x - scale, y + scale * 4 ,z - scale}, //top-left-back
		{x - scale, y + scale * 4 ,z + scale}, //top-left-front
		{x + scale * xMod , y + scale * 4,z - scale}, //top-right-back
		{x + scale * xMod , y + scale * 4,z + scale}, //top-right-front

		{x - scale, y - scale,z - scale}, //bottom-left-back
		{x - scale, y - scale,z + scale}, //bottom-left-front
		{x + scale * xMod , y - scale,z - scale}, //bottom-right-back
		{x + scale * xMod , y - scale,z + scale}, //bottom-right-front

		{x + scale * xMod , y + scale * 4 ,z + scale}, //right-front-top
		{x + scale * xMod , y - scale ,z + scale}, //right-front-bottom
		{x + scale * xMod , y - scale ,z - scale}, //right-back-bottom
		{x + scale * xMod , y + scale * 4 ,z - scale}, //right-back-top

		{x - scale, y + scale * 4 ,z + scale}, //left-front-top
		{x - scale, y - scale ,z + scale}, //left-front-bottom
		{x - scale, y - scale ,z - scale}, //left-back-bottom
		{x - scale, y + scale * 4 ,z - scale}, //left-back-top

		{x - scale, y + scale * 4 ,z + scale}, //front-left-top
		{x - scale, y - scale ,z + scale}, //front-left-bottom
		{x + scale * xMod , y - scale ,z + scale}, //front-right-bottom
		{x + scale * xMod , y + scale * 4 ,z + scale}, //front-right-top

		{x - scale, y + scale * 4 ,z - scale}, //back-left-top
		{x - scale, y - scale ,z - scale}, //back-left-bottom
		{x + scale * xMod , y - scale ,z - scale}, //back-right-bottom
		{x + scale * xMod , y + scale * 4 ,z - scale}, //back-right-top
	};

	glBegin(GL_TRIANGLES);
	//Draw Top
	float* normal = calculateNormal(pos[0], pos[1], pos[2]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[0]);
	glVertex3fv(pos[1]);
	glVertex3fv(pos[2]);

	normal = calculateNormal(pos[2], pos[1], pos[3]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[2]);
	glVertex3fv(pos[1]);
	glVertex3fv(pos[3]);

	//Draw Bottom
	normal = calculateNormal(pos[4], pos[5], pos[6]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[4]);
	glVertex3fv(pos[5]);
	glVertex3fv(pos[6]);

	normal = calculateNormal(pos[6], pos[5], pos[7]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[6]);
	glVertex3fv(pos[5]);
	glVertex3fv(pos[7]);

	//Draw right
	normal = calculateNormal(pos[8], pos[9], pos[10]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[8]);
	glVertex3fv(pos[9]);
	glVertex3fv(pos[10]);

	normal = calculateNormal(pos[10], pos[11], pos[8]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[10]);
	glVertex3fv(pos[11]);
	glVertex3fv(pos[8]);

	//Draw left
	normal = calculateNormal(pos[12], pos[13], pos[14]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glVertex3fv(pos[12]);
	glVertex3fv(pos[13]);
	glVertex3fv(pos[14]);

	normal = calculateNormal(pos[14], pos[15], pos[12]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glVertex3fv(pos[14]);
	glVertex3fv(pos[15]);
	glVertex3fv(pos[12]);

	//Draw front
	normal = calculateNormal(pos[16], pos[17], pos[18]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[16]);
	glVertex3fv(pos[17]);
	glVertex3fv(pos[18]);

	normal = calculateNormal(pos[18], pos[16], pos[19]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glVertex3fv(pos[18]);
	glVertex3fv(pos[16]);
	glVertex3fv(pos[19]);

	//Draw back
	normal = calculateNormal(pos[20], pos[21], pos[22]);
	glNormal3f(-normal[0], -normal[1], -normal[2]);
	glVertex3fv(pos[20]);
	glVertex3fv(pos[21]);
	glVertex3fv(pos[22]);

	normal = calculateNormal(pos[18], pos[16], pos[19]);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3fv(pos[22]);
	glVertex3fv(pos[20]);
	glVertex3fv(pos[23]);
	glEnd();
}