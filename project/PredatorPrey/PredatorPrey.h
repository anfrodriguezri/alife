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
        bool starvationDeath;
        bool reproducing;
    public:
        PredatorPrey();
        vector<T> getPreys();
        vector<U> getPredators();
        bool getPreysPresent();
        bool getPredatorsPresent();
        void togglePreys();
        void togglePredators();
        void toggleDeathFromStarvation();
        void toggleReproducing();
        int runPreys(Sugarscape sugarscape, float velocityFactor, float maxWidth, float maxHeight);
        void runPredators(float velocityFactor, float maxWidth, float maxHeight);
        int run(Sugarscape sugarscape, float velocityFactor, float maxWidth, float maxHeight);
        void addPrey(T);
        void addPredator(U);
        void renderPreys();
        void renderPredators();
        void render();
        virtual ~PredatorPrey();
};
#endif /* PREDATOR_PREY_H_ */

