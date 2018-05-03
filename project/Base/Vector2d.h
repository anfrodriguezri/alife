#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <tuple>
#include <math.h>

#define DEGTORAD M_PI/180.0f  // Grados a radianes
#define RADTODEG 180.0f/M_PI  // Radianes a grados

using namespace std;

class Vector2d {
    protected:
        float x;
        float y;
    public:
    	Vector2d();
        Vector2d(float, float);
    	virtual ~Vector2d();
        static float dist(Vector2d, Vector2d);
        static Vector2d sub(Vector2d v1, Vector2d v2);
    	float getX();
    	void setX(float);
    	float getY();
    	void setY(float);
        void setXY(float, float);
        tuple<float, float> getTuple();
        void add(Vector2d);
        void sub(Vector2d);
        Vector2d& mult(float);
        Vector2d& div(float);
        float magnitude();
        Vector2d& normalize();
        Vector2d& setMagnitude(float);
        Vector2d& limit(float);
        float heading();
        string toString();
};

#endif /* VECTOR2D_H_ */