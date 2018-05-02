/*
 * Turtle.cpp
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#include "Turtle.h"

#include <tuple>
#include <math.h>

using namespace std;

Turtle::Turtle() {}

Turtle::Turtle(float x, float y) {
	setPosition(x, y);

	acceleration = make_tuple(0, 0);
	
	float randFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float angle = (randFloat * 2 * M_PI + 0);
	velocity = make_tuple( cos(angle), sin(angle) );
}

Turtle::~Turtle() {}