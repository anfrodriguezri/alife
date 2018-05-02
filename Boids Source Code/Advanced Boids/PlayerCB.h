#ifndef PLAYER_CB_H
#define PLAYER_CB_H
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <iostream>

#include <osgViewer/Viewer>

#include "Obstacle.h"

#ifndef M_PI
#define M_PI 3.141592654
#endif

class Player;

using namespace osg;
using namespace osgViewer;
using namespace std;

class PlayerCB : public osg::NodeCallback
{
public:
	PlayerCB(double r, double x, double y, double dir, double vel, double vis);
	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );
	
	double getX();
	double getY();
	double getDir();
	double getVel();
	double dirX();			//calculates movement in the x direction
	double dirY();			//calculates movement in the y direction
	
private:
	double _x,_y;			//initial position of the boid
	double _dx,_dy;			//current offset from the initial position
	double _radius;			//the radius of the boid
	double _theta;			//the current direction the boid is facing
	double _vel;			//the boid's current velocity
	double _vis;			//the radius of the boid's area of visability
	
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
	
	void obstacle_avoidance();
	double distance_to_obstacle(int ob);
	double collision(int ob);
};

#endif 

