#ifndef BOID_H
#define BOID_H
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

#include "Obstacle.h"
#include "generalIncludes.h"
class BoidCB;

using namespace osg;
using namespace osgViewer;
using namespace std;

class Boid
{
public:
	Boid(double x, double y, double dir, double vel, double vis, int ID);
	Boid(double dir, double vel, double vis, int ID);
	double getX();
	double getY();
	double getDir();
	double getVel();
	double dirX();
	double dirY();
	double getDX();
	double getDY();
	void setRandomPos();
	osg::MatrixTransform *T;
	osg::Sphere *shape;
	osg::ShapeDrawable *draw;
	Geode *geode;

private:
	BoidCB* bcb;	//the boid's callback function
};

#endif