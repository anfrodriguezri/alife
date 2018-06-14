#include "PredatorPrey.h"
#include <iostream>

template <class T, class U>
PredatorPrey<T, U>::PredatorPrey() {
	preysPresent = false;
	predatorsPresent = false;

	starvationDeath = false;
}
template <class T, class U>
vector<T> PredatorPrey<T, U>::getPreys(){
	return preys;
}
template <class T, class U>
vector<U> PredatorPrey<T, U>::getPredators(){
	return predators;
}
template <class T, class U>
bool PredatorPrey<T, U>::getPreysPresent(){
	return preysPresent;
}
template <class T, class U>
bool PredatorPrey<T, U>::getPredatorsPresent(){
	return predatorsPresent;
}
template <class T, class U>
void PredatorPrey<T, U>::togglePreys(){
	preysPresent = !preysPresent;
};
template <class T, class U>
void PredatorPrey<T, U>::togglePredators(){
	predatorsPresent = !predatorsPresent;
};
template <class T, class U>
void PredatorPrey<T, U>::toggleDeathFromStarvation(){
	starvationDeath = !starvationDeath;
};
template <class T, class U>
void PredatorPrey<T, U>::toggleReproducing(){
	reproducing = !reproducing;
}
template <class T, class U>
int PredatorPrey<T, U>::runPreys(Sugarscape sugarscape, float velocityFactor, float maxWidth, float maxHeight){
	if( !preysPresent ) return -1;

	vector<Predator> empty;
	vector<Predator>* withPredators = &empty;

	if( predatorsPresent )
		withPredators = &predators;

	int numOfReproductions = 0;
	for( int i = 0; i < preys.size(); i++){
		bool reproduced = false;
		bool isAlive = preys[i].run(preys, *withPredators, sugarscape, velocityFactor, maxWidth, maxHeight, starvationDeath, reproducing, reproduced);

		if( reproduced ){
			numOfReproductions++;
		}
		if(!isAlive){
			preys.erase(preys.begin()+i);
		}
	}
	return numOfReproductions;
}
template <class T, class U>
void PredatorPrey<T, U>::runPredators(float velocityFactor, float maxWidth, float maxHeight){
	if( !predatorsPresent ) return;

	vector<Boid> empty;
	vector<Boid>* withPreys = &empty;
	
	if( preysPresent )
		withPreys = &preys;

	for( int i = 0; i < predators.size(); i++){
		bool isAlive = predators[i].run(predators, *withPreys, velocityFactor, maxWidth, maxHeight, starvationDeath);

		if(!isAlive){
			predators.erase(predators.begin()+i);
		}
	}
}

template <class T, class U>
int PredatorPrey<T, U>::run(Sugarscape sugarscape, float velocityFactor, float maxWidth, float maxHeight){
	runPredators(velocityFactor, maxWidth, maxHeight);
	return runPreys(sugarscape, velocityFactor, maxWidth, maxHeight);
}
template <class T, class U>
void PredatorPrey<T, U>::addPrey(T prey){
	preys.push_back(prey);
}
template <class T, class U>
void PredatorPrey<T, U>::addPredator(U predator){
	predators.push_back(predator);
}
template <class T, class U>
void PredatorPrey<T, U>::renderPreys(){
	if( !preysPresent ) return;

	for( int i = 0; i < preys.size(); i++){
		preys[i].render(starvationDeath);
	}
}
template <class T, class U>
void PredatorPrey<T, U>::renderPredators(){
	if( !predatorsPresent ) return;

	for( int i = 0; i < predators.size(); i++){
		predators[i].render(starvationDeath);
	}
}
template <class T, class U>
void PredatorPrey<T, U>::render(){
	renderPreys();
	renderPredators();
}

template <class T, class U>
PredatorPrey<T, U>::~PredatorPrey() {}

template class PredatorPrey<Boid, Predator>;