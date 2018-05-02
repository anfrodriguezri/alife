#include "PlayerCB.h"
#include "Player.h"
#include "generalIncludes.h"

/** Creates a Boid at the specified position (x,y) **/
Player::Player(double x, double y, double dir, double vel, double vis)
{
	// geometry
	double radius = 0.2;
	//Cylinder *shape=new Cylinder(Vec3(x,y,0.5),radius,0.1);
	Sphere *shape=new Sphere(Vec3(x,y,0.5),radius);
	
	ShapeDrawable *draw=new ShapeDrawable(shape);
	draw->setColor(Vec4(0.5,0.1,0.9,1));
	Geode *geode=new Geode();
	geode->addDrawable(draw);
	
	// transformation
	T=new MatrixTransform();
	
	bcb = new PlayerCB(radius,x,y,dir,vel,vis);
	T->setUpdateCallback(bcb);
	
	T->addChild(geode);
	
	root->addChild(T);
}

/** Creates a Boid at position at which it does not intersect any of the obstacles **/
Player::Player(double dir, double vel, double vis)
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
	draw->setColor(Vec4(0.5,0.1,0.9,1));
	Geode *geode=new Geode();
	geode->addDrawable(draw);
	
	// transformation
	T=new MatrixTransform();
	
	bcb = new PlayerCB(radius,x,y,dir,vel,vis);
	T->setUpdateCallback(bcb);
	
	T->addChild(geode);
	
	root->addChild(T);
}

/** Returns current x coordinate of boid's position **/
double Player::getX(){ return bcb->getX(); }

/** Returns current y coordinate of boid's position **/
double Player::getY(){ return bcb->getY(); }

/** Returns current direction of travel **/
double Player::getDir(){ return bcb->getDir(); }

/** Returns current velocity **/
double Player::getVel(){ return bcb->getVel();; }




