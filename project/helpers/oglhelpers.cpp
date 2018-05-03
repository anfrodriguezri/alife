#include <iostream>

#include "oglhelpers.h"

using namespace std;

void drawString(std::string message){
    std::string::iterator it = message.begin();

    for (; it != message.end(); ++it)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *it);
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void drawTriangle(float x, float y, float theta, float sideLength){
	glPushMatrix();
		glTranslatef(x, y, 0);
	    glRotatef(theta, 0, 0, 1);

	    glBegin(GL_TRIANGLES);
	        glVertex3f(0, -sideLength*2, 0);
	        glVertex3f(-sideLength, sideLength*2, 0);
	        glVertex3f(sideLength, sideLength*2, 0);
	    glEnd();
    glPopMatrix();
}