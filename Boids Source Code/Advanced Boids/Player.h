#ifndef PLAYER_H
#define PLAYER_H
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <iostream>

#include <osgViewer/Viewer>

#include "Obstacle.h"
class PlayerCB;

using namespace osg;
using namespace osgViewer;
using namespace std;

class Player
{
public:
	Player(double x, double y, double dir, double vel, double vis);
	Player(double dir, double vel, double vis);
	double getX();
	double getY();
	double getDir();
	double getVel();
	MatrixTransform *T;
private:
	PlayerCB* bcb;	//the boid's callback function
};

#endif 

