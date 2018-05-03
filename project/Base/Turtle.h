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
	public:
		Turtle();
		Turtle(float, float);
		Vector2d getVelocity();
		Vector2d getAcceleration();
		void applyForce(Vector2d);
		void update();
		void borders(float, float);
		virtual void render();
		virtual void run(float, float);
		virtual ~Turtle();
};

#endif /* TURTLE_H_ */
