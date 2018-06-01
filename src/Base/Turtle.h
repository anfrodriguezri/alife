#ifndef TURTLE_H_
#define TURTLE_H_

#include <tuple>

#include "Figure.h"

using namespace std;

class Turtle : public Figure {
	protected:
		
		Vector2d velocity;
		Vector2d acceleration;
		float maxForce; // max steering force to change velocity direction
		float maxSpeed;
		float sideLength;
		float vision;
		int life;

	public:
		static float desiredSeparation;
		
		Turtle();
		Turtle(float, float);
		Vector2d getVelocity();
		Vector2d getAcceleration();
		int getLife();
		void applyForce(Vector2d);
		void update(float velocityFactor, bool starvationDeath);
		void borders(float, float);
		virtual void render(float r, float g, float b, bool starvationDeath);
		virtual bool isAlive(bool starvationDeath);
		virtual bool run(float velocityFactor, float maxWidth, float maxHeight, bool starvationDeath);
		virtual ~Turtle();
};

#endif /* TURTLE_H_ */
