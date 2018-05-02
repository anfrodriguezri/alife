#include "PlayerCB.h"
#include "Player.h"

#include "generalIncludes.h"

#define WALL_BOUNCE 0

#define B_NONE 0
#define B_SEPARATION 1
#define B_ALIGNMENT 2
#define B_COHESION 3
#define B_FLOCKING 4

/** Creates a new boid with default behaviours **/
PlayerCB::PlayerCB(double r, double x, double y, double dir, double vel, double vis)
{
	_x = x; _y = y; _radius = r;
	_dx = 0; _dy = 0;
	_theta = dir;
	_vel = vel;
	_vis = vis;
	
	behaviour = B_FLOCKING;
	wall_behaviour = WALL_BOUNCE;
}
/** Returns current x coordinate of boid's position **/
double PlayerCB::getX(){ return _x+_dx; }
/** Returns current y coordinate of boid's position **/
double PlayerCB::getY(){ return _y+_dy; }
/** Returns current direction of travel **/
double PlayerCB::getDir(){ return _theta; }
/** Returns current velocity **/
double PlayerCB::getVel(){ return _vel; }

/** Returns the amount the boid will move each step in the x direction **/
double PlayerCB::dirX(){ return _vel*sin(_theta); }
/** Returns the amount the boid will move ech step in the y direction **/
double PlayerCB::dirY(){ return _vel*cos(_theta); }

/** The callback function.  Code in this function is executed repeatedly **/
void PlayerCB::operator()( osg::Node* node, osg::NodeVisitor* nv )
{	
	//calculate next movement
	perform_behaviour();
	obstacle_avoidance();
	if(wall_behaviour == WALL_BOUNCE){ wall_bounce(); }
	if(_theta < M_PI){ _theta += 2*M_PI; }
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
void PlayerCB::steer(double a){ _theta += a; }
/** If a is positive, boid will accelerate, if a is negative, will decelerate **/
void PlayerCB::accelerate(double a){ _vel += a; }

/** Calculates the distance between the boid and obstacle[ob] **/
double PlayerCB::distance_to_obstacle(int ob)
{
	return sqrt(pow(obstacles[ob]->x-getX(),2)+pow(obstacles[ob]->y-getY(),2));
}

/** Calculates direction in which boid must turn to avoid colliding with obstacle ob **/
double PlayerCB::collision(int ob)
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
void PlayerCB::wall_bounce()
{
	if ( (getX() < (wall4->getCenter().x()) && dirX() < 0) || (getX() > (wall3->getCenter().x()) && dirX() > 0) )
		_theta = -_theta;
	if ( (getY() < (wall2->getCenter().y()) && dirY() < 0) || (getY() > (wall1->getCenter().y()) && dirY() > 0) )
		_theta = -_theta+M_PI;
}

void PlayerCB::obstacle_avoidance()
{
	// write your code here.


}

void PlayerCB::perform_behaviour()
{
	if(behaviour == B_SEPARATION){ separation(); }
	else if(behaviour == B_ALIGNMENT){ alignment(); }
	else if(behaviour == B_COHESION){ cohesion(); }
	else if(behaviour == B_FLOCKING){ flocking(); }
}
void PlayerCB::separation()
{
	
}
void PlayerCB::alignment()
{
	
}
void PlayerCB::cohesion()
{
	
}
void PlayerCB::flocking()
{
	if (IDevState->acceleratePlayer)
		accelerate(0.001);
	if (IDevState->decceleratePlayer)
		if (_vel > 0)
			accelerate(-0.001);
		else _vel = 0;
	if (IDevState->playerTurnLeft)
		steer(-0.01);
	if (IDevState->playerTurnRight)
		steer(0.01);
}

