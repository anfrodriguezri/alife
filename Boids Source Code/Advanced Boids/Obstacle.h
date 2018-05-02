#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

#include <osgViewer/Viewer>

using namespace osg;
using namespace osgViewer;

class Obstacle
{
	
	public:
		double x,y;			//the obstacle's position
		double radius;		//the obstacle's radius
		//osg::MatrixTransform *T;	//Public accesible so we can remove them
		osg::ShapeDrawable *draw;	//Public accesible so we can remove/update them
		osg::Cylinder *shape;
		osg::Geode *geode;
		bool exist;

		Obstacle(double x, double y, double radius);
		Obstacle(double r_min, double r_max);
};

#endif 

