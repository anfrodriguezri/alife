#ifndef BOID_H_
#define BOID_H_

#include <vector>

#include "../Base/Vector2d.h"
#include "../Base/Turtle.h"

using namespace std;

class Boid: public Turtle {
    using Turtle::Turtle;
	protected:
        float neighborDist = 50;

    public:
        Boid();
        virtual ~Boid();
        Vector2d separate(vector<Boid>);
        Vector2d align(vector<Boid>);
        Vector2d seek(Vector2d);
        Vector2d cohere(vector<Boid>);
        void flock(vector<Boid>);
        void run(vector<Boid>, float, float, float);
};
#endif /* BOID_H_ */

