#include <iostream>

#include "Turtle.h"

#include <tuple>
#include <math.h>

#include "../helpers/helpers.h"

using namespace std;

Turtle::Turtle() {}

Turtle::Turtle(float x, float y, float r, float g, float b, GLuint texture) {
	acceleration.setXY( 0, 0 );
	
	float randFloat = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float angle = (randFloat * 2 * M_PI);

	velocity.setXY( cos(angle), sin(angle) );
	
	position.setXY( x, y );

	maxSpeed = 2;
	maxForce = 0.3;
	sideLength = 15;
	life = 1;
	vision = 50;

	this->texture = texture;
	this->r = r;
	this->g = g;
	this->b = b;
}
float Turtle::getR(){
  return r;
}
float Turtle::getG(){
  return g;
}
float Turtle::getB(){
  return b;
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
float Turtle::getVision(){
	return vision;
}
float Turtle::getMaxSpeed(){
	return maxSpeed;
}
void Turtle::setTexture(int texture){
	this->texture = texture;
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

void Turtle::render(bool starvationDeath){
	// Draw a triangle rotated in the direction of velocity
	float theta = velocity.heading() * RADTODEG + 90;
	glColor3f(r, g, b);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	drawTriangle(position.getX(), position.getY(), theta, sideLength);
	glDisable(GL_TEXTURE_2D);
	
	if( starvationDeath ){
		drawString(to_string(life), position.getX() - 20, position.getY() - sideLength);
	}
}
bool Turtle::isAlive(bool starvationDeath){
	return !(life == 0 && starvationDeath);
}
bool Turtle::run(float velocityFactor, float maxWidth, float maxHeight, bool starvationDeath){
	if( !isAlive(starvationDeath) ) return false;

	update(velocityFactor, starvationDeath);
	borders(maxWidth, maxHeight);
	render(starvationDeath);
	
	return true;
}
Turtle::~Turtle() {}