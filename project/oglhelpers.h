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

#define DEGTORAD M_PI/180.0f  // Grados a radianes

void DrawString(std::string);
void DrawLine(GLfloat, GLfloat, GLfloat, GLfloat);


#endif /* OGLHELPERS_H_ */
