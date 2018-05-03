#ifndef PREDATORPREY_H_
#define PREDATORPREY_H_

#include <vector>
#include "../Flocking/Boid.h"

using namespace std;

template <class T>
class PredatorPrey {
	protected:
        vector<T> turtles;

    public:
        PredatorPrey();
        virtual ~PredatorPrey();
        void run(float, float);
        void addBoid(T);
};
#endif /* PREDATORPREY_H_ */

