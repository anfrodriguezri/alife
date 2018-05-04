#include <iostream>

#include "Boid.h"

Boid::Boid() {}

Boid::Boid(float x, float y) : Turtle(x, y) {
  maxForce = 0.28;
}
Vector2d Boid::separate(vector<Boid> boids){
	Vector2d steer;

	int count = 0; 

	for( int i = 0; i < boids.size(); i++){
		Vector2d otherPosition = boids[i].getPosition();

		float distance = Vector2d::dist(position, otherPosition);
		
		if ((distance > 0) && (distance < Boid::desiredSeparation)) {
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
Vector2d Boid::align(vector<Boid> boids){
  Vector2d sum;
  int count = 0;
  for (int i = 0; i < boids.size(); i++) {
  	Vector2d otherPosition = boids[i].getPosition();
  	Vector2d otherVelocity = boids[i].getVelocity();

  	float distance = Vector2d::dist(position, otherPosition);
  	
  	if ((distance > 0) && (distance < vision)) {
  		sum.add(otherVelocity);
  		count++;
  	}
  }

  if (count > 0) {

    sum.div((float)count);

    // Implement Reynolds: Steering = Desired - Velocity
    sum.setMagnitude(maxSpeed);
    Vector2d steer = Vector2d::sub(sum, velocity);
    steer.limit(maxForce);
    return steer;
  }else {
    return Vector2d();
  }
};
Vector2d Boid::seek(Vector2d target){
	Vector2d desired = Vector2d::sub(target, position);  // A vector pointing from the position to the target
    // Scale to maximum speed
    desired.setMagnitude(maxSpeed);

    // Steering = Desired minus Velocity
    Vector2d steer = Vector2d::sub(desired, velocity);
    steer.limit(maxForce);  // Limit to maximum steering force
    return steer;
};
Vector2d Boid::cohere(vector<Boid> boids){
    Vector2d sum;   // Start with empty vector to accumulate all positions
    int count = 0;

    for(int i = 0; i < boids.size(); i++) {
    	Vector2d otherPosition = boids[i].getPosition();
  		float distance = Vector2d::dist(position, otherPosition);

  		if ((distance > 0) && (distance < vision)) {
  			sum.add(otherPosition); // Add position
  			count++;
  		}
    }
    if (count > 0) {
  		sum.div(count);
  		return seek(sum);  // Steer towards the position
    }else {
    	return Vector2d();
    }
};
Vector2d Boid::escape(vector<Predator> predators){
  Vector2d steer;

  int count = 0; 

  for( int i = 0; i < predators.size(); i++){
    Vector2d otherPosition = predators[i].getPosition();

    float distance = Vector2d::dist(position, otherPosition);
    
    if ((distance > 0) && (distance < vision)) {
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
}
void Boid::flock(vector<Boid>& boids, vector<Predator>& predators){
	Vector2d sep = separate(boids);   // Separation
  Vector2d ali = align(boids);      // Alignment
  Vector2d coh = cohere(boids);   // Cohesion
  Vector2d esc = escape(predators);   // Cohesion
  // Arbitrarily weight these forces
  sep.mult(1.5);
  ali.mult(1);
  coh.mult(1);
  esc.mult(2);
  // Add the force vectors to acceleration
  applyForce(sep);
  applyForce(ali);
  applyForce(coh);
  applyForce(esc);
};
void Boid::run(vector<Boid>& boids, vector<Predator>& predators, float velocityFactor, float maxWidth, float maxHeight) {
  flock(boids, predators);
  update(velocityFactor);
  borders(maxWidth, maxHeight);
  render(1, 1, 1);
}

Boid::~Boid() {}