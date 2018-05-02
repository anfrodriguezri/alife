#ifndef BOID_CB_H
#define BOID_CB_H
#include "Obstacle.h"
#include "generalIncludes.h"

#ifndef M_PI
#define M_PI 3.141592654
#endif

class Boid;

using namespace osg;
using namespace osgViewer;
using namespace std;

class BoidCB : public osg::NodeCallback
{
public:
	BoidCB(double r, double x, double y, double dir, double vel, double vis, int ID);
	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );
	
	double getX();
	double getY();
	double getDir();
	double getVel();
	double dirX();			//calculates movement in the x direction
	double dirY();			//calculates movement in the y direction
	double getDY();
	double getDX();
	void setRandomPos();	//Function sets random positions
	
private:
	double _x,_y;			//initial position of the boid
	double _dx,_dy;			//current offset from the initial position
	double _radius;			//the radius of the boid
	double _theta;			//the current direction the boid is facing
	double _vel;			//the boid's current velocity
	double _vis;			//the radius of the boid's area of visability

	double _newDX, _newDY;	//Stores the new direction that the boids will be heading
	bool setRandom;			//Used to decide if the boids locations should be reset
	
	//Weightings of each action
	double _coheshion;
	double _alignment;
	double _separation;
	double _flee;
	double _obstacleAvoid;

	int _boidID;			//The id for this boid (the number it is in the array)
	
	int behaviour;			//the value of this determines the boid's behaviour
	int wall_behaviour;		//the value of this determines what the boid does when it reaches a wall
	
	void steer(double a);
	void accelerate(double a);
	
	void perform_behaviour();
	void separation();
	void alignment();
	void cohesion();
	void flocking();
	
	void wall_bounce();
	
	bool obstacle_avoidance();
	bool obstacle_dis();
	double distance_to_obstacle(int ob);
	double distance_to_boid(int bd);
	double collision(int ob);
	double distance_to_pos(double x, double y);
	double angle_to_pos(double x, double y);
	int predator_check();
	double distance_to_predator(int pd);
};

#endif