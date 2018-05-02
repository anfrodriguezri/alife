#include "BoidCB.h"
#include "Boid.h"
#include "generalIncludes.h"
#include <iostream>

/** Creates a Boid at the specified position (x,y) **/
Boid::Boid(double x, double y, double dir, double vel, double vis, int ID)
{
	// geometry
	double radius = 0.2;
	//Cylinder *shape=new Cylinder(Vec3(x,y,0.5),radius,0.1);
	shape=new Sphere(Vec3(x,y,0.5),radius);

	draw=new ShapeDrawable(shape);
	draw->setColor(Vec4(0,0,1,1));
	geode=new Geode();
	geode->addDrawable(draw);

	// transformation
	T=new MatrixTransform();

	bcb = new BoidCB(radius,x,y,dir,vel,vis,ID);
	T->setUpdateCallback(bcb);

	T->addChild(geode);

	bds->addChild(T);
}

/** Creates a Boid at position at which it does not intersect any of the obstacles **/
Boid::Boid(double dir, double vel, double vis, int ID)
{
	double x,y;
	double radius = 0.2;
	int tries = 0;

	//position
	int position_found = 0;
	while( (!position_found) && (tries < 120) )
	{
		tries++;
		/*x = 19.0*rand()/RAND_MAX-9.5;
		y = 19.0*rand()/RAND_MAX-9.5;*/
		x = ((wall1->getCenter().y() * 2) - 1) * rand() / RAND_MAX - (((wall1->getCenter().y() * 2) - 1) / 2);
		y = ((wall3->getCenter().x() * 2) - 1) * rand() / RAND_MAX - (((wall3->getCenter().x() * 2) - 1) / 2);

		position_found = 1;
		for(int i = 0; i < ob_count; i++)
		{
			if(sqrt(pow(obstacles[i]->x-x,2)+pow(obstacles[i]->y-y,2)) < obstacles[i]->radius+radius+0.1)
			{
				position_found = 0;
			}
		}
	}

	if (tries < 120)
	{
		// geometry
		shape=new Sphere(Vec3(x,y,0.5),radius);

		draw=new ShapeDrawable(shape);
		draw->setColor(Vec4(0,0,1,1));
		geode=new Geode();
		geode->addDrawable(draw);

		// transformation
		T=new MatrixTransform();

		bcb = new BoidCB(radius,x,y,dir,vel,vis,ID);
		T->setUpdateCallback(bcb);
		T->setDataVariance(Object::DYNAMIC);

		T->addChild(geode);

		bds->addChild(T);

		bd_count++;
		cout << "Added boid, ID : " << bd_count << endl;
	}
	else
		std::cout << "Couldn't find a safe location to spawn boid :: " << bd_count << endl;
}

/** Returns current x coordinate of boid's position **/
double Boid::getX(){ return bcb->getX(); }

/** Returns current y coordinate of boid's position **/
double Boid::getY(){ return bcb->getY(); }

/** Returns current direction of travel **/
double Boid::getDir(){ return bcb->getDir(); }

/** Returns current velocity **/
double Boid::getVel(){ return bcb->getVel();; }

double Boid::dirX(){ return bcb->dirX();; }

double Boid::dirY(){ return bcb->dirY();; }

double Boid::getDX(){ return bcb->getDX();; }

double Boid::getDY(){ return bcb->getDY();; }

void Boid::setRandomPos(){ return bcb->setRandomPos();; }