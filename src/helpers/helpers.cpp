#include <iostream>

#include "helpers.h"

using namespace std;

void drawString(std::string message, GLfloat x, GLfloat y){
    glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(.18,.17,0);
		glColor3f(0, 0, 0);

	    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)message.c_str());
    glPopMatrix();
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void drawTriangle(GLfloat x, GLfloat y, GLfloat theta, GLfloat sideLength){
	glPushMatrix();
		glTranslatef(x, y, 0);
	    glRotatef(theta, 0, 0, 1);

	    glBegin(GL_TRIANGLES);
	        glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -sideLength*2, 0);
	        glTexCoord2f(1.0f, 1.0f); glVertex3f(-sideLength, sideLength*2, 0);
	        glTexCoord2f(1.0f, 0.0f); glVertex3f(sideLength, sideLength*2, 0);
	    glEnd();
    glPopMatrix();
}

void drawCircle(GLfloat x, GLfloat y, GLfloat radius){
	int triangleAmount = 20; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * M_PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(int i = 0; i <= triangleAmount; i++) { 
			glVertex2f(
		        x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
float randFloat(float max, float min){
    float diff = max - min;
    
    return (((float) rand() / RAND_MAX) * diff) + min;
}

vector<uint8_t> floatToBytes(float f){
	union Float {
	    float    m_float;
	    uint8_t  m_bytes[sizeof(float)];
	};

	Float float_union;
	
	vector<uint8_t> v;

	float_union.m_float = f;

	for( int i = 0; i < sizeof(float); i++ ){
		v.push_back(float_union.m_bytes[i]);
	}
	
	return v;
}

float bytesToFloat(vector<uint8_t> v){
	uint8_t m_bytes[sizeof(float)];

	for(int i = 0; i < sizeof(float); i++ ){
		m_bytes[i] = v[i];
	}
	return *(float*)(m_bytes);
};
vector<uint8_t> intToBytes(int paramInt){
	vector<uint8_t> v;
	for (int i = 0; i < sizeof(int); i++){
		v.push_back( paramInt >> (i * 8) );
	}

	return v;
}
int bytesToInt(vector<uint8_t> v){
	int i = int((unsigned char)(v[3]) << 24 |
            (unsigned char)(v[2]) << 16 |
            (unsigned char)(v[1]) << 8 |
            (unsigned char)(v[0]));

	return i;
};

string byteToString(int byte){
	string s;

	unsigned char mask = 1; // Bit mask
	for (int i = 7; i >= 0; i--) {
	    int bit = (int)((byte & (mask << i)) != 0);
	    s += to_string(bit);
	}

	return s;
};

int stringToByte(string s){
	int inum;
	for(int i = 7; i >= 0; i--){
		int bit = s[i] - '0';
		if( bit )
			inum += pow(2, 7-i);
	}

	return inum;
}

string floatToBits(float f){
	vector<uint8_t> bytes = floatToBytes(f);

	string s;
	for( int i = bytes.size() - 1; i >= 0 ; i-- ){
		s += byteToString(bytes[i]);
	}
	return s;
}

float bitsToFloat(string s){
	vector<uint8_t> v;

	for( int i = 0; i < sizeof(float); i++ ){
		string sub = s.substr(i*8,8);
		v.push_back( stringToByte(sub) );
	}
	reverse(v.begin(), v.end());

	return bytesToFloat(v);
}

string intToBits(int inum){
	vector<uint8_t> bytes = intToBytes(inum);
	string s;

	for( int i = bytes.size() - 1; i >= 0 ; i-- ){
		s += byteToString(bytes[i]);
	}
	return s;
}

float bitsToInt(string s){
	vector<uint8_t> v;

	for( int i = 0; i < sizeof(float); i++ ){
		v.push_back( stringToByte(s.substr(i*8,8)) );
	}
	reverse(v.begin(), v.end());

	return bytesToInt(v);
}