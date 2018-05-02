#include "UserInput.h"
#include "generalIncludes.h"

UserInput::UserInput()
{
}

void UserInput::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	if (IDevState->addObstacle)
	{	//Add another obstacle
		IDevState->addObstacle = false;
		Obstacle *boo = new Obstacle(0.4,2.0);
		if (boo->exist)
			obstacles.push_back(boo);
	}

	if (IDevState->removeObstacles)
	{
		IDevState->removeObstacles = false;
		if (ob_count > 0)
		{
			ob_count--;
			O->removeChild(obstacles[ob_count]->geode);
			O->dirtyBound();
			obstacles.pop_back();
			cout << "Removed obstacle : " << ob_count << endl;
		}
		else
			cout << ob_count << " obstacles to remove! " << endl;
	}

	if (IDevState->addMoreBoids)
	{	//Add more flocking boids
		IDevState->addMoreBoids = false;
		boids.push_back(new Boid(2*M_PI*rand()/RAND_MAX,0.02,1.0,bd_count));
	}

	if (IDevState->removeBoids)
	{
		IDevState->removeBoids = false;

		if (bd_count > 0)
		{
			bd_count--;
			bds->removeChild(boids[bd_count]->T);
			boids.pop_back();
			cout << "Removed Boid : " << bd_count << endl;
		}
		else
			cout << "Can't removed Last boid!!" << endl;
	}

	if (IDevState->addPredator)
	{
		IDevState->addPredator = false;
		predators.push_back(new Predator(2*M_PI*rand()/RAND_MAX,0.04,2.0,pd_count));
	}

	if (IDevState->removePredator)
	{
		IDevState->removePredator = false;

		if (pd_count > 1)
		{
			pd_count--;

			preds->removeChild(predators[pd_count]->T);
			predators.pop_back();
			cout << "Removed Predator : " << pd_count << endl;
		}
		else if (pd_count == 1)
		{
			pd_count--;
			preds->removeChildren(0,preds->getNumChildren());
			predators.pop_back();
			cout << "Removed Predator : " << pd_count << endl;
		}
		else
			cout << pd_count << " Predators to remove!" << endl;
	}

	if (IDevState->randomRelocate)
	{
		IDevState->randomRelocate = false;
		for (int i = 0; i < bd_count; i++)
		{
			boids[i]->setRandomPos();
		}
		cout << "Random locations set!" << endl;
	}

	if (IDevState->spawnFollowBoid)
	{
		IDevState->spawnFollowBoid = false;
		if (players.size() <= 0)
		{
			players.push_back(new Player(2*M_PI*rand()/RAND_MAX,0,2.0));
			cout << "Spawned player controlled boid." << endl;
		}
		else
		{
			root->removeChild(players[0]->T);
			players.pop_back();
			cout << "Player controlled boid removed." << endl;
		}
	}

	//CURRENTLY DOES NOT FUCNTION CORRECTLY (NEEDS CALLING MULTIPLE TIMES TO WORK)!!
	if (IDevState->cleanObstacles)
	{	//Clean up obstacles outside of the walls
		IDevState->cleanObstacles = false;
		int obstaclesRemoved = 0;
		bool removeMe = false;

		for (int i = 0; i < ob_count; i++)
		{	//Loop through them backwards to allow for easy removal

			removeMe = false;	//Each time set to false

			if (obstacles[i]->x + obstacles[i]->radius > wall3->getCenter().x())
			{	//Its beyond the right wall remove it!
				removeMe = true;
			}
			else if (obstacles[i]->x - obstacles[i]->radius < wall4->getCenter().x())
			{	//Its beyond the left wall remove it!
				removeMe = true;
			}
			else if (obstacles[i]->y + obstacles[i]->radius > wall1->getCenter().y())
			{	//Its beyond the top wall remove it!
				removeMe = true;
			}
			else if (obstacles[i]->y - obstacles[i]->radius < wall2->getCenter().y())
			{	//Its beyond the top wall remove it!
				removeMe = true;
			}

			if (removeMe)
			{	//Remove this obstacle
				obstaclesRemoved++;
				if (i == ob_count - 1)
				{
					ob_count--;
					O->removeChild(obstacles[ob_count]->geode);
					obstacles.pop_back();
					cout << "Removed last obstacle : " << ob_count << endl;
				}
				else
				{
					ob_count--;
					obstacles[i]->radius = obstacles[ob_count]->radius;
					obstacles[i]->x = obstacles[ob_count]->x;
					obstacles[i]->y = obstacles[ob_count]->y;
					obstacles[i]->geode->removeDrawable(obstacles[i]->draw);
					obstacles[i]->shape->set(obstacles[ob_count]->shape->getCenter(),obstacles[ob_count]->shape->getRadius(),obstacles[ob_count]->shape->getHeight());
					obstacles[i]->draw->setShape(obstacles[i]->shape);
					obstacles[i]->geode->addDrawable(obstacles[i]->draw);
					obstacles[i]->draw->dirtyDisplayList();

					O->removeChild(obstacles[ob_count]->geode);
					obstacles.pop_back();
					cout << "Removed obstacle out side of wall : " << ob_count << endl;
				}
			}
		}

		if (obstaclesRemoved > 0)
			cout << "Performed obstacle clean up, : " << ob_count << " :: " << obstaclesRemoved << " obstacles removed." << endl;
		else
			cout << "There are no obstacles to clean up!" << endl;
	}

	if (IDevState->expandWallsRequest)
	{
		//Expand walls!??
		double wTL = wall1->getHalfLengths().x();
		double wBL = wall2->getHalfLengths().x();
		double wLL = wall3->getHalfLengths().y();
		double wRL = wall4->getHalfLengths().y();

		wall1->setHalfLengths(Vec3(wTL + 0.2,0.04,0.5));
		wall2->setHalfLengths(Vec3(wBL + 0.2,0.04,0.5));
		wall3->setHalfLengths(Vec3(0.04,wLL + 0.2,0.5));
		wall4->setHalfLengths(Vec3(0.04,wRL + 0.2,0.5));

		plane->setHalfLengths(Vec3(wall1->getHalfLengths().x(),wall3->getHalfLengths().y(),0.1));

		wall1->setCenter(Vec3(0, wall3->getHalfLengths().y(), 0.5));
		wall2->setCenter(Vec3(0, wall3->getHalfLengths().y() * (-1), 0.5));
		wall3->setCenter(Vec3(wall1->getHalfLengths().x(), 0, 0.5));
		wall4->setCenter(Vec3(wall1->getHalfLengths().x() * (-1), 0, 0.5));


		//Redraw after all the changes!
		wdraw1->dirtyDisplayList();
		wdraw2->dirtyDisplayList();
		wdraw3->dirtyDisplayList();
		wdraw4->dirtyDisplayList();
		pdraw->dirtyDisplayList();
	}

	if ( (IDevState->shrinkWallsRequest) && (wall1->getHalfLengths().x() > 5) ) //Make sure the walls aren't too small already
	{
		double wTL = wall1->getHalfLengths().x();
		double wBL = wall2->getHalfLengths().x();
		double wLL = wall3->getHalfLengths().y();
		double wRL = wall4->getHalfLengths().y();

		wall1->setHalfLengths(Vec3(wTL - 0.2,0.04,0.5));
		wall2->setHalfLengths(Vec3(wBL - 0.2,0.04,0.5));
		wall3->setHalfLengths(Vec3(0.04,wLL - 0.2,0.5));
		wall4->setHalfLengths(Vec3(0.04,wRL - 0.2,0.5));

		plane->setHalfLengths(Vec3(wall1->getHalfLengths().x(),wall3->getHalfLengths().y(),0.1));

		wall1->setCenter(Vec3(0, wall3->getHalfLengths().y(), 0.5));
		wall2->setCenter(Vec3(0, wall3->getHalfLengths().y() * (-1), 0.5));
		wall3->setCenter(Vec3(wall1->getHalfLengths().x(), 0, 0.5));
		wall4->setCenter(Vec3(wall1->getHalfLengths().x() * (-1), 0, 0.5));


		//Redraw after all the changes!
		wdraw1->dirtyDisplayList();
		wdraw2->dirtyDisplayList();
		wdraw3->dirtyDisplayList();
		wdraw4->dirtyDisplayList();
		pdraw->dirtyDisplayList();
	}

	traverse( node, nv);
}