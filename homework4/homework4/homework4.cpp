/*
    -----------------------------------------------------------
    * Programmer--Jacob Hisscock
    * Course------CS 3233
    * Project-----Homework #4: Lighted Hexagonal Birpyramid
    * Due---------November 11th, 2020
    *
    * This program creates and displays a 3D hexagonal bipyramid.
    * It also includes lighting on the bipyramid with the addition
    * of a trackball mouse rotation utility.
    *-----------------------------------------------------------
*/
#include <GL/glut.h>
#include <iostream> 
#include "camera.h"

void initGL() {
    //Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    //Init trackball functionality
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
}

void hexagonalBipyramid() {

    //Define x and z coordiantes for hexagonal pyrazmid
    float x[] = { 0.866f, 0.0f, -0.866f, -0.866f,  0.0f,  0.866f };
    float z[] = { 0.5f,   1.0f,  0.5f,   -0.5f,   -1.0f, -0.5f };

    float top[][3] = { { 0.0f, 3.5f, 0.0f } };
    float bottom[][3] = { { 0.0f, -3.5f, 0.0f } };

    //Define points to be used in the creation of triangles
    float newVertex[][3] = {
           {1.866f, 0.0f, 1.0f},
           {0.0f, 0.0f, 2.0f},
           {-1.866f, 0.0f, 1.0f},
           {-1.866f, 0.0f, -1.0f},
           {0.0f, 0.0f, -2.0f},
           {1.866f, 0.0f, -1.0f}
    };

    //Define the color for the bipyramid
    float pyramidColor[] = { 0.5f, 0.1f, 0.7f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, pyramidColor);      
    glMaterialfv(GL_FRONT, GL_SPECULAR, pyramidColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, pyramidColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    glBegin(GL_TRIANGLES);
        //Top pyramid
        glNormal3f(0.5f, 1.0f, 1.0f);
        glVertex3fv(top[0]);
        glVertex3fv(newVertex[1]);
        glVertex3fv(newVertex[0]);

        glNormal3f(-0.5f, 1.0f, 1.0f);
        glVertex3fv(top[0]);
        glVertex3fv(newVertex[2]);
        glVertex3fv(newVertex[1]);

        glNormal3f(-1.0f, 1.0f, 0.0f);
        glVertex3fv(top[0]);
        glVertex3fv(newVertex[3]);
        glVertex3fv(newVertex[2]);

        glNormal3f(1.0f, 1.0f, 0.0f);
        glVertex3fv(top[0]);
        glVertex3fv(newVertex[0]);
        glVertex3fv(newVertex[5]);

        glNormal3f(-0.5f, 1.0f, -1.0f);
        glVertex3fv(top[0]);
        glVertex3fv(newVertex[4]);
        glVertex3fv(newVertex[3]);

        glNormal3f(0.5f, 1.0f, -1.0f);
        glVertex3fv(top[0]);
        glVertex3fv(newVertex[5]);
        glVertex3fv(newVertex[4]);

        //Bottom Pyramid
        glNormal3f(0.5f, 0.0f, 1.0f);
        glVertex3fv(bottom[0]);
        glVertex3fv(newVertex[1]);
        glVertex3fv(newVertex[0]);

        glNormal3f(-0.5f, 0.0f, 1.0f);
        glVertex3fv(bottom[0]);
        glVertex3fv(newVertex[2]);
        glVertex3fv(newVertex[1]);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3fv(bottom[0]);
        glVertex3fv(newVertex[3]);
        glVertex3fv(newVertex[2]);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3fv(bottom[0]);
        glVertex3fv(newVertex[0]);
        glVertex3fv(newVertex[5]);

        glNormal3f(-0.5f, 0.0f, -1.0f);
        glVertex3fv(bottom[0]);
        glVertex3fv(newVertex[4]);
        glVertex3fv(newVertex[3]);

        glNormal3f(0.5f, 0.0f, -1.0f);
        glVertex3fv(bottom[0]);
        glVertex3fv(newVertex[5]);
        glVertex3fv(newVertex[4]);
    glEnd();
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    cameraSetLimits(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0); // Eck camera
    cameraApply();

    hexagonalBipyramid();//Draw bipyramid

    glFlush();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(640, 640);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display);
    initGL();                   //Custom init function to define parameters for this project
    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
