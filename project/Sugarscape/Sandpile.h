#ifndef SANDPILE_H_
#define SANDPILE_H_

#include <vector>

using namespace std;

class Sandpile {
	protected:
        float x;
        float y;
        int size;
        vector<vector<int>> sandpile2d;
        float max;
        float grainResource;

    public:
        Sandpile();
        Sandpile(float x, float y, int size, float max);
        void initializeMatrix();
        void dropGrain();
        void updateNeighbours(int, int);
        void collapseGrains();
        void update();
        void render(float r, float g, float b, float space);
        void run(float space);
        void print();
        virtual ~Sandpile();
};
#endif /* SANDPILE_H_ */

