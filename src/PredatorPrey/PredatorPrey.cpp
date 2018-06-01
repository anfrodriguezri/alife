#include "PredatorPrey.h"

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
void PredatorPrey<T, U>::runPreys(Sugarscape sugarscape, float velocityFactor, float maxWidth, float maxHeight){
	if( !preysPresent ) return;

	vector<Predator> empty;
	vector<Predator>* withPredators = &empty;

	if( predatorsPresent )
		withPredators = &predators;

	for( int i = 0; i < preys.size(); i++){
		bool isAlive = preys[i].run(preys, *withPredators, sugarscape, velocityFactor, maxWidth, maxHeight, starvationDeath);

		if(!isAlive){
			preys.erase(preys.begin()+i);
		}
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
		bool isAlive = predators[i].run(predators, *withPreys, velocityFactor, maxWidth, maxHeight, starvationDeath);

		if(!isAlive){
			predators.erase(predators.begin()+i);
		}
	}
}

template <class T, class U>
void PredatorPrey<T, U>::run(Sugarscape sugarscape, float velocityFactor, float maxWidth, float maxHeight){
	runPreys(sugarscape, velocityFactor, maxWidth, maxHeight);
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
		preys[i].render(1, 1, 1, starvationDeath);
	}
}
template <class T, class U>
void PredatorPrey<T, U>::renderPredators(){
	if( !predatorsPresent ) return;

	for( int i = 0; i < predators.size(); i++){
		predators[i].render(1, 0, 0, starvationDeath);
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