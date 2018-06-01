#include <iostream>

#include "Predator.h"

Predator::Predator(){}
Predator::Predator(float x, float y) : Turtle(x, y) {
  vision = 300;
  life = 600;
};

Vector2d Predator::separate(vector<Predator> predators){
	Vector2d steer;

	int count = 0; 

	for( int i = 0; i < predators.size(); i++){
		Vector2d otherPosition = predators[i].getPosition();

		float distance = Vector2d::dist(position, otherPosition);
		
		if ( distance > 0 && distance < Predator::desiredSeparation ) {
			// Calculate vector pointing away from neighbor
			Vector2d diff = Vector2d::sub(position, otherPosition);
			diff.normalize();
			diff.div(distance);        // Weight by distance
			steer.add(diff);
			count++;            // Keep track of how many
		}
	}

	if (count > 0) {
    steer.div((float)count);
  }

  // As long as the vector is greater than 0
  if (steer.magnitude() > 0) {
    // First two lines of code below could be condensed with new PVector setMag() method
    // Not using this method until Processing.js catches up
    // steer.setMag(maxspeed);

    // Implement Reynolds: Steering = Desired - Velocity
    steer.setMagnitude(maxSpeed);
    steer.sub(velocity);
    steer.limit(maxForce);
  }
  return steer;
};
Vector2d Predator::seek(Vector2d target){
	Vector2d desired = Vector2d::sub(target, position);  // A vector pointing from the position to the target
  // Scale to maximum speed
  desired.setMagnitude(maxSpeed);

  // Steering = Desired minus Velocity
  Vector2d steer = Vector2d::sub(desired, velocity);
  steer.limit(maxForce);  // Limit to maximum steering force
  return steer;
};
void Predator::eat(vector<Boid>& preys, int hunted){
  preys.erase(preys.begin()+hunted);
  life += 500;
}
Vector2d Predator::hunt(vector<Boid>& preys){
  Vector2d closest;   // Start with empty vector to accumulate all positions
  bool anyClose = false;
  
  for(int i = 0; i < preys.size(); i++) {
    Vector2d otherPosition = preys[i].getPosition();
    float distance = Vector2d::dist(position, otherPosition);

    if( distance < 2 * sideLength ){
      eat(preys, i);
    }

    if( distance > 0 && distance < vision) {
      anyClose = true;
      closest = otherPosition;
    }
  }
  if( anyClose )
    return seek(closest);
  else
    return Vector2d();
}
void Predator::move(vector<Predator>& predators, vector<Boid>& preys){
	Vector2d sep = separate(predators);   // Separation
  Vector2d hun = hunt(preys);
	// Arbitrarily weight these forces
	sep.mult(1);
  hun.mult(2);
  	// Add the force vectors to acceleration
 	applyForce(sep);
  applyForce(hun);
};
bool Predator::run(vector<Predator>& predators, vector<Boid>& preys, 
                                    float velocityFactor, float maxWidth, float maxHeight, bool starvationDeath){
  if( !isAlive(starvationDeath) ) return false;
  
  move(predators, preys);
  update(velocityFactor, starvationDeath);
  borders(maxWidth, maxHeight);
  render(1, 0, 0, starvationDeath);

  return true;
}

Predator::~Predator() {}
