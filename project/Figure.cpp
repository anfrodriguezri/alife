/*
 * Figure.cpp
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#include <tuple>

#include "Figure.h"

#include <iostream>

Figure::Figure() {}

float Figure::getX(Vector2d v){ return get<0>(v); }
float Figure::getY(Vector2d v) { return get<1>(v); }
float Figure::getAngle () { return angle; }
void Figure::setX(float x, Vector2d& v) { get<0>(v) = x; }
void Figure::setY(float y, Vector2d& v) { get<1>(v) = y; }
void Figure::setAngle(float angle) { this->angle = angle; }
Vector2d Figure::getPosition(){
	return position;
};
void Figure::setPosition(float x, float y){
	setX(x, position);
	setY(y, position);
};
Figure::~Figure() {}