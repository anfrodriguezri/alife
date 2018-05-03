#ifndef PREDATORPREY_H_
#define PREDATORPREY_H_

#include <vector>
#include "../Flocking/Boid.h"
#include "../PredatorPrey/Predator.h"

using namespace std;

template <class T, class U>
class PredatorPrey {
	protected:
        vector<T> preys;
        vector<U> predators;

    public:
        PredatorPrey();
        virtual ~PredatorPrey();
        void run(float, float, float);
        void addPrey(T);
        void addPredator(U);
};
#endif /* PREDATORPREY_H_ */

