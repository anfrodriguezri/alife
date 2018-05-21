#include <iostream>

#include "Turtle.h"

#include <tuple>
#include <math.h>

#include "../helpers/oglhelpers.h"

using namespace std;

Turtle::Turtle() {}

float Turtle::desiredSeparation = 25;

Turtle::Turtle(float x, float y) {
	acceleration.setXY( 0, 0 );
	
	float randFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float angle = (randFloat * 2 * M_PI);

	velocity.setXY( cos(angle), sin(angle) );
	
	position.setXY( x, y );

	maxSpeed = 2;
	maxForce = 0.3;
	sideLength = 8;
	life = 1;
	vision = 50;
}
Vector2d Turtle::getVelocity(){
	return velocity;
}
Vector2d Turtle::getAcceleration(){
	return acceleration;
}
int Turtle::getLife(){
	return life;
}
void Turtle::applyForce(Vector2d force){
	acceleration.add(force);
};
void Turtle::update(float velocityFactor, bool starvationDeath) {
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	velocity.mult(velocityFactor);
	position.add(velocity);
	acceleration.mult(0);

	if( starvationDeath )
		life -= 1;
}
void Turtle::borders(float width, float height) {
	float x = position.getX();
	float y = position.getY();

	if (x < -sideLength) position.setX(width + sideLength);
    if (y < -sideLength) position.setY(height + sideLength);
    if (x > width + sideLength) position.setX(-sideLength);
    if (y > height + sideLength) position.setY(-sideLength);
}

void Turtle::render(float r, float g, float b, bool starvationDeath){
	// Draw a triangle rotated in the direction of velocity
	GLuint loadBMP_custom(const char * imagepath);
	GLuint image = loadBMP_custom("./texture.bmp");
	float theta = velocity.heading() * RADTODEG + 90;
	glColor3f(r, g, b);
	drawTriangle(position.getX(), position.getY(), theta, sideLength);
	if( starvationDeath ){
		drawString(to_string(life), position.getX() - 20, position.getY() - 30);
	}
}
bool Turtle::isAlive(bool starvationDeath){
	return !(life == 0 && starvationDeath);
}
bool Turtle::run(float velocityFactor, float maxWidth, float maxHeight, bool starvationDeath){
	if( !isAlive(starvationDeath) ) return false;

	update(velocityFactor, starvationDeath);
	borders(maxWidth, maxHeight);
	render(1, 1, 1, starvationDeath);
	
	return true;
}
Turtle::~Turtle() {}