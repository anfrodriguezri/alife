#include "generalIncludes.h"
#include "PredatorCB.h"

#define WALL_BOUNCE 0

#define B_NONE 0
#define B_HUNT 1
#define B_CHASE 2

/** Creates a new boid with default behaviours **/
PredatorCB::PredatorCB(double r, double x, double y, double dir, double vel, double vis, int ID)
{
	_x = x; _y = y; _radius = r;
	_dx = 0; _dy = 0;
	_theta = dir;
	_vel = vel;
	_vis = vis;
	_predID = ID;

	_separation = 0.28;
	_chase = 0.35;

	behaviour = B_HUNT;
	wall_behaviour = WALL_BOUNCE;
}
/** Returns current x coordinate of boid's position **/
double PredatorCB::getX(){ return _x+_dx; }
/** Returns current y coordinate of boid's position **/
double PredatorCB::getY(){ return _y+_dy; }
/** Returns current direction of travel **/
double PredatorCB::getDir(){ return _theta; }
/** Returns current velocity **/
double PredatorCB::getVel(){ return _vel; }

//osg::Geode* PredatorCB::getGeode(){ return Pgeode; }

/** Returns the amount the boid will move each step in the x direction **/
double PredatorCB::dirX(){ return _vel*sin(_theta); }
/** Returns the amount the boid will move ech step in the y direction **/
double PredatorCB::dirY(){ return _vel*cos(_theta); }

/** The callback function.  Code in this function is executed repeatedly **/
void PredatorCB::operator()( osg::Node* node, osg::NodeVisitor* nv )
{	
	//calculate next movement
	double tempN = sqrt(dirX()*dirX()+dirY()*dirY());
	_dirX = (dirX() / tempN) * _vel;
	_dirY = (dirY() / tempN) * _vel;


	perform_behaviour();
	obstacle_avoidance();
	if(wall_behaviour == WALL_BOUNCE){ wall_bounce(); }

	_theta = atan2(_dirX, _dirY);	//Sets the theta based on new cords

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
void PredatorCB::steer(double a){ _theta += a; }
/** If a is positive, boid will accelerate, if a is negative, will decelerate **/
void PredatorCB::accelerate(double a){ _vel += a; }

/** Calculates the distance between the boid and obstacle[ob] **/
double PredatorCB::distance_to_obstacle(int ob)
{
	return sqrt(pow(obstacles[ob]->x-getX(),2)+pow(obstacles[ob]->y-getY(),2));
}

/** Calculates the distance between the predator and predator[pd] **/
double PredatorCB::distance_to_predator(int pd)
{
	return sqrt(pow(predators[pd]->getX() - getX(),2)+pow(predators[pd]->getY() - getY(),2));
}

/** Calculates direction in which boid must turn to avoid colliding with obstacle ob **/
double PredatorCB::collision(int ob)
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

/** Calculates the angle towards the specified predator**/
double PredatorCB::angle_to_predator(int pd)
{
	double angle = atan2((predators[pd]->getX() - getX()),predators[pd]->getY() - getY());// - _theta;
	if(angle > M_PI){ angle -= 2*M_PI; }
	if(angle < -M_PI){ angle += 2*M_PI; }
	return angle;
}

void PredatorCB::wall_bounce()
{
	if ( (getX() < (wall4->getCenter().x()) && _dirX < 0) || (getX() > (wall3->getCenter().x()) && _dirX > 0) )
		_dirX = -_dirX;
	if ( (getY() < (wall2->getCenter().y()) && _dirY < 0) || (getY() > (wall1->getCenter().y()) && _dirY > 0) )
		_dirY = -_dirY;
}

/** Decides whether there is an obstacle to close (True = had to avoid an obstacle)**/
void PredatorCB::obstacle_avoidance()
{
	double obX, obY;
	for (int i = 0; i < ob_count; i++)
	{
		if (distance_to_obstacle(i) < (obstacles[i]->radius * 1.6) )
		{
			obX = ((getX() - obstacles[i]->x) / distance_to_obstacle(i)) * _vel;
			obY = ((getY() - obstacles[i]->y) / distance_to_obstacle(i)) * _vel;

			_dirX += (obX - dirX()) * 0.16;
			_dirY += (obY - dirY()) * 0.16;
		}
	}
}

void PredatorCB::perform_behaviour()
{
	if (behaviour = B_HUNT){ hunt(); }
}

void PredatorCB::separation()
{
	double sepX = 0, sepY = 0;
	double sepCount = 0;
	for (int i = 0; i < pd_count; i++)
	{
		if ( (distance_to_predator(i) < (_vis / 2)) && (_predID != i) )
		{
			sepX += predators[i]->getX() + predators[i]->dirX();
			sepY += predators[i]->getY() + predators[i]->dirY();
			sepCount++;
		}
	}
	if (sepCount > 0)	//Make sure there are some boids nearby before proceding
	{
		sepX = sepX / sepCount;
		sepY = sepY / sepCount;

		sepX = getX() - sepX;
		sepY = getY() - sepY;
		double d = sqrt(sepX*sepX+sepY*sepY);

		sepX = (sepX / d) * _vel;
		sepY = (sepY / d) * _vel;

		_dirX += (sepX - dirX()) * _separation;
		_dirY += (sepY - dirY()) * _separation;

	}
}

void PredatorCB::chase(int bd)
{
	if (_vel < 0.04)
		accelerate(0.0005);

	double chaseX = boids[bd]->getX() + boids[bd]->dirX();
	double chaseY = boids[bd]->getY() + boids[bd]->dirY();

	chaseX = chaseX - getX();
	chaseY = chaseY - getY();

	double d = sqrt(chaseX*chaseX+chaseY*chaseY);

	chaseX = (chaseX / d) * _vel;
	chaseY = (chaseY / d) * _vel;

	_dirX += (chaseX - dirX()) * _chase;
	_dirY += (chaseY - dirY()) * _chase;
}

void PredatorCB::hunt()
{
	if (IDevState->predatorsHunt)
	{
		int closestBoid = -1;
		for (int i = 0; i < bd_count; i++)
		{
			if (closestBoid == -1)
				closestBoid = i;
			else if (distance_to_boid(i) < distance_to_boid(closestBoid))
				closestBoid = i;
		}

		if (closestBoid != -1)
		{
			chase(closestBoid); //Chase the closest boid!
		}
		else
		{ //Not chasing anything
			if (_vel > 0.02)
				accelerate(-0.001);
			if (_vel < 0.02)
				_vel = 0.02;
		}
	}
	else if (_vel > 0.02)
		accelerate(-0.001);
	
	if (_vel < 0.02)
		_vel = 0.02;

	if (IDevState->predatorSep)
		separation(); //Run seperation againts other predators, keep them apart
}

/** Calculates the distance between the predator and boid[bd] **/
double PredatorCB::distance_to_boid(int bd)
{
	return sqrt(pow(boids[bd]->getX() - getX(),2)+pow(boids[bd]->getY() - getY(),2));
}

/** Calculates the angle towards the specified boid**/
double PredatorCB::angle_to_boid(int bd)
{
	double angle = atan2((boids[bd]->getX() - getX()),boids[bd]->getY() - getY()) - _theta;
	if(angle > M_PI){ angle -= 2*M_PI; }
	if(angle < -M_PI){ angle += 2*M_PI; }
	return angle;
}