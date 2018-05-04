#ifndef BOID_H_
#define BOID_H_

#include <vector>

#include "../Base/Vector2d.h"
#include "../Base/Turtle.h"
#include "../PredatorPrey/Predator.h"
#include "../Sugarscape/Sugarscape.h"
#include "../Sugarscape/Sandpile.h"

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
        void eat(Vector2d foodPosition, Sandpile sandpile);
        Vector2d searchFood(Sugarscape);
        void flock(vector<Boid>& boids, vector<Predator>& predators, Sugarscape sugarscape);
        bool run(vector<Boid>& boids, vector<Predator>& predators, Sugarscape sugarscape,
                                float velocityFactor, float maxWidth, float maxHeight, bool death);
};
#endif /* BOID_H_ */

