#ifndef SUGARSCAPE_H_
#define SUGARSCAPE_H_

#include <vector>
#include "Sandpile.h"

using namespace std;

class Sugarscape {
	protected:
		bool present;
		float capacity;
		vector<Sandpile> sandpiles;

	public:
		Sugarscape();
		Sugarscape(float capacity);
		void togglePresence();
		float getCapacity();
		vector<Sandpile> getSandpiles();
		void addSandpile(Sandpile);
		void run();
		void render();
		virtual ~Sugarscape();
};
#endif /* SUGARSCAPE_H_ */