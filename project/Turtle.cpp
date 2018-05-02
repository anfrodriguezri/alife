#include <iostream>

#include "Turtle.h"

#include <tuple>
#include <math.h>

#include "oglhelpers.h"

using namespace std;

Turtle::Turtle() {}

Turtle::Turtle(float x, float y) {
	setPosition(x, y);

	acceleration.setXY( 0, 0 );
	
	float randFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float angle = (randFloat * 2 * M_PI + 0);

	velocity.setXY( cos(angle), sin(angle) );
	
	position.setXY( x, y );

	maxSpeed = 2;
	maxForce = 0.03;
}

void Turtle::applyForce(Vector2d force){
	acceleration.add(force);
};

void Turtle::update() {
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	velocity.mult(3);
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

void Turtle::render() {
	// Draw a triangle rotated in the direction of velocity
	float theta = velocity.heading() + 90 * DEGTORAD;

	drawTriangle(position.getX(), position.getY(), theta, sideLength);
}

void Turtle::run(float maxWidth, float maxHeight) {
	update();
	borders(maxWidth, maxHeight);
	render();
}
Turtle::~Turtle() {}