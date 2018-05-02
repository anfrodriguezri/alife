/*
 * Turtle.h
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */
#ifndef TURTLE_H_
#define TURTLE_H_

#include <tuple>

#include "Figure.h"

using namespace std;

class Turtle : public Figure {
	protected:
		tuple<float, float> velocity;
		tuple<float, float> acceleration;
		float maxForce; // max steering force to change velocity direction
		float maxSpeed;
	public:
		Turtle();
		Turtle(float, float);
		virtual ~Turtle();
};

#endif /* TURTLE_H_ */
