#include "Boid.h"
#include "BoidCB.h"
#include "Obstacle.h"
#include "generalIncludes.h"
#include "Predator.h"
#include "PredatorCB.h"
#include "UserInput.h"
#include "Player.h"
#include "PlayerCB.h"

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

#include <osgViewer/Viewer>
#include <vector>

using namespace osg;
using namespace osgViewer;

//----These variables are accesible throughout program-----//
Box *wall1, *wall2, *wall3, *wall4, *plane;
Viewer *viewer;
ShapeDrawable *wdraw1, *wdraw2, *wdraw3, *wdraw4, *pdraw;
//Obstacle **obstacles;
vector<Obstacle*> obstacles;
int ob_count, bd_count, pd_count, trav_pd_count;
osg::Group *root, *bds, *preds;
//Boid **boids;
vector<Boid*> boids;
//Predator **predators;
vector<Predator*> predators;
vector<Player*> players;
InputDeviceStateType* IDevState;
MatrixTransform *O;	//obstacle group //Boids group
//----END----//

int main()
{
	//osg::setNotifyLevel(DEBUG_FP);
	srand ( time(NULL) );
	viewer = new Viewer();
	root = new Group();
	bds = new Group();
	preds = new Group();

	IDevState = new InputDeviceStateType;
	myKeyboardEventHandler* myEventHandler = new myKeyboardEventHandler(IDevState);
	viewer->addEventHandler(myEventHandler);
	
	
	//Create the plane and walls
	Geode *gplane=new Geode();
	
	plane=new Box(Vec3(0,0,0),20.2,20.2,0.01);	//The FLOOR"!!! :p
	pdraw=new ShapeDrawable(plane);
	pdraw->setColor(Vec4(0,1,0,1));
	gplane->addDrawable(pdraw);
	
	wall1=new Box(Vec3(0,10.1,0.5),20.2,0.04,1.0);	//Top wall
	wdraw1=new ShapeDrawable(wall1);
	wdraw1->setColor(Vec4f(0.3,0.15,0,1));
	gplane->addDrawable(wdraw1);
	
	wall2=new Box(Vec3(0,-10.1,0.5),20.2,0.04,1.0);	//Bottom wall
	wdraw2=new ShapeDrawable(wall2);
	wdraw2->setColor(Vec4f(0.3,0.15,0,1));
	gplane->addDrawable(wdraw2);
	
	wall3=new Box(Vec3(10.1,0,0.5),0.04,20.2,1.0); //Right wall
	wdraw3=new ShapeDrawable(wall3);
	wdraw3->setColor(Vec4f(0.3,0.15,0,1));
	gplane->addDrawable(wdraw3);
	
	wall4=new Box(Vec3(-10.1,0,0.5),0.04,20.2,1.0);	//Left wall
	wdraw4=new ShapeDrawable(wall4);
	wdraw4->setColor(Vec4f(0.3,0.15,0,1));
	gplane->addDrawable(wdraw4);


	//Tells osg that we are going to be updating these on the fly (This prevents osg from bugging out)
	pdraw->setDataVariance(Object::DYNAMIC);
	wdraw1->setDataVariance(Object::DYNAMIC);
	wdraw2->setDataVariance(Object::DYNAMIC);
	wdraw3->setDataVariance(Object::DYNAMIC);
	wdraw4->setDataVariance(Object::DYNAMIC);
	//------

	O = new MatrixTransform();
	root->addChild(O);

	root->addChild(bds);
	root->addChild(preds);
	
	root->addChild(gplane);

	MatrixTransform *K = new MatrixTransform();
	UserInput *I = new UserInput;
	K->setUpdateCallback(I);
	root->addChild(K);

	//Create objects
	ob_count = 0;
	int spawn_ob_count = 18;
	//obstacles = new Obstacle*[spawn_ob_count];
	srand ( time(NULL) );
	for(int i = 0; i < spawn_ob_count; i++)
	{
		//obstacles[i] = new Obstacle(0.4,2.0);
		obstacles.push_back(new Obstacle(0.4,2.0));
	}
	
	//Create boids
	bd_count = 0;
	int spawn_bd_count = 45;
	//boids = new Boid*[spawn_bd_count];

	//Initalise Boids
	for (int i = 0; i < spawn_bd_count; i++)
	{
		boids.push_back(new Boid(2*M_PI*rand()/RAND_MAX,0.02,1.0,i));
		//boids[i] = new Boid(2*M_PI*rand()/RAND_MAX,0.02,1.0,i);
	}

	//Initliase Predators
	pd_count = 0;
	int spawn_pd_count = 0;
	//predators = new Predator*[spawn_pd_count];
	for (int i = 0; i < spawn_pd_count; i ++)
	{
		predators.push_back(new Predator(2*M_PI*rand()/RAND_MAX,0.02,1.0,i));
		//predators[i] = new Predator(2*M_PI*rand()/RAND_MAX,0.02,1.0,i);
	}

	//Display everything
	viewer->setSceneData(root);
	viewer->setUpViewInWindow(100,100,512,512);
	
	viewer->run();
	
	return 0;
}