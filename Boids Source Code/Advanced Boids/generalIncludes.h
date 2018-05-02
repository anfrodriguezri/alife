#ifndef GENERALINCLUDES_H
#define GENERALINCLUDES_H

#include "keyboardEventHandler.h"
#include "Boid.h"
#include "Predator.h"
#include "Player.h"

class Boid;
class Predator;

extern osg::Box *wall1, *wall2, *wall3, *wall4, *plane;
extern osgViewer::Viewer *viewer;
extern osg::ShapeDrawable *wdraw1, *wdraw2, *wdraw3, *wdraw4, *pdraw;
//extern Obstacle **obstacles;
extern vector<Obstacle*> obstacles;
extern int ob_count, bd_count, pd_count;
extern osg::Group *root, *bds, *preds;
//extern Boid **boids;
extern vector<Boid*> boids;
extern InputDeviceStateType* IDevState;
extern MatrixTransform *O;
//extern Predator **predators;
extern vector<Predator*> predators;
extern vector<Player*> players;

#endif