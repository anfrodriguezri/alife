/*
 * Figure.cpp
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#include <tuple>

#include "Figure.h"

Figure::Figure() {
	// TODO Auto-generated constructor stub
}

Figure::~Figure() {
	// TODO Auto-generated destructor stub
}

float Figure::getX(){ return get<0>(position); }
float Figure::getY() { return get<1>(position); }
float Figure::getAngle () { return angle; }
void Figure::setX(float x) { get<0>(position) = x; }
void Figure::setY(float y) { get<1>(position) = y; }
void Figure::setAngle(float angle) { this->angle = angle; }
