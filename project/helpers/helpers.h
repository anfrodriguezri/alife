#ifndef OGL_HELPERS_H_
#define OGL_HELPERS_H_

#include <GL/freeglut.h>
#include <string>
#include <math.h>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

void drawString(std::string message, GLfloat x, GLfloat y);
void drawLine(GLfloat, GLfloat, GLfloat, GLfloat);
void drawTriangle(GLfloat, GLfloat, GLfloat, GLfloat);
void drawCircle(GLfloat x, GLfloat y, GLfloat radius);
float randFloat(float max, float min);

vector<uint8_t> floatToBytes(float f);
float bytesToFloat(vector<uint8_t>);

vector<uint8_t> intToBytes(int f);
int bytesToInt(vector<uint8_t>);

string byteToString(int byte);
int stringToByte(string s);

string floatToBits(float);
float bitsToFloat(string s);

string intToBits(int inum);

float bitsToInt(string s);

#endif /* OGL_HELPERS_H_ */
