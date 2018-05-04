#ifndef BOID_H_
#define BOID_H_

#include <vector>

#include "../Base/Vector2d.h"
#include "../Base/Turtle.h"
#include "../PredatorPrey/Predator.h"

using namespace std;

class Predator;

class Boid: public Turtle {
    using Turtle::Turtle;
	protected:

    public:
        Boid();
        Boid(float, float);
        virtual ~Boid();
        Vector2d separate(vector<Boid>);
        Vector2d align(vector<Boid>);
        Vector2d seek(Vector2d);
        Vector2d cohere(vector<Boid>);
        Vector2d escape(vector<Predator>);
        void flock(vector<Boid>&, vector<Predator>&);
        void run(vector<Boid>&, vector<Predator>&, float, float, float);
};
#endif /* BOID_H_ */

