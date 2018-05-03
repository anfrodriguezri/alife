/*
 * LSystem.h
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#ifndef LSYSTEM_H_
#define LSYSTEM_H_

#include <string>
#include <vector>

using namespace std;

#include "../helpers/oglhelpers.h"
#include "../Base/Figure.h"

class LSystem : public Figure {
	protected:
        int depth;
        string axiom;
        string word;
        vector< pair<char, std::string> > rules;
        float lineLength = 1.0;
	public:
		LSystem();
		LSystem(float, float, bool);
		LSystem(int, float, string, vector< pair<char, string> >);
		float getLineLength();
		void setLineLength(float);
		void generateWord();
		void draw();
		void setParams(int, float, string, vector< pair<char, string> >);
		void setTree(char);
		void setRandom();
		string toString();
		virtual ~LSystem();
};
#endif /* LSYSTEM_H_ */
