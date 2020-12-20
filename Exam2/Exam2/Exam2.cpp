/*
    -----------------------------------------------------------
    * Programmer--Jacob Hisscock
    * Course------CS 3233
    * Project-----Exam #2: Pyramids of Giza
    * Due---------November 17th, 2020
    *
    * This program creates and displays a simple recreation of 
    * the pyramids of Giza. It lights the pyramid and includes
    * a camera API for rotating around the scene.
    *-----------------------------------------------------------
*/
#ifdef _WIN32    
    #include <GL/glut.h>
#elif __linux__    
    #include <GL/glut.h>
#elif __APPLE__    
    #define GL_SILENCE_DEPRECATION    
    #include <OpenGL/gl.h>    
    #include <GLUT/glut.h>
#endif

#include <iostream> 
#include "camera.h"

void initGL() {
    //Enable normals
    glEnable(GL_NORMALIZE);

    //Init trackball functionality
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
}

//Function for calculating normals based on three points
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

//Fucntion that draws a pyramid based on a given x, y, and z coordinate and a scale
void drawPyramid(float x, float y, float z, float scale) {
    //Create the points for the pyramid
    float pos[][3] = {
        {x, y + scale/1.5, z},
        {x - scale/2, y, z + scale/2},
        {scale/2 + x, y, z + scale/2},
        {x - scale / 2, y, z - scale / 2},
        {scale / 2 + x, y, z - scale / 2},
    };

    //Set pyramid color
    float pyramidColor[] = { 0.8f, 0.7f, 0.5f, 1.0f };

    //Enable lighting material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pyramidColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pyramidColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, pyramidColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    //Begin drawing pyramid
    glBegin(GL_TRIANGLES);
    float* normal = calculateNormal(pos[0], pos[1], pos[2]);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3fv(pos[0]);
    glVertex3fv(pos[1]);
    glVertex3fv(pos[2]);

    normal = calculateNormal(pos[0], pos[3], pos[1]);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3fv(pos[0]);
    glVertex3fv(pos[3]);
    glVertex3fv(pos[1]);

    normal = calculateNormal(pos[0], pos[4], pos[3]);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3fv(pos[0]);
    glVertex3fv(pos[4]);
    glVertex3fv(pos[3]);

    normal = calculateNormal(pos[0], pos[2], pos[4]);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3fv(pos[0]);
    glVertex3fv(pos[2]);
    glVertex3fv(pos[4]);

    glEnd();
}


void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    cameraSetLimits(-10.0, 10.0, -5.0, 5.0, -60.0, 60.0); // Eck camera
    cameraApply();

    //Draw floor (not lighted beacuse lighting made it hard to see pyramids).
    glBegin(GL_TRIANGLES);

    glColor3f(0.8f, 0.7f, 0.6f);
    glVertex3f(20.0f, -2.0f, -60.0f);
    glVertex3f(-20.0f, -2.0f, 60.0f);
    glVertex3f(20.0f, -2.0f, 60.0f);

    glColor3f(0.8f, 0.7f, 0.6f);
    glVertex3f(20.0f, -2.0f, -60.0f);
    glVertex3f(-20.0f, -2.0f, -60.0f);
    glVertex3f(-20.0f, -2.0f, 60.0f);

    glEnd();

    //Enable Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Draw three small pyramids in front
    drawPyramid(-3.5, -2, 4, 1);
    drawPyramid(-2.25, -2, 4, 1);
    drawPyramid(-1, -2, 4, 1);

    //Draw three larger pyramids from closest to farthest
    drawPyramid(-1.25, -2, 1, 2.5);
    drawPyramid(4, -2, -10, 5);
    drawPyramid(13.5, -2, -30, 6.5);

    //Disable Lighting
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glFlush();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    float p1[][3] = { { 7.0f, 8.0f, 9.0f },
                    { 1.0f, 2.0f, 3.0f },
                       { 4.0f, 5.0f, 6.0f } };
    float* ans = calculateNormal(p1[0], p1[1], p1[2]);
    std::cout << ans[0] << ", " << ans[1] << ", " << ans[2] << std::endl;
    glutInit(&argc, argv);                 // Initialize GLUT
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(640, 640);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display);
    initGL();                   //Custom init function to define parameters for this project
    glutMainLoop();
    
    
    return 0;
}
