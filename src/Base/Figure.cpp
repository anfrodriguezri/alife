#include <tuple>

#include "Figure.h"

Figure::Figure() {}

float Figure::getX(Vector2d v){ return v.getX(); }
float Figure::getY(Vector2d v) { return v.getY(); }
float Figure::getAngle () { return angle; }
void Figure::setX(float x, Vector2d& v) { v.setX(x); }
void Figure::setY(float y, Vector2d& v) { v.setY(y); }
void Figure::setAngle(float angle) { this->angle = angle; }
Vector2d Figure::getPosition(){
	return position;
};
void Figure::setPosition(float x, float y){
	setX(x, position);
	setY(y, position);
};
Figure::~Figure() {}