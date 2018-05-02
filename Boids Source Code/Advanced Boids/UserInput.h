#ifndef USERINPUT_H
#define USERINPUT_H

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

#include "generalIncludes.h"

#ifndef M_PI
#define M_PI 3.141592654
#endif

class UserInput : public osg::NodeCallback
{
public:
	UserInput();
	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );
};
#endif