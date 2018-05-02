#ifndef FLOCK_H_
#define FLOCK_H_

#include <vector>
#include "Turtle.h"

using namespace std;

class Flock {
	protected:
        vector<Turtle> boids;

    public:
        Flock();
        virtual ~Flock();
        void run(float, float);
        void addBoid(Turtle);
};
#endif /* FLOCK_H_ */

