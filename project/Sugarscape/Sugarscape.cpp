#include "Sugarscape.h"

Sugarscape::Sugarscape(){}

Sugarscape::Sugarscape(float capacity){
	present = false;

	this->capacity = capacity;
}

void Sugarscape::togglePresence(){
	present = !present;
}
bool Sugarscape::isPresent(){
	return present;
}
float Sugarscape::getCapacity(){
	return capacity;
}
vector<Sandpile> Sugarscape::getSandpiles(){
	return sandpiles;
}
void Sugarscape::addSandpile(Sandpile sandpile){
	sandpiles.push_back(sandpile);
}
void Sugarscape::run(){
	if( !present ) return;

	for(int i = 0; i < sandpiles.size(); i++){
		sandpiles[i].run();
	}
}

void Sugarscape::render(){
	if( !present ) return;

	for(int i = 0; i < sandpiles.size(); i++){
		sandpiles[i].render(1, 1, 0);
	}
}
Sugarscape::~Sugarscape(){}