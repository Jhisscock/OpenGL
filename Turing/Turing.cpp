/*
	-----------------------------------------------------------
	* Programmer--Jacob Hisscock
	* Course------CS 3233
	* Project----- Homework #5: Drawing of my own
	* Due---------December 7th, 2020
	*
	* This project draws a simple recreation of Alan Turing's
	* bombe machine that helped crack the enigma code during WW2.
	* It is also heavily responsible for the start of computing.
	*-----------------------------------------------------------
*/

#include <stdlib.h>
#include <math.h>
#include "Camera.h"
#include "Knob.h"
#include "Normals.h"
#include <time.h>
#include <iostream>
#include "TextureLoader.h"
#include "Particles.h"

using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 1.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

//Used to rotate knob on machine
GLfloat angleKB = 0.0f;
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
float angleZ = 1.0f;
GLfloat speed = -2.0f;

//Used to move particle effects and their textures
float pSpeed = 0.02f;
float pHeight = 0;

unsigned int ID; //Contains ids for different textures
float** particles; //Contains random coordiantes for the particles

void LoadTexture(const char* filename);

void GLinit() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	particles = initParticles(); //Initialize particles with random coordiantes

	//Initialize texture that will be used
	LoadTexture("texture/metal10.bmp");
	LoadTexture("texture/coding.bmp");
	LoadTexture("texture/blackhole1.bmp");
}

//Function to load a texture into memory and save it under a unique ID
void LoadTexture(const char* filename) {
	TextureLoader tl(filename);
	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tl.iWidth, tl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, tl.textureData);
}

//Draw the machine
void drawTuring(float radius, float height, float x, float y, float z, float scale) {
	//Draw all the rotating knobs on the machine
	for (int i = 0; i < 135; i++) {
		//Create three rows and 9 rows of knobs in pairs of three
		float kX = knobPos[i % 9][0] + i / 9 * 0.7;
		float kY = knobPos[i % 9][1] + 1.75f;
		float kZ = knobPos[i % 9][2] + 0.25f;

		//Rotate knobs
		glPushMatrix();
		glTranslatef(kX, kY, kZ);
		glRotatef(angleKB, angleX, angleY, angleZ);
		glScalef(0.3f, 0.3f, 0.3f);
		
		//Draw knob base
		glPushMatrix();
		drawCylinder(radius, height, scale, 0.2f, 0.0f, 0.0f);
		glPopMatrix();

		//Draw inner knob
		glPushMatrix();
		glTranslatef(0, 0, 0.1f);
		drawCylinder(radius * 0.9, height, scale, 0.2f, 0.2f, 0.2f);
		glPopMatrix();

		//Draw inner circle in knob
		glPushMatrix();
		glTranslatef(0, 0, 1);
		drawCylinder(radius, height / 2, scale / 3, 0.4f, 0.4f, 0.4f);
		glPopMatrix();

		//Draw rectangle in knob
		glPushMatrix();
		glTranslatef(0, -1, 0);
		drawKnobRect(x, y, z + height, scale / 3, 0.4f, 0.4f, 0.4f, 1.0f);
		glPopMatrix();

		
		glPopMatrix();
	}

	//Draw the machine itself
	glPushMatrix();
	glTranslatef(x + scale * 5, y, z);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	drawRectangularPrism(x, y, z - height * 2.5 , scale * 5.5, 0.2f, 0.2f, 0.2f, 2.5f);
	glPopMatrix();

	//Draw chords
	drawChord(3, 0.075f, 0.5f, 0.1f, 0.1f, 150, -6, 7.3, 0.75f, 50, true, 2.5, 0.25);
	drawChord(3, 0.025f, 0.5f, 0.1f, 0.1f, 350, 6.5, -1, 0.75f, 75, false, 0.75, 2);
	for (int i = 0; i < 18; i++) {
		drawChord(8, 0.04f, 0.5f, 0.1f, 0.1f, 100, 6.5 + (float)i * -0.75f, -1, -5.6f, 75, false, 0.75, 9);
	}
}

void renderScene(void) {
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, z,x + lx, 1.0f, z + lz,0.0f, 1.0f, 0.0f);

	//Set texture for machine and draw the machine
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 1);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTranslatef(0, 0.75f, 0);
	glScalef(0.1f, 0.1f, 0.1f);

	drawTuring(1.0, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);

	glPopMatrix();

	//Set texture for particles and draw particles
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 3);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	drawParticles(particles, 0.2f, pHeight, 0.2f, 0.7f, 0.2f);
	glPopMatrix();

	//Set texture for background and draw background
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 2);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-20, -20, -10);
	glTexCoord2f(0.0, 1.0); glVertex3f(-20, 20, -10);
	glTexCoord2f(1.0, 1.0); glVertex3f(20, 20, -10);
	glTexCoord2f(1.0, 0.0); glVertex3f(20, -20, -10);

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-20, -20, 10);
	glTexCoord2f(0.0, 1.0); glVertex3f(-20, 20, 10);
	glTexCoord2f(1.0, 1.0); glVertex3f(20, 20, 10);
	glTexCoord2f(1.0, 0.0); glVertex3f(20, -20, 10);
	glPopMatrix();

	glTexCoord2f(0.0, 0.0); glVertex3f(-10, -20, -20);
	glTexCoord2f(0.0, 1.0); glVertex3f(-10, 20, -20);
	glTexCoord2f(1.0, 1.0); glVertex3f(-10, 20, 20);
	glTexCoord2f(1.0, 0.0); glVertex3f(-10, -20, 20);

	glTexCoord2f(0.0, 0.0); glVertex3f(10, -20, -20);
	glTexCoord2f(0.0, 1.0); glVertex3f(10, 20, -20);
	glTexCoord2f(1.0, 1.0); glVertex3f(10, 20, 20);
	glTexCoord2f(1.0, 0.0); glVertex3f(10, -20, 20);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void timer(int v) {
	//Controls knobs rotating
	angleKB += speed; //increment angle by user entered speed value.
	if (angleKB > 360.0) {
		angleKB = 0;
	}

	//Controls particles falling and their textures
	pHeight -= pSpeed;
	if (pHeight <= -10) {
		pHeight = 0;
	}
	glutPostRedisplay(); //Redraws image with new rotation applied

	glutTimerFunc(1000 / 60, timer, v);
}

int main(int argc, char** argv) {
	srand(time(0));
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Homework 5");

	
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//Allow user to move camera with arrow keys
	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	//Call timer function for animations
	glutTimerFunc(100, timer, 0);

	// OpenGL init
	GLinit();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}