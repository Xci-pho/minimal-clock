
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

const GLdouble PI = std::acos(-1);

void display();
void reshape(GLsizei width, GLsizei height);
void initOpenGL();
void Timer(GLint value);
void drawClock();

void drawHourHand();
void drawMinuteHand();
void drawSecondHand();

GLint refreshTimeMillis = 1000;
// elasped time in seconds
GLint elaspedTime = 0;


    void initOpenGL() {
    glClearColor(1, 1, 1, 1.0);
}



void drawCircle(GLdouble cx, GLdouble cy, GLfloat r, GLint steps) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        GLfloat angle;
        for (GLint i = 0; i <= steps; ++i) {
            angle = i * 2.0f * PI / steps;
            glVertex2f(std::cos(angle) * r + cx, std::sin(angle) * r + cy);
        }
    glEnd();
}

void drawRectangle(GLdouble x, GLdouble y, GLdouble w, GLdouble h) {
    glBegin(GL_QUADS);

        glVertex2d(x, y);
        glVertex2d(x, y + h);
        glVertex2d(x - w, y + h);
        glVertex2d(x - w, y);

    glEnd();
}






void Timer(GLint value) {
    glutPostRedisplay();
    ++elaspedTime;
    glutTimerFunc(refreshTimeMillis, Timer, 0);
}

void display() {
    glClearColor(0.976, 0.725, 0.203, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// To operate on Model-View matrix
	glMatrixMode(GL_MODELVIEW);
	// Reset the Model-View matrix
	glBegin(GL_QUADS);
	glColor3ub(33,33,33);
	glVertex2f(-1.05,-2);
	glVertex2f(-1.05,.5);
	glVertex2f(+1.05,.5);
	glVertex2f(1.05,-2);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(126, 72, 37);
	glVertex2f(-1,-2);
	glVertex2f(-1,.5);
	glVertex2f(+1,.5);
	glVertex2f(1,-2);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(33,33,33);
	glVertex2f(-1.05,.5);
	glVertex2f(0,1.55);
	glVertex2f(+1.05,.5);
	//glVertex2f(1,-2);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3ub(126, 72, 37);
	glVertex2f(-1,.5);
	glVertex2f(0,1.5);
	glVertex2f(+1,.5);
	//glVertex2f(1,-2);
	glEnd();



	glBegin(GL_QUADS);
	glColor3ub(62,39,35);
	glVertex2f(-.7,-1.5);
	glVertex2f(-.7,-.7);
	glVertex2f(.7,-.7);
	glVertex2f(.7,-1.5);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(33,33,33);
	glVertex2f(-.4,-1.2);
	glVertex2f(-.4,1);
	glVertex2f(.4,1);
	glVertex2f(.4,-1.2);
	glEnd();

	glLoadIdentity();

	drawClock();

    glutSwapBuffers();
}


void drawFrame() {
    glColor3ub(54, 54, 54);
    drawCircle(0.0, 0.0, .5, 100);

    glColor3ub(126, 72, 37);
    drawCircle(0.0, 0.0, .435, 100);
}

void drawHourTicks() {
    glColor3ub(54, 54, 54);
    GLdouble angle = 30.0;
    for (int i = 0; i < 12; ++i) {
        glPushMatrix();
            glRotated(angle * i, 0.0, 0.0, 1.0);
            drawRectangle(0.435, -0.01, 0.05, 0.02);
        glPopMatrix();
    }
}

void drawMinuteTicks() {
    glColor3ub(33,33,33);
    GLdouble angle = 6.0;
    for (int i = 0; i < 60; ++i) {
        glPushMatrix();
            glRotated(angle * i, 0.0, 0.0, 1.0);
            drawRectangle(0.435, -0.005, 0.02, 0.01);
        glPopMatrix();
    }
}

GLint hourAngle = 30.0;
void drawHourHand() {
    glColor3ub(54, 54, 54);
    glPushMatrix();

        glRotated((-1) * hourAngle * (elaspedTime / 3600) + 90, 0.0, 0.0, 1.0);
        drawRectangle(0.2, -0.0125, 0.25, 0.025);

    glPopMatrix();
}

GLint minuteAngle = 6.0;
void drawMinuteHand() {
    glColor3ub(54, 54, 54);
    glPushMatrix();

        glRotated((-1) * minuteAngle * (elaspedTime / 60) + 90, 0.0, 0.0, 1.0);
        drawRectangle(0.335, -0.01, 0.35, 0.02);

    glPopMatrix();
}

GLint secondAngle = 6.0;
void drawSecondHand() {
    glColor3ub(205, 30, 30);
    glPushMatrix();

        glRotated((-1) * secondAngle * elaspedTime + 90, 0.0, 0.0, 1.0);
        drawRectangle(0.435, -0.005, 0.535, 0.01);

    glPopMatrix();
}

void drawMidNob() {
    glColor3ub(25, 25, 25);
    drawCircle(0.0, 0.0, 0.025, 50);
}

void drawClock() {
    gluOrtho2D(-2.0f,2.0f,-2.0f,2.0f);
    drawFrame();
    drawMinuteTicks();
    drawHourTicks();
    drawHourHand();
    drawMinuteHand();
    drawSecondHand();
    drawMidNob();
}


void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}

int main(int argc, char **argv) {
    // Initialize glut
    glutInit(&argc, argv);

    // Set display mode
    // GLUT_DOUBLE - enable double buffering
    // GLUT_RGBA - RGBA color for display
//    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    // Set window size
    glutInitWindowSize(800, 800);

    // Set window position
    glutInitWindowPosition(100, 100);

    // Create the window
    glutCreateWindow("Analog Clock");

    // Initialize OpenGL
    initOpenGL();

    // Set the display function callback, which will be called
    // over and over again, from glut's main loop
    glutDisplayFunc(display);

    // Callback for when glut will remain idle
    // glutIdleFunc(display);

    // Callback for when the window state is changed (like resize)
    glutReshapeFunc(reshape);

    // Callback for controlling timer (FPS)
    glutTimerFunc(0, Timer, 0);

    // Start the main loop
    glutMainLoop();

    return 0;
}

