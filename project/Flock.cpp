#include "Flock.h"


Flock::Flock() {}

void Flock::run(float maxWidth, float maxHeight){
	for( int i = 0; i < boids.size(); i++){
		boids[i].run(maxWidth, maxHeight);
	}
}

void Flock::addBoid(Turtle boid){
	boids.push_back(boid);
};

Flock::~Flock() {}