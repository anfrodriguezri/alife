/*
 * Figure.h
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#ifndef FIGURE_H_
#define FIGURE_H_

#include <tuple>

using namespace std;

typedef tuple<float, float> Vector2d;

class Figure {
	protected:
        tuple<float, float> position;
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

