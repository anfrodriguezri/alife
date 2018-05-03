#include "PredatorPrey.h"

template <class T>
PredatorPrey<T>::PredatorPrey() {}

template <class T>
void PredatorPrey<T>::run(float maxWidth, float maxHeight){
	for( int i = 0; i < turtles.size(); i++){
		turtles[i].run(turtles, maxWidth, maxHeight);
	}
}

template <class T>
void PredatorPrey<T>::addBoid(T turtle){
	turtles.push_back(turtle);
};

template <class T>
PredatorPrey<T>::~PredatorPrey() {}

template class PredatorPrey<Boid>;