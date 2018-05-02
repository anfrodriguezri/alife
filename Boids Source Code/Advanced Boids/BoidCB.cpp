#include "BoidCB.h"
#include "Boid.h"
#include "generalIncludes.h"

#include <iostream>

#define WALL_BOUNCE 0

#define B_NONE 0
#define B_SEPARATION 1
#define B_ALIGNMENT 2
#define B_COHESION 3
#define B_FLOCKING 4

/** Creates a new boid with default behaviours **/
BoidCB::BoidCB(double r, double x, double y, double dir, double vel, double vis, int ID)
{
	_x = x; _y = y; _radius = r;
	_theta = dir;
	_vel = vel;
	_dx = 0; _dy = 0;
	_vis = vis;
	_boidID = ID;

	//Set the weightings for each action
	_coheshion = 0.09;
	_separation = 0.28;
	_alignment = 0.10;
	_flee = 0.05;
	_obstacleAvoid = 0.24;

	setRandom = false;

	behaviour = B_FLOCKING;	//Set action to flocking (This method calls all flocking fucntions)
	wall_behaviour = WALL_BOUNCE;
}
/** Returns current x coordinate of boid's position **/
double BoidCB::getX(){ return _x+_dx; }
/** Returns current y coordinate of boid's position **/
double BoidCB::getY(){ return _y+_dy; }
/** Returns current direction of travel **/
double BoidCB::getDir(){ return _theta; }
/** Returns current velocity **/
double BoidCB::getVel(){ return _vel; }

double BoidCB::getDX(){ return _dx; }
double BoidCB::getDY(){ return _dy; }

void BoidCB::setRandomPos()
{
	setRandom = true;
}

/** Returns the amount the boid will move each step in the x direction **/
double BoidCB::dirX(){ return _vel*sin(_theta); }
/** Returns the amount the boid will move ech step in the y direction **/
double BoidCB::dirY(){ return _vel*cos(_theta); }

/** The callback function.  Code in this function is executed repeatedly **/
void BoidCB::operator()( osg::Node* node, osg::NodeVisitor* nv )
{	
	if (setRandom)
	{	//Runs if the user requires the boid to be set to a random location
		//Done here to prevent osg bugs caused by changes while running
		setRandom = false;	//Don't run it again

		int position_found = 0,x,y;
		while(!position_found)
		{
			x = ((wall3->getCenter().x() * 2) - 1) * rand() / RAND_MAX - (((wall3->getCenter().x() * 2) - 1) / 2);
			y = ((wall1->getCenter().y() * 2) - 1) * rand() / RAND_MAX - (((wall1->getCenter().y() * 2) - 1) / 2);

			position_found = 1;
			for(int i = 0; i < ob_count; i++)
			{
				if(sqrt(pow(obstacles[i]->x-x,2)+pow(obstacles[i]->y-y,2)) < obstacles[i]->radius+_radius+0.1)
				{
					position_found = 0;
				}
			}
		}
		_x = x;
		_y = y;
		_dx = 0;
		_dy = 0;
		_theta = 2*M_PI*rand()/RAND_MAX;

		//Osg bits (For it to display correctly we need to adjust the boids shapes etc)
		boids[_boidID]->geode->removeDrawable(boids[_boidID]->draw);
		boids[_boidID]->shape = new Sphere(Vec3(x,y,0.5),_radius);
		boids[_boidID]->draw = new ShapeDrawable(boids[_boidID]->shape);
		boids[_boidID]->draw->setColor(Vec4(0,0,1,1));
		boids[_boidID]->geode->addDrawable(boids[_boidID]->draw);
	}

	//Sets up the tracking of movement
	/** These are used to determine what _theta should be after doing all the actions
	They are setup here and then adjusted per each function before finally adjusting _theta **/
	//These would be the normal movement without adjustments
	_newDX = (dirX() / (distance_to_pos(dirX(),dirY())) ) * _vel;	//Sets the temporary direction of X (This is equal to, "ammount of X movement / distance between X & Y movement) * velocity")
	_newDY = (dirY() / (distance_to_pos(dirX(),dirY())) ) * _vel;	//Sets the temporary direction of Y (This is equal to, "ammount of Y movement / distance between X & Y movement) * velocity")

	//calculate next movement
	perform_behaviour();			//Performs Flocking behaviour
	obstacle_avoidance();			//Obstacle avoidance (Needs to be done after behaviour, to allow it to alter the direction)
	if(wall_behaviour == WALL_BOUNCE){ wall_bounce(); }

	//Change _theta to the new direction
	_theta = atan2(_newDX, _newDY);	//Sets _theta based on the new cords (Obtained through adjustments in functions etc)

	//Normalise the angle
	if(_theta < -M_PI){ _theta += 2*M_PI; }
	if(_theta > M_PI){ _theta -= 2*M_PI; }

	//execute movement of the boid
	osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>( node );
	osg::Matrix mR, mT;
	_dx += dirX();
	_dy += dirY();
	mT.makeTranslate(_dx,_dy,0.0);
	mt->setMatrix( mT );

	//execute next callback
	traverse( node, nv );
}

/** If a is positive, boid will steer right, if a is negative, will steer left **/
void BoidCB::steer(double a){ _theta += a; }
/** If a is positive, boid will accelerate, if a is negative, will decelerate **/
void BoidCB::accelerate(double a){ _vel += a; }

/** Calculates the distance between the boid and obstacle[ob] **/
double BoidCB::distance_to_obstacle(int ob)
{
	return sqrt(pow(obstacles[ob]->x - getX(),2)+pow(obstacles[ob]->y - getY(),2));
}

/** Calculates the distance between the boid and boids[bd] **/
double BoidCB::distance_to_boid(int bd)
{
	return sqrt(pow(boids[bd]->getX() - getX(),2) + pow(boids[bd]->getY() - getY(),2));
}

/** Calculates the distance between the boids and specific position **/
double BoidCB::distance_to_pos(double x, double y)
{
	return sqrt(pow(x,2) + pow(y,2));
}

double BoidCB::angle_to_pos(double x, double y)
{
	double angle = atan2(x,y) - _theta;
	if (angle > M_PI)
		angle -= 2 * M_PI;
	if (angle < -M_PI)
		angle += 2 * M_PI;
	if ( (angle > M_PI/2) || (angle < -M_PI / 2) )
		return 0;
	return angle;
}

/** Calculates direction in which boid must turn to avoid colliding with obstacle ob **/
double BoidCB::collision(int ob)
{
	double dist = distance_to_obstacle(ob);
	double angle_to_centre = atan2((obstacles[ob]->x-getX()),obstacles[ob]->y-getY()) - _theta;
	if(angle_to_centre > M_PI){ angle_to_centre -= 2*M_PI; }
	if(angle_to_centre < -M_PI){ angle_to_centre += 2*M_PI; }
	if(angle_to_centre > M_PI/2 || angle_to_centre < -M_PI /2){ return 0; }
	double angle_centre_edge = asin((obstacles[ob]->radius+_radius)/dist);
	if(fabs(angle_to_centre) < fabs(angle_centre_edge))
	{
		if(angle_to_centre >= 0){ return -fabs(angle_centre_edge); }
		if(angle_to_centre < 0){ return fabs(angle_centre_edge); }
	}
	else{ return 0; }
}

/** Causes the boid to 'bounce' when it reaches a wall **/
void BoidCB::wall_bounce()
{	//Using our adjustment positions we get better results
	if ( (getX() < (wall4->getCenter().x()) && _newDX < 0) || (getX() > (wall3->getCenter().x()) && _newDX > 0) )
		_newDX = -_newDX;
	if ( (getY() < (wall2->getCenter().y()) && _newDY < 0) || (getY() > (wall1->getCenter().y()) && _newDY > 0) )
		_newDY = -_newDY;
}

/** This simply checks that we are not to close to an obstacle **/
bool BoidCB::obstacle_dis()
{
	for (int i = 0; i < ob_count; i++)
	{
		if (distance_to_obstacle(i) < (obstacles[i]->radius * 1.6))
			return true;
	}
	return false;
}

/** Causes the boid to avoid the obstacle **/
bool BoidCB::obstacle_avoidance()
{
	double obX = 0, obY = 0;
	bool didWeAvoid = false;	//Tells us whether we had to avoid anything
	for (int i = 0; i < ob_count; i++)
	{
		if (distance_to_obstacle(i) < (obstacles[i]->radius * 1.6) )
		{
			if (collision(i) != 0)
			{	
				obX = getX() - obstacles[i]->x;					//Works out the X position to move away from the obstacles center
				obY = getY() - obstacles[i]->y;					//Works out the Y position to move away from the obstacles center
				obX = (obX / distance_to_obstacle(i)) * _vel;	//Calculate the X movement based on position/distance * velocity
				obY = (obY / distance_to_obstacle(i)) * _vel;	//Calculate the Y movement based on position/distance * velocity
				_newDX += (obX - dirX()) * _obstacleAvoid;				//Make the changes to the newDirection X, (Difference between newDX and DX) * weighting
				_newDY += (obY - dirY()) * _obstacleAvoid;				//Make the changes to the newDirection Y, (Difference between newDY and DY) * weighting
				didWeAvoid = true;
			}
		}
	}
	if (didWeAvoid)
		return true;
	else
		return false;
}

//This function seems redundant, I dont set the behaviour to do this (Might Remove)
void BoidCB::perform_behaviour()
{
	if(behaviour == B_SEPARATION){ separation(); }
	else if(behaviour == B_ALIGNMENT){ alignment(); }
	else if(behaviour == B_COHESION){ cohesion(); }
	else if(behaviour == B_FLOCKING){ flocking(); }
}

void BoidCB::separation()
{
	if (!obstacle_avoidance() && (!obstacle_dis()))
	{
		double sepX = 0, sepY = 0;	//Stores the average X/Y pos's
		double sepCount = 0;		//Stores the number of pos's
		for (int i = 0; i < bd_count; i++)
		{
			if ( (distance_to_boid(i) < (_vis / 2)) && (_boidID != i) )
			{
				sepX += boids[i]->getX();// + boids[i]->dirX();	//Get the average FUTURE positions of the nearby boids, X
				sepY += boids[i]->getY();// + boids[i]->dirY();	//Get the average FUTURE positions of the nearby boids, Y
				sepCount++;
			}
		}
		if (sepCount > 0)	//Make sure there are some boids nearby before proceding
		{
			sepX = getX() - (sepX / sepCount);						//Difference between the two positions pos - (averagePos)
			sepY = getY() - (sepY / sepCount);						//Difference between the two positions pos - (averagePos)
			sepX = (sepX / distance_to_pos(sepX, sepY)) * _vel;		//Calculate new movement based on the position / distance * velocity
			sepY = (sepY / distance_to_pos(sepX, sepY)) * _vel;		//Calculate new movement based on the position / distance * velocity
			_newDX += (sepX - dirX()) * _separation;				//Adjust the new movement, Add the difference between sepDirection and current Direction * separation weighting
			_newDY += (sepY - dirY()) * _separation;				//Adjust the new movement, Add the difference between sepDirection and current Direction * separation weighting
		}
	}
}

void BoidCB::alignment()
{
		double alignX = 0, alignY = 0;	//Stores the average X/Y direction
		double alignCount = 0;			//Stores the number of directions
		for (int i = 0; i < bd_count; i++)
		{
			if ( (distance_to_boid(i) < (_vis * 1.5)) && (_boidID != i) )
			{
				alignX += boids[i]->dirX();		//Add the boids[i] current movement X
				alignY += boids[i]->dirY();		//Add the boids[i] current movement Y
				alignCount++;
			}
		}
		if (alignCount > 0)
		{
			alignX = alignX / alignCount;		//Average out the movement
			alignY = alignY / alignCount;		//Average out the movement
			_newDX += alignX * _alignment;		//Add the averaged out movement * weighting to the new movement direction
			_newDY += alignY * _alignment;		//Add the averaged out movement * weighting to the new movement direction
		}
}

void BoidCB::cohesion()
{
	if (!obstacle_avoidance())
	{
		double cohX = 0, cohY = 0;
		double cohCount = 0;
		for (int i = 0; i < bd_count; i++)
		{
			if ( (distance_to_boid(i) < (_vis * 1.5)) && (_boidID != i) )
			{
				cohX += boids[i]->getX() + boids[i]->dirX();		//Add the boids[i] current X position
				cohY += boids[i]->getY() + boids[i]->dirY();		//Add the boids[i] current Y position
				cohCount++;
			}
		}

		if (cohCount > 0)
		{
			cohX = (cohX / cohCount) - getX();						//Difference in X position between averaged nearby X and current X (avg - curr, means we get the direction to turn towards)
			cohY = (cohY / cohCount) - getY();						//Difference in Y position between averaged nearby Y and current Y (avg - curr, means we get the direction to turn towards)
			cohX = (cohX / distance_to_pos(cohX, cohY)) * _vel;		//Calculate the new X movement (Based on the average pos)
			cohY = (cohY / distance_to_pos(cohX, cohY)) * _vel;		//Calcualte the new Y movement (Based on the average pos)
			_newDX += (cohX - dirX()) * _coheshion;					//Adjust the new X movement with, difference (average future pos - current movement) * weighting
			_newDY += (cohY - dirY()) * _coheshion;					//Adjust the new Y movement with, difference (average future pos - current movement) * weighting
		}
	}
}

/** This function calls the other funcitons to create flocking**/
void BoidCB::flocking()
{
	bool needToAvoid = false;			//Tells us if we need to avoid instead of alignment/cohesion

	int predC = predator_check();		//Do a check for the nearest predator
	if (predC > -1)						//If there is one within vis range flee from it
	{
		if (_vel < 0.0501)			//Accelerate the boid (Within limits)
			accelerate(0.0005);
		double fleeX = predators[predC]->getX() + predators[predC]->dirX();		//Work out the predators future pos X
		double fleeY = predators[predC]->getY() + predators[predC]->dirY();		//Work out the predators future pos Y
		fleeX = getX() - fleeX;													//Calculate the difference (curr - flee) because we want to move away from that position
		fleeY = getY() - fleeY;													//Calculate the difference (curr - flee) because we want to move away from that position
		fleeX = (fleeX / distance_to_pos(fleeX, fleeY)) * _vel;					//Calculate the predators movement in X direction
		fleeY = (fleeY / distance_to_pos(fleeX, fleeY)) * _vel;					//Calcualte the predators movement in Y direction
		_newDX += (fleeX - dirX()) * _flee;										//Adjust our new movement direction, diff (pred future pos - curr X movement) * weighting
		_newDY += (fleeY - dirY()) * _flee;										//Adjust our new movement direction, diff (pred future cos - curr Y movement) * weighting
	}
	else
	{
		if (_vel > 0.02)			//If the boid is going to fast and not fleeing
			accelerate(-0.01);		//Slow it down
		if (_vel < 0.02)			//If its going slower than min speed
			_vel = 0.02;			//Set min speed
	}

	for (int i = 0; i < bd_count; i++)
	{	//Check for any boids that are too close
		if ( (_boidID != i) && (distance_to_boid(i) < (_vis / 2)) )
			needToAvoid = true;			//If there is one too close, tell this one to avoid it
	}

	if (!needToAvoid)
	{	//There are no boids to avoid, so proceed
		if (players.size() > 0)
		{	//We have a player controlled boid on the screen, So head towards its position!
			double playerX = players[0]->getX();							//Get the players current X pos
			double playerY = players[0]->getY();							//Get the players current Y pos
			playerX = playerX - getX();										//Difference in position (player - boid) gives us movement towards its position
			playerY = playerY - getY();										//Difference in position (player - boid) gives us movement towards its position
			playerX = (playerX / distance_to_pos(playerX, playerY)) * _vel;	//Calculate player movement in X direction
			playerY = (playerY / distance_to_pos(playerX, playerY)) * _vel;	//Calcualte player movement in Y direction
			_newDX += (playerX - dirX()) * _coheshion;						//Adjust the new movement direction to take the players pos into account, (player future pos - boid curr pos) * weighting
			_newDY += (playerY - dirY()) * _coheshion;						//Adjust the new movement direction to take the players pos into account, (player future pos - boid curr pos) * weighting

		}
		else
		{	//No player controlled boid, so proceed
			if (IDevState->alignmentMode)	//Check to see if alignment is actually enabled (User Input)
				alignment();
			if (IDevState->cohesionMode)	//Check to see if cohesion is actually enabled (User Input)
				cohesion();
		}
	}
	else
	{	//We need to move away from at least one boid
		if (IDevState->seperationMode)	//Check to see if seperation is actually enabled (User Input)
			separation();
	}
}

int BoidCB::predator_check()
{
	for (int i = 0; i < pd_count; i++)
	{
		if (distance_to_predator(i) < (_vis * 2)) //Predator is within detection range!
			return i;
	}
	return -1;
}

/** Calculates the distance between the boid and predator **/
double BoidCB::distance_to_predator(int pd)
{
	return sqrt(pow(predators[pd]->getX() - getX(),2)+pow(predators[pd]->getY() - getY(),2));
}