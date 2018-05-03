/*
 * LSystem.cpp
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#include <string>
#include <vector>

#include <stack>
#include <math.h>

#include "LSystem.h"
#include "../Base/Turtle.h"

#include <iostream>

using namespace std;

LSystem::LSystem(){}
LSystem::LSystem(float x, float y, bool maximumVals){
    if( maximumVals ){
        float randx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float randy = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        x = (randx * x + 0);
        y = (randy * y + 0);
    }
    setPosition(x, y);
}
LSystem::LSystem(int depth, float angle, string axiom, vector<pair<char, string>> rules){
    setParams(depth, angle, axiom, rules);
}
float LSystem::getLineLength(){
	return lineLength;
}
void LSystem::setLineLength(float length){
    lineLength = length;
};
void LSystem::generateWord(){
	for( int d = 0, i = 0; d < depth; d++){
        for( int i = 0; i < word.size(); i++){
            for( int r = 0; r < rules.size(); r++ ){
                char character = rules[r].first;
                string replacement = rules[r].second;

                if( (char)word[i] == character ){
                    word.replace(i, 1, replacement);
                    i += replacement.size();
                    break;
                }
            }
        }
    }
};
void LSystem::draw(){
    float x0, y0;
    tie(x0, y0) = position.getTuple();
    
    float x1 = x0;
    float y1 = y0;

    stack<Turtle> savedStates;
    Turtle currentTurtle;

    float angleRot = 0.0f; // horizontal

    if(true){
        angleRot = 90.0f;  // En vertical
    }

    for( int i = 0; i < word.size(); i++ ){
        //angleRot += (rand() % 5 - 1)/5.f;
        switch(word[i]){
            case 'F':
                x1 = x0 + lineLength * cos( angleRot * DEGTORAD );
                y1 = y0 + lineLength * sin( angleRot * DEGTORAD );
                
                drawLine(x0, y0, x1, y1);
                x0 = x1;
                y0 = y1;
                break;
            case '[':
                currentTurtle.setPosition(x1, y1);
                currentTurtle.setAngle(angleRot);
                savedStates.push(currentTurtle);
                break;
            case ']':
                tie(x0, y0) = savedStates.top().getPosition().getTuple();
                x1 = x0;
                y1 = y0;
                angleRot = savedStates.top().getAngle();
                savedStates.pop();
                break;
            case '+':
                angleRot += angle;
                break;
            case '-':
                angleRot -= angle;
                break;
        }
    }
};
void LSystem::setParams(int depth, float angle, string axiom, vector<pair<char, string>> rules){
    this->depth = depth;
    this->angle = angle;
    this->axiom = axiom;
    this->word = this->axiom;
    this->rules = rules;
    this->lineLength = 1.5;
    generateWord();
}
void LSystem::setTree(char code){
    vector<pair<char, string>> rules;
    
    switch(code){
        case 'A':
            rules.push_back( make_pair('F', "F[+F]F[-F]F") );
            setParams(4, 25.7, "F", rules);
            break;
        case 'B':
            rules.push_back( make_pair('F', "F[+F]F[-F][F]") );
            setParams(5, 20, "F", rules);
            break;
        case 'C':
            rules.push_back( make_pair('F', "FF-[-F+F+F]+[+F-F-F]") );
            setParams(4, 22.5, "F", rules);
            break;
        case 'D':
            rules.push_back( make_pair('X', "F[+X]F[-X]+X") );
            rules.push_back( make_pair('F', "FF") );
            setParams(7, 20, "X", rules);
            break;
        case 'E':
            rules.push_back( make_pair('X', "F[+X][-X]FX") );
            rules.push_back( make_pair('F', "FF") );
            setParams(7, 25.7, "X", rules);
            break;
        case 'F':
            rules.push_back( make_pair('X', "F-[[X]+X]+F[+FX]-X") );
            rules.push_back( make_pair('F', "FF") );
            setParams(5, 22.5, "X", rules);
            break;
    }
}
void LSystem::setRandom(){
    char code = 'A' + (rand() % 5 + 0);
    setTree(code);
}
string LSystem::toString(){
    string tostring = "LSystem: {" + to_string(depth) + "; "
                        + to_string(angle) + "; "
                        + axiom + "; {";

    
    for( int i = 0; i < rules.size(); i++){
        char character = rules[i].first;
        string replacement = rules[i].second;
        tostring += character;
        tostring += ": " + replacement + ", ";
    }

    tostring += "}, " + to_string(lineLength) + "}";

    return tostring;
}
LSystem::~LSystem() {}