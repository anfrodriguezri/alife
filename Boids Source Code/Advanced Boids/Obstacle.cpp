#include "Obstacle.h"
#include "generalIncludes.h"
#include <iostream>

/** Create an obstacle of radius r at position (x_pos,y_pos) **/
Obstacle::Obstacle(double x_pos, double y_pos, double r) 
{
	x = x_pos;
	y = y_pos;
	radius = r;
	shape=new Cylinder(Vec3(x,y,0.5),radius,0.8+0.4*rand()/RAND_MAX);
	draw=new ShapeDrawable(shape);
	geode=new Geode();
	geode->addDrawable(draw);

	//T = new MatrixTransform();
	O->addChild(geode);
	exist = true;

	//root->addChild(O);
}

/** Create a random obstacle (minimum radius r_min, maximum radius r_max) that does not overlap any other obstacles **/
Obstacle::Obstacle(double r_min, double r_max) 
{
	int position_found = 0;
	int can_find_pos = 0;
	exist = false;

	while( (!position_found) && (can_find_pos < 120) && (ob_count < 230))
	{
		can_find_pos++;

		x = (((wall1->getCenter().y() - 2) * 2) - r_max) * rand() / RAND_MAX - ((((wall1->getCenter().y() - 2) * 2) - r_max) / 2);
		y = (((wall3->getCenter().x() - 2) * 2) - r_max) * rand() / RAND_MAX - ((((wall3->getCenter().x() - 2) * 2) - r_max) / 2);
		//x = 15.0*rand()/RAND_MAX-7.5;
		//y = 15.0*rand()/RAND_MAX-7.5;
		radius = r_min+(r_max-r_min)*rand()/RAND_MAX;

		position_found = 1;
		for(int i = 0; i < ob_count; i++)
		{
			if(sqrt(pow(obstacles[i]->x-x,2)+pow(obstacles[i]->y-y,2)) < obstacles[i]->radius+radius+0.4)
			{
				position_found = 0;
			}
		}
	}

	if ( (can_find_pos < 120) && (ob_count < 230) )
	{
		ob_count++;
		std::cout << "Adding new obstacle : " << ob_count << std::endl;
		shape=new Cylinder(Vec3(x,y,0.5),radius,0.8+0.4*rand()/RAND_MAX);
		draw=new ShapeDrawable(shape);
		geode=new Geode();
		geode->addDrawable(draw);

		//T = new MatrixTransform();
		O->addChild(geode);
		exist = true;

		//root->addChild(T);
	}
	else
	{
		if (ob_count < 230)
		{
			//ob_count--;
			std::cout << "Couldn't add obstacle" << ob_count << std::endl;
		}
		else
		{
			//ob_count--;
			std::cout << "Too many obstacles - beyond hard limit of : " << 230 << std::endl;
		}
	}
}
