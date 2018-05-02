#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <tuple>
#include <math.h>

#define DEGTORAD M_PI/180.0f  // Grados a radianes

using namespace std;

class Vector2d {
    protected:
        float x;
        float y;
    public:
    	Vector2d();
    	virtual ~Vector2d();
    	float getX();
    	void setX(float);
    	float getY();
    	void setY(float);
        void setXY(float, float);
        tuple<float, float> getTuple();
        void add(Vector2d);
        float magnitude();
        Vector2d& mult(float scalar);
        Vector2d& div(float scalar);
        Vector2d& normalize();
        Vector2d& limit(float max);
        float heading();
};

#endif /* VECTOR2D_H_ */