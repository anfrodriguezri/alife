#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <cstring>
#include <stack>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iterator>

#define PI  3.14159265358979323846
#define DEGTORAD PI/180.0f  // Grados a radianes

#define WINDOW_TITLE_PREFIX "Alife"

using namespace std;

float lineLength = 2.0f;

// Plant 1
// int depth = 4;
// float angle = 25.7;
// string axiom = "F";
// pair<char, string> rulesArr[1] = {
//     make_pair('F', "F[-FF][+F]F[−F]F")
// };
// vector<pair<char, string>> rules( std::begin(rulesArr), std::end(rulesArr) );
 

// Seaweed
// int depth = 4;
// float angle = 22;
// string axiom = "F";
// pair<char, string> rulesArr[1] = {
//     make_pair('F', "FF-[-F+F+F]+[+F-F-F]")
// };
// vector<pair<char, string>> rules( std::begin(rulesArr), std::end(rulesArr) );


// Seaweed
// int depth = 7;
// float angle = 20;
// string axiom = "X";
// pair<char, string> rulesArr[2] = {
//     make_pair('X', "F-[[X]+X]+F[+FX]-X"),
//     make_pair('F', "FF")
// };
// vector<pair<char, string>> rules( std::begin(rulesArr), std::end(rulesArr) );


const float width = 800;
const float height = 750;

int cameraX = 0;
int cameraY = 0;
int cameraZ = 0;

unsigned FrameCount = 0;

void DrawString(string);
void DrawLine(GLfloat, GLfloat, GLfloat, GLfloat);

class Figure {
    protected:
        float x;
        float y;
        float angle;

    public:
        float getX () { return x; }
        float getY () { return y; }
        float getAngle () { return angle; }
        void setX(float x) { this->x = x; }
        void setY(float y) { this->y = y; }
        void setAngle(float angle) { this->angle = angle; }
};
class Turtle: public Figure {};


class LSystem: public Figure {
    int depth;
    string axiom;
    string word;
    vector<pair<char, string>> rules;
    float lineLength;

    public:
        LSystem(){}
        LSystem(int depth, float angle, string axiom, vector<pair<char, string>> rules, float lineLength){
            this->depth = depth;
            this->angle = angle;
            this->axiom = axiom;
            this->word = axiom;
            this->rules = rules;
            this->lineLength = lineLength;
        }
        float getLineLength() { return lineLength; }
        void setLineLength(float length) { this->lineLength = length; }
        void generateWord(){
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
        }
        void draw(){
            float lsystemX = width/2.0f;
            float lsystemY = 30.0f;

            float x0 = x;
            float y0 = y;
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
                        DrawLine(x0, y0, x1, y1);
                        x0 = x1;
                        y0 = y1;
                        break;
                    case '[':
                        currentTurtle.setX(x1);
                        currentTurtle.setY(y1);
                        currentTurtle.setAngle(angleRot);
                        savedStates.push(currentTurtle);
                        break;
                    case ']':
                        x0 = savedStates.top().getX();
                        y0 = savedStates.top().getY();
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
        }
};
LSystem lsystem;

static void display(void);
static void key(unsigned char, int, int);
void TimerFunction(int);
static void resize(int width, int height);
static void idle(void);

int main(int argc, char *argv[]){

    srand( time(NULL) );
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("L-System 2D");
    glutReshapeFunc( resize );
    glutDisplayFunc( display );
    glutKeyboardFunc( key );
    glutTimerFunc(0, TimerFunction, 0);
    glutIdleFunc( idle );
    glClearColor(0, 0, 0, 1);

    int depth = 7;
    float angle = 20;
    string axiom = "X";
    pair<char, string> rulesArr[2] = {
        make_pair('X', "F-[[X]+X]+F[+FX]-X"),
        make_pair('F', "FF")
    };
    vector<pair<char, string>> rules( std::begin(rulesArr), std::end(rulesArr) );
    lsystem = LSystem(depth, angle, axiom, rules, 2.0);
    lsystem.generateWord();
    glutMainLoop();

    return EXIT_SUCCESS;
}

void DrawString(string message){
    string::iterator it = message.begin();

    for (; it != message.end(); ++it)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *it);

}

void DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
    glBegin(GL_LINE_STRIP);
        glColor3f(1, 1, 1);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(cameraX, 0, 0);
    glTranslatef(0, cameraY, 0);

    glRasterPos2f(20, height - 55);
    DrawString("Crecer arbol: Key +");
    glRasterPos2f(width/2 - 50, height - 40);
    DrawString("L-SYSTEM 2D");

    lsystem.draw();

    ++FrameCount;

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y){
    int id;
    switch (key){
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'w':
            cameraY -= 5;
            break;

        case 's':
            cameraY += 5;
            break;

        case 'a':
            cameraX += 5;
            break;

        case 'd':
            cameraX -= 5;
            break;
    }

    glutPostRedisplay();
}
void TimerFunction(int Value){
  if (0 != Value) {
    char* TempString = (char*)
      malloc(512 + strlen(WINDOW_TITLE_PREFIX));

    sprintf(
      TempString,
      "%s: %d Frames Per Second @ %f x %f",
      WINDOW_TITLE_PREFIX,
      FrameCount * 4,
      width,
      height
    );

    glutSetWindowTitle(TempString);
    free(TempString);
  }
  
  FrameCount = 0;
  glutTimerFunc(250, TimerFunction, 1);
}
static void resize(int width, int height){
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}
static void idle(void){
    glutPostRedisplay();
}
//g++ lsystems.cpp -o lsystems -lglut -lGL -lGLEW -lGLU && ./lsystems