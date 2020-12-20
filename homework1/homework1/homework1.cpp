/*
    -----------------------------------------------------------
    * Programmer--Jacob Hisscock
    * Course------CS 3233
    * Project-----Homework #1: Multi-color triangle
    * Due---------September 17, 2020
    *
    * This program creates and displays a multicolored triangle
    *-----------------------------------------------------------
*/
#include <GL/glut.h>


void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    // Draw a Multicolored triangle
    glBegin(GL_TRIANGLES);              // Each set of 3 vertices form a triangle
    glColor3f(0.0f, 1.0f, 0.0f);        // Color 1 will be applied to verticy 1 (Green)
    glVertex2f(0.5f, -0.5f);            // Verticy 1 (Bottom right verticy)
    glColor3f(0.0f, 0.0f, 1.0f);        // Color 2 will be applied to verticy 2 (Blue)
    glVertex2f(0.0f, 0.5f);             // Verticy 2 (Top verticy)
    glColor3f(1.0f, 0.0f, 0.0f);        // Color 3 will be applied to verticy 3 (Red)
    glVertex2f(-0.5f, -0.5f);           // Verticy 3 (Bottom left verticy)
    glEnd();

    glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
