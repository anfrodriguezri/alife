#include "PredatorPrey.h"

template <class T, class U>
PredatorPrey<T, U>::PredatorPrey() {}

template <class T, class U>
void PredatorPrey<T, U>::run(float velocityFactor, float maxWidth, float maxHeight){
	for( int i = 0; i < preys.size(); i++){
		preys[i].run(preys, velocityFactor, maxWidth, maxHeight);
	}
	for( int i = 0; i < predators.size(); i++){
		predators[i].run(predators, preys, velocityFactor, maxWidth, maxHeight);
	}
}

template <class T, class U>
void PredatorPrey<T, U>::addPrey(T prey){
	preys.push_back(prey);
};

template <class T, class U>
void PredatorPrey<T, U>::addPredator(U predator){
	predators.push_back(predator);
};

template <class T, class U>
PredatorPrey<T, U>::~PredatorPrey() {}

template class PredatorPrey<Boid, Predator>;