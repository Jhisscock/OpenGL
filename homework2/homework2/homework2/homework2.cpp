/*
    -----------------------------------------------------------
    * Programmer--Jacob Hisscock
    * Course------CS 3233
    * Project-----Homework #2: Multi-color triangle
    * Due---------September 17, 2020
    *
    * This program creates and displays a multicolored triangle
    *-----------------------------------------------------------
*/
#include <GL/glut.h>
#include <cmath>

GLuint house;

void drawHouse() {
    //Draw Moon
    glBegin(GL_TRIANGLE_FAN);
    float x = 130.0f;
    float y = 130.0f;
    for (int i = 0; i < 360; i++) {
        glColor3f(0.8f, 0.8f, 0.8f);
        x = x + (0.25f * cos(i * 2.0f * 3.14f / 360));
        y = y + (0.25f * sin(i * 2.0f * 3.14f / 360));
        glVertex2f(x / GLUT_SCREEN_WIDTH, y / GLUT_SCREEN_HEIGHT);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    //Roof
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.0f, 0.5f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.5f, 0.25f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.5f, 0.25f);

    //House Body
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(-0.35f, 0.25f);
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(0.35f, 0.25f);
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(-0.35f, -0.35f);
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(0.35f, 0.25f);
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(-0.35f, -0.35f);
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(0.35f, -0.35f);

    //Door
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex2f(-0.1f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex2f(0.1f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex2f(-0.1f, -0.35f);
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex2f(0.1f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex2f(-0.1f, -0.35f);
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex2f(0.1f, -0.35f);

    //Windows
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(-0.25f, 0.15f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(-0.15f, 0.15f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(-0.25f, 0.05f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(-0.15f, 0.15f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(-0.15f, 0.05f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(-0.25f, 0.05f);

    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(0.25f, 0.15f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(0.15f, 0.15f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(0.25f, 0.05f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(0.15f, 0.15f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(0.15f, 0.05f);
    glColor4f(0.8, 0.8, 0.8, 0.5);
    glVertex2f(0.25f, 0.05f);
    glEnd();

    //Shrub
    float xTranslate = 0.5f;
    float yTranslate = 1.0f;
    for (int j = 0; j < 5; j++) {
        glBegin(GL_TRIANGLE_FAN);
        float xx = 130.0f;
        float yy = 130.0f;
        for (int i = 0; i < 360; i++) {
            glColor3f(0.0f, 0.8f, 0.0f);
            xx = xx + (0.25f * cos(i * 2.0f * 3.14f / 360));
            yy = yy + (0.25f * sin(i * 2.0f * 3.14f / 360));
            glVertex2f(xx / GLUT_SCREEN_WIDTH - xTranslate, yy / GLUT_SCREEN_HEIGHT - yTranslate);
        }
        if (j == 2) {
            xTranslate = 0.55f;
            yTranslate -= 0.1f;
        }
        xTranslate -= 0.1f;
        glEnd();
    }
}

void display() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glEnable(GL_BLEND);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);

    house = glGenLists(1);
    glNewList(house, GL_COMPILE);
    drawHouse();
    glEndList();

    glCallList(house);

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
