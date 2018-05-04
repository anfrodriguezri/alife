#ifndef OGL_HELPERS_H_
#define OGL_HELPERS_H_

#include <GL/freeglut.h>
#include <string>
#include <math.h>

void drawString(std::string);
void drawLine(GLfloat, GLfloat, GLfloat, GLfloat);
void drawTriangle(GLfloat, GLfloat, GLfloat, GLfloat);
void drawCircle(GLfloat x, GLfloat y, GLfloat radius);

#endif /* OGL_HELPERS_H_ */
