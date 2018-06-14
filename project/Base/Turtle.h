#ifndef TURTLE_H_
#define TURTLE_H_

#include <tuple>
#include <vector>
#include <string>
#include <GL/freeglut.h>
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
		GLuint texture;
		float r;
		float g;
		float b;

	public:

		Turtle();
		Turtle(float x, float y, float r, float g, float b, GLuint texture);
		Vector2d getVelocity();
		Vector2d getAcceleration();
		int getLife();
		float getVision();
		float getMaxSpeed();
		float getR();
		float getG();
		float getB();
		void setTexture(int texture);
		void applyForce(Vector2d);
		void update(float velocityFactor, bool starvationDeath);
		void borders(float, float);
		virtual void render(bool starvationDeath);
		virtual bool isAlive(bool starvationDeath);
		virtual bool run(float velocityFactor, float maxWidth, float maxHeight, bool starvationDeath);
		virtual ~Turtle();
};

#endif /* TURTLE_H_ */
