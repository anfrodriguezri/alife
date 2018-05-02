#ifndef PREDATOR_H
#define PREDATOR_H
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <iostream>

#include <osgViewer/Viewer>

#include "generalIncludes.h"
class Boid;
class PredatorCB;

using namespace osg;
using namespace osgViewer;
using namespace std;

class Predator
{
public:
	Predator(double x, double y, double dir, double vel, double vis, int ID);
	Predator(double dir, double vel, double vis, int ID);
	double getX();
	double getY();
	double getDir();
	double getVel();
	double getRadius();
	double dirX();
	double dirY();
	osg::MatrixTransform *T;

private:
	PredatorCB* pcb;	//the boid's callback function
};

#endif