/*
 * oglhelpers.h
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#ifndef OGLHELPERS_H_
#define OGLHELPERS_H_

#include <GL/freeglut.h>
#include <string>
#include <math.h>

void drawString(std::string);
void drawLine(GLfloat, GLfloat, GLfloat, GLfloat);
void drawTriangle(float x, float y, float theta, float sideLength);

#endif /* OGLHELPERS_H_ */
