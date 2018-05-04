#include "PredatorPrey.h"

template <class T, class U>
PredatorPrey<T, U>::PredatorPrey() {
	preysPresent = false;
	predatorsPresent = false;
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
void PredatorPrey<T, U>::runPreys(float velocityFactor, float maxWidth, float maxHeight){
	if( !preysPresent ) return;

	vector<Predator> empty;
	vector<Predator>* withPredators = &empty;

	if( predatorsPresent )
		withPredators = &predators;

	for( int i = 0; i < preys.size(); i++){
		preys[i].run(preys, *withPredators, velocityFactor, maxWidth, maxHeight);
	}
}
template <class T, class U>
void PredatorPrey<T, U>::runPredators(float velocityFactor, float maxWidth, float maxHeight){
	if( !predatorsPresent ) return;

	vector<Boid> empty;
	vector<Boid>* withPreys = &empty;
	
	if( preysPresent )
		withPreys = &preys;

	for( int i = 0; i < predators.size(); i++){
		predators[i].run(predators, *withPreys, velocityFactor, maxWidth, maxHeight);
	}
}

template <class T, class U>
void PredatorPrey<T, U>::run(float velocityFactor, float maxWidth, float maxHeight){
	runPreys(velocityFactor, maxWidth, maxHeight);
	runPredators(velocityFactor, maxWidth, maxHeight);
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
		preys[i].render(1, 1, 1);
	}
}
template <class T, class U>
void PredatorPrey<T, U>::renderPredators(){
	if( !predatorsPresent ) return;

	for( int i = 0; i < predators.size(); i++){
		predators[i].render(1, 0, 0);
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