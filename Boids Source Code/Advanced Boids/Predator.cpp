#include "generalIncludes.h"
#include "Predator.h"
#include "PredatorCB.h"

/** Creates a Boid at the specified position (x,y) **/
Predator::Predator(double x, double y, double dir, double vel, double vis, int ID)
{
	// geometry
	double radius = 0.2;
	Sphere *shape=new Sphere(Vec3(x,y,0.5),radius);
	
	ShapeDrawable *draw=new ShapeDrawable(shape);
	draw->setColor(Vec4(1,0,0,1));
	Geode *geode = new Geode();
	geode->addDrawable(draw);
	
	// transformation
	T=new MatrixTransform();
	
	pcb = new PredatorCB(radius,x,y,dir,vel,vis,ID);
	T->setUpdateCallback(pcb);
	
	T->addChild(geode);
	
	preds->addChild(T);

	pd_count++;
}

/** Creates a Boid at position at which it does not intersect any of the obstacles **/
Predator::Predator(double dir, double vel, double vis, int ID)
{
	double x,y;
	double radius = 0.2;
	
	//position
	int position_found = 0;
	while(!position_found)
	{
		x = 19.0*rand()/RAND_MAX-9.5;
		y = 19.0*rand()/RAND_MAX-9.5;
		
		position_found = 1;
		for(int i = 0; i < ob_count; i++)
		{
			if(sqrt(pow(obstacles[i]->x-x,2)+pow(obstacles[i]->y-y,2)) < obstacles[i]->radius+radius+0.1)
			{
				position_found = 0;
			}
		}
	}
	
	// geometry
	Sphere *shape=new Sphere(Vec3(x,y,0.5),radius);
	
	ShapeDrawable *draw=new ShapeDrawable(shape);
	draw->setColor(Vec4(1,0,0,1));
	Geode *geode = new Geode();
	geode->addDrawable(draw);
	
	// transformation
	T=new MatrixTransform();
	
	pcb = new PredatorCB(radius,x,y,dir,vel,vis,ID);
	T->setUpdateCallback(pcb);
	
	T->addChild(geode);
	
	preds->addChild(T);

	pd_count++;
	cout << "Added predator : " << pd_count << endl;
}

/** Returns current x coordinate of boid's position **/
double Predator::getX(){ return pcb->getX(); }

/** Returns current y coordinate of boid's position **/
double Predator::getY(){ return pcb->getY(); }

/** Returns current direction of travel **/
double Predator::getDir(){ return pcb->getDir(); }

/** Returns current velocity **/
double Predator::getVel(){ return pcb->getVel();; }

double Predator::dirX(){ return pcb->dirX();; }

double Predator::dirY(){ return pcb->dirY();; }