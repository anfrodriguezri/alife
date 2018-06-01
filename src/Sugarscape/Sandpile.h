#ifndef SANDPILE_H_
#define SANDPILE_H_

#include <vector>
#include <tuple>

#include "../Base/Vector2d.h"

using namespace std;

class Sandpile {
    private:
        void initializeMatrix();
        void calculateGrainLocations();
        void calculateRadious();

	protected:
        Vector2d position;
        int size;
        vector<vector<int>> sandpile2d;
        vector<vector<Vector2d>> grainLocations;
        float capacity;
        float grainResource;
        float radious;
        
    public:
        Sandpile();
        Sandpile(float x, float y, int size, float max);
        Sandpile(Vector2d position, int size, float max);
        Vector2d getPosition();
        float getRadious();
        float getCapacity();
        void dropGrain();
        void updateNeighbours(int, int);
        void collapseGrains();
        Vector2d getBestGrainLocation(Vector2d position);
        int getResource(Vector2d foodPosition);
        void update();
        void render(float r, float g, float b);
        void print();
        void run();
        
        
        virtual ~Sandpile();
};
#endif /* SANDPILE_H_ */

