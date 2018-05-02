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

class Figure {
	protected:
        tuple<float, float> position;
        float angle;

    public:
        Figure();
        virtual ~Figure();
        float getX();
        float getY();
        float getAngle();
        void setX(float);
        void setY(float);
        void setAngle(float);
};
#endif /* FIGURE_H_ */

