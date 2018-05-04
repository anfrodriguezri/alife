#ifndef PREDATOR_H_
#define PREDATOR_H_

#include <vector>
#include "../Base/Turtle.h"
#include "../Flocking/Boid.h"

using namespace std;

class Boid;

class Predator: public Turtle {
	using Turtle::Turtle;
	protected:

    public:
        Predator();
        Predator(float, float);
        virtual ~Predator();
        Vector2d separate(vector<Predator>);
        Vector2d seek(Vector2d);
        Vector2d hunt(vector<Boid>&);
        void eat(vector<Boid>&, int);
        void move(vector<Predator>&, vector<Boid>&);
        void run(vector<Predator>&, vector<Boid>&, float, float, float);
};
#endif /* PREDATORPREY_H_ */

