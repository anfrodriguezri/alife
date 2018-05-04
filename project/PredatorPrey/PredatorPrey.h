#ifndef PREDATOR_PREY_H_
#define PREDATOR_PREY_H_

#include <vector>
#include "../Flocking/Boid.h"
#include "../PredatorPrey/Predator.h"

using namespace std;

template <class T, class U>
class PredatorPrey {
	protected:
        vector<T> preys;
        vector<U> predators;
        bool preysPresent;
        bool predatorsPresent;
    public:
        PredatorPrey();
        virtual ~PredatorPrey();
        void togglePreys();
        void togglePredators();
        void runPreys(float velocityFactor, float maxWidth, float maxHeight);
        void runPredators(float velocityFactor, float maxWidth, float maxHeight);
        void run(float velocityFactor, float maxWidth, float maxHeight);
        void addPrey(T);
        void addPredator(U);
        void renderPreys();
        void renderPredators();
        void render();
};
#endif /* PREDATOR_PREY_H_ */

