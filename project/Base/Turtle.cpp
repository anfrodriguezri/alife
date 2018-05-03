#include <iostream>

#include "Turtle.h"

#include <tuple>
#include <math.h>

#include "../helpers/oglhelpers.h"

using namespace std;

Turtle::Turtle() {}

Turtle::Turtle(float x, float y) {
	acceleration.setXY( 0, 0 );
	
	float randFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float angle = (randFloat * 2 * M_PI);

	velocity.setXY( cos(angle), sin(angle) );
	
	position.setXY( x, y );

	maxSpeed = 2;
	maxForce = 0.3;
	sideLength = 4;
	life = 1;
}
Vector2d Turtle::getVelocity(){
	return velocity;
}
Vector2d Turtle::getAcceleration(){
	return acceleration;
}
void Turtle::applyForce(Vector2d force){
	acceleration.add(force);
};
void Turtle::update(float velocityFactor) {
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	velocity.mult(velocityFactor);
	position.add(velocity);
	acceleration.mult(0);
}
void Turtle::borders(float width, float height) {
	float x = position.getX();
	float y = position.getY();

	if (x < -sideLength) position.setX(width + sideLength);
    if (y < -sideLength) position.setY(height + sideLength);
    if (x > width + sideLength) position.setX(-sideLength);
    if (y > height + sideLength) position.setY(-sideLength);
}

void Turtle::render(float r, float g, float b) {
	// Draw a triangle rotated in the direction of velocity
	float theta = velocity.heading() * RADTODEG + 90;
	glColor3f(r, g, b);
	drawTriangle(position.getX(), position.getY(), theta, sideLength);
}

void Turtle::run(float velocityFactor, float maxWidth, float maxHeight) {
	if( life > 0 ){
		update(velocityFactor);
		borders(maxWidth, maxHeight);
		render(1, 1, 1);
	}
}
void Turtle::die(){
	life = 0;
}
Turtle::~Turtle() {}