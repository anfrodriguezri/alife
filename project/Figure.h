#ifndef FIGURE_H_
#define FIGURE_H_

#include <tuple>

#include "Vector2d.h"

using namespace std;

class Figure {
	protected:
        Vector2d position;
        float angle;

    public:
        Figure();
        virtual ~Figure();
        float getX(Vector2d);
        float getY(Vector2d);
        float getAngle();
        void setX(float, Vector2d&);
        void setY(float, Vector2d&);
        Vector2d getPosition();
        void setPosition(float, float);
        void setAngle(float);
};
#endif /* FIGURE_H_ */

