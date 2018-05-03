
#include "Vector2d.h"

using namespace std;

Vector2d::Vector2d(){
	x = 0;
	y = 0;
}
Vector2d::Vector2d(float x, float y){
	this->x = x;
	this->y = y;
}
float Vector2d::dist(Vector2d v1, Vector2d v2){
	float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrt(dx*dx + dy*dy);
};
Vector2d Vector2d::sub(Vector2d v1, Vector2d v2){
	return Vector2d(v1.x - v2.x, v1.y - v2.y);
};
float Vector2d::getX(){ return x; }
void Vector2d::setX(float x){ this->x = x; };
float Vector2d::getY(){ return y; }
void Vector2d::setY(float y){ this->y = y; };
tuple<float, float> Vector2d::getTuple(){
	return make_tuple(x, y);
}
void Vector2d::setXY(float x, float y){
	setX(x);
	setY(y);
}
void Vector2d::add(Vector2d v2d){
	x += v2d.getX();
	y += v2d.getY();
};
void Vector2d::sub(Vector2d v2d){
	x -= v2d.getX();
	y -= v2d.getY();
};
Vector2d& Vector2d::mult(float scalar){
	x *= scalar;
	y *= scalar;
	return *this;
}
Vector2d& Vector2d::div(float scalar){
	x /= scalar;
	y /= scalar;
	return *this;
}
float Vector2d::magnitude(){
	return sqrt( x*x + y*y );
};
Vector2d& Vector2d::normalize(){
	float m = magnitude();
    if (m != 0 && m != 1) {
      div(m);
    }
    return *this;
}
Vector2d& Vector2d::setMagnitude(float len){
	normalize();
	mult(len);
	return *this;
}
Vector2d& Vector2d::limit(float max){
	if( magnitude() > max * max ){
		normalize();
		mult(max);
	}
	return *this;
};
float Vector2d::heading(){
	float angle = (float) atan2(y, x);
    return angle;
}
Vector2d::~Vector2d(){}