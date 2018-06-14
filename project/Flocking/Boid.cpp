#include <iostream>

#include "Boid.h"

Boid::Boid(float x, float y, float r, float g, float b, GLuint texture) : Turtle(x, y, r, g, b, texture) {
  alreadyReproduced = false;

  maxSpeed = 2;
  life = 400;
  sideLength = 22;
  maxForce = 0.02;

  reproductionProb = .2;
}
Boid::Boid(float x, float y, float r, float g, float b, GLuint texture, 
                    int life, float vision, float maxSpeed) : Turtle(x, y, r, g, b, texture) {
  alreadyReproduced = false;

  this->maxSpeed = maxSpeed;
  this->life = life;
  this->vision = vision;

  sideLength = 22;

  reproductionProb = .3;
}
float Boid::fit_value(Boid boid){
  if( boid.getAlreadyReproduced() )
    return 0;

  return boid.getLife() + boid.getVision() + boid.getMaxSpeed();
};
string Boid::encode(Boid boid){
  string code;
  code += intToBits( boid.getLife() );
  code += floatToBits( boid.getVision() );
  code += floatToBits( boid.getMaxSpeed() );
  code += floatToBits( boid.getR() );
  code += floatToBits( boid.getG() );
  code += floatToBits( boid.getB() );

  return code;
};
Boid Boid::decode(string dna, float x, float y, GLuint texture){
  string sub = dna.substr(0*32,32);
  int life = bitsToInt(sub);

  sub = dna.substr(1*32,32);
  float vision = bitsToFloat(sub);
  
  sub = dna.substr(2*32,32);
  float maxSpeed = bitsToFloat(sub);
  
  sub = dna.substr(3*32,32);
  float r = bitsToFloat(sub);

  sub = dna.substr(4*32,32);
  float g = bitsToFloat(sub);
  
  sub = dna.substr(5*32,32);
  float b = bitsToFloat(sub);

  return Boid(x, y, r, g, b, texture, life, vision, maxSpeed);
}
Vector2d Boid::separate(vector<Boid> boids){
	Vector2d steer;

	int count = 0; 

	for( int i = 0; i < boids.size(); i++){
		Vector2d otherPosition = boids[i].getPosition();

		float distance = Vector2d::dist(position, otherPosition);
		
		if ((distance > 0) && (distance < 2.2*sideLength)) {
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
void Boid::eat(Vector2d foodPosition, Sandpile sandpile){
  life += sandpile.getResource(foodPosition);;
}
Vector2d Boid::search_food(Sugarscape sugarscape){
  Vector2d closest;
  bool anyClose = false;
  vector<Sandpile> sandpiles = sugarscape.getSandpiles();

  if( sugarscape.isPresent() ){
    for( Sandpile sandpile : sandpiles ){
    
      Vector2d sandpilePosition = sandpile.getPosition();

      float distance = Vector2d::dist(position, sandpilePosition);
      distance -= sandpile.getRadious();
      
      if( distance > 0 && distance < vision) {
        anyClose = true;
        
        closest = sandpile.getBestGrainLocation(position);

        float distanceToClosest = Vector2d::dist(position, closest);
        
        if( distance < sandpile.getCapacity() / 10 ){
          eat(closest, sandpile);
        }
      }
    }
  }
  
  if( anyClose )
    return seek(closest);
  else
    return Vector2d();
}
vector<string> Boid::crossover(string dna1, string dna2){
  int pos = rand() % (dna1.size()-1) + 1;
  vector<string> offspring;

  offspring.push_back(dna1);
  offspring.push_back(dna2);

  
  for( int i = pos; i < dna1.size(); i++ ){
    offspring[0][i] = dna2[i];
    offspring[1][i] = dna1[i];
  }
  return offspring;
}
void Boid::mutate(string& dna){
  double p = .3;
  
  for( int i=0; i < dna.size(); i++ ){
    if( randFloat(0,1) < p ){
      if( dna[i] == '0' ) dna[i] = '1';
      if( dna[i] == '1' ) dna[i] = '0';
    }
  }
}
bool Boid::getAlreadyReproduced(){
  return alreadyReproduced;
}
void Boid::setAlreadyReproduced(bool ar){
  alreadyReproduced = ar;
};
void Boid::reproduce(vector<Boid>& preys, int mate_index){
  //alreadyReproduced = true;
  //preys[mate_index].setAlreadyReproduced(true);

  string this_dna = Boid::encode(*this);
  string mate_dna = Boid::encode(preys[mate_index]);
  
  vector<string> offspring = Boid::crossover(this_dna, mate_dna);
  
  Boid::mutate(offspring[0]); 
  
  Vector2d parentsPosition = this->getPosition();
  float distance = 4 * sideLength;
  // Boid o = Boid::decode(offspring[0], parentsPosition.getX()+distance, parentsPosition.getY()+distance,
  //                                  this->r, this->g, this->b, this->texture);

  
  // cout << o.toString() << endl;
  //preys.push_back(Boid::decode(offspring[0], parentsPosition.getX()+distance, parentsPosition.getY()+distance,
                                 // 0, this->g, 0, this->texture));
  
  preys[mate_index] = Boid::decode(offspring[0], parentsPosition.getX()+distance, parentsPosition.getY()+distance, this->texture);
  
}
Vector2d Boid::mate_selection(vector<Boid>& boids, bool& reproduced){
    Vector2d closest_fittest;
    float fittest_value = -1;
    bool anyClose = false;

    for(int i = 0; i < boids.size(); i++) {
      Vector2d otherPosition = boids[i].getPosition();
      float distance = Vector2d::dist(position, otherPosition);

      if( distance > 0 && distance < 3.5 * sideLength ){
        if( randFloat(0, 1) < reproductionProb ){
          reproduced = true;
          reproduce(boids, i);
        }
      }

      if( distance > 0 && distance < vision) {
        float others_fit_value = Boid::fit_value(boids[i]);
        anyClose = true;
        if( others_fit_value > fittest_value ){
          closest_fittest = otherPosition;  
          fittest_value = others_fit_value;
        }
      }
    }

    if( anyClose )
      return seek(closest_fittest);
    else
      return Vector2d();
};
void Boid::flock(vector<Boid>& boids, vector<Predator>& predators, Sugarscape sugarscape, bool reproducing, bool& reproduced){
	Vector2d sep = separate(boids);   // Separation
  Vector2d ali = align(boids);      // Alignment
  Vector2d coh = cohere(boids);   // Cohesion
  Vector2d esc = escape(predators);   // Cohesion
  Vector2d food = search_food(sugarscape);
  Vector2d selec;
  if( reproducing && !alreadyReproduced ){
    selec = mate_selection(boids, reproduced);
  }
  else
    selec = Vector2d();

  // Arbitrarily weight these forces
  sep.mult(1.5);
  ali.mult(1);
  coh.mult(1);
  esc.mult(3);
  food.mult(1.5);
  selec.mult(3);
  // Add the force vectors to acceleration
  applyForce(sep);
  applyForce(ali);
  applyForce(coh);
  applyForce(esc);
  applyForce(food);
  applyForce(selec);
};
bool Boid::run(vector<Boid>& boids, vector<Predator>& predators, Sugarscape sugarscape,
                      float velocityFactor, float maxWidth, float maxHeight, bool starvationDeath, bool reproducing, bool& reproduced) {
  if( !isAlive(starvationDeath) ) return false;

  flock(boids, predators, sugarscape, reproducing, reproduced);
  update(velocityFactor, starvationDeath);
  borders(maxWidth, maxHeight);
  render(starvationDeath);
  
  return true;
}
string Boid::toString(){
  string s;
  s+= "Life: " + to_string(life);
  s+= ", vision: " + to_string(vision);
  s+= ", maxSpeed: " + to_string(maxSpeed);
  return s;
};
Boid::~Boid() {}