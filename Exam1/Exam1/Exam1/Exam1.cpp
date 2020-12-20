/*
    -----------------------------------------------------------
    * Programmer--Jacob Hisscock
    * Course------CS 3233
    * Project-----Exam #1 Part 2: Hexagonal Bipyramid
    * Due---------October 12th, 2020
    *
    * This program creates and displays a 3D hexagonal bipyramid
    *-----------------------------------------------------------
*/
#include <GL/glut.h>
#include <iostream> 

GLfloat angle = 0.0f;
GLfloat angleX = 0.0f;
GLfloat angleY = 1.0f;
GLfloat angleZ = 0.0f;
GLfloat speed = 1.0f;

void initGL() {
    //Enables projection view for showing depth calculations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set background to black
    glClearDepth(1.0f); //Clear current depth

    glEnable(GL_DEPTH_TEST); //Enable use of depth calculations
    glDepthFunc(GL_LEQUAL);

    
}

void hexagonalBipyramid() {
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f); // Move object back into the scene to be more easily visible and center it
    glRotatef(angle, angleX, angleY, angleZ); // Rotate about the user specified axis/axes by angle

    //Define x and z coordiantes for hexagonal pyrazmid
    float x[] = { 0.866f, 0.0f, -0.866f, -0.866f,  0.0f,  0.866f };
    float z[] = { 0.5f,   1.0f,  0.5f,   -0.5f,   -1.0f, -0.5f };

    //Define the colors for each of the top triangles
    float colorXTop[] = { 1.0f,   0.0f,  0.0f,   1.0f,   1.0f, 0.0f };
    float colorYTop[] = { 0.0f,   1.0f,  0.0f,   0.0f,   1.0f, 1.0f };
    float colorZTop[] = { 0.0f,   0.0f,  1.0f,   1.0f,   0.0f, 1.0f };

    //Define the colors for each of the bottom triangles
    float colorXBottom[] = { 0.2f,   0.7f,  0.0f,   1.0f,   1.0f, 0.4f };
    float colorYBottom[] = { 0.1f,   0.0f,  1.0f,   0.7f,   0.5f, 0.0f };
    float colorZBottom[] = { 0.5f,   0.3f,  0.5f,   0.2f,   1.0f, 0.8f };

    //draw top triangles
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; ++i)
    {
        //sets color for each triangle on top
        glColor3f(colorXTop[i], colorYTop[i], colorZTop[i]);

        int j = (i + 1) % 6; // j will equal 0 when i equals 5 to create the last triangle
        glVertex3f(0.0f, 1.5f, 0.0f); //Top point drawn for every traingle

        //Pairs the i + 1 (j) index of x[] and z[] with the i index of x[] and z[]
        glVertex3f(x[j], 0.0f, z[j]);
        glVertex3f(x[i], 0.0f, z[i]);
    }
    glEnd();

    //draw bottom triangles
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; ++i)
    {
        //sets color for each triangle on the bottom
        glColor3f(colorXBottom[i], colorYBottom[i], colorZBottom[i]);

        int j = (i + 1) % 6;
        glVertex3f(0.0f, -1.5f, 0.0f);

        // Pairs the i index of x[] and z[] with the i + 1 (j) index of x[] and z[]
        glVertex3f(x[i], 0.0f, z[i]);
        glVertex3f(x[j], 0.0f, z[j]);
    }
    glEnd();
}


//function that increments angle by one until it reaches 360 and then resets back to zero and continues incrementing
void timer(int v) {
    angle += speed; //increment angle by user entered speed value.
    if (angle > 360.0) {
        angle = 0;
    }
    glutPostRedisplay(); //Redraws image with new rotation applied

    glutTimerFunc(1000 / 60, timer, v);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    hexagonalBipyramid();

    glFlush();
    glutSwapBuffers();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    //Take user input to determin axis of rotation and rotation speed.
    std::cout << "Enter axis of rotation 0 to not include that axis and 1 to include the axis i.e. x = 0, y = 1, z = 0 would rotate about the y axis. \nAny number between 0 and 1 will rotate at a fraction of that angle. \nx: ";
    std::cin >> angleX;
    std::cout << "y: ";
    std::cin >> angleY;
    std::cout << "z: ";
    std::cin >> angleZ;
    std::cout << "Enter speed of rotation, 0 for no rotation, default is 1, and anything greater than 1 will further increase the speed of rotation, values can be decimals. \nSpeed: ";
    std::cin >> speed;

    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);       //Enables the use of swapBuffers for the use of the time function for rotation
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
    glutInitWindowSize(320, 320);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);  //Calls timer function to begin rotation
    initGL();                   //Custom init function to define parameters for this project
    glutMainLoop();           // Enter the infinitely event-processing loop
    return 0;
}
