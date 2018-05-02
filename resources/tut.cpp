#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <math.h>
#include <stack>
#include <utility>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define WINDOW_TITLE_PREFIX "Alife"

using namespace std;

#define PI  3.14159265358979323846
#define DEGTORAD PI/180.0f  // Grados a radianes

struct Turtle {
    float x;
    float y;
    float angle;
};

int
  CurrentWidth = 800,
  CurrentHeight = 750,
  WindowHandle = 0;

int cameraX = 0;
int cameraY = 0;
int cameraZ = 0;

unsigned FrameCount = 0;

int depth = 2;
string axiom = "F";
float angle = 22.5f;
string rule = "F[+F]F[-F]F";

string word = axiom;

void drawString(string);
void drawLine(GLfloat, GLfloat, GLfloat, GLfloat);
void generateWord();
void drawLSystem(void);
void RenderFunction(void);
void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void TimerFunction(int);
void IdleFunction(void);

int main(int argc, char* argv[]){
    Initialize(argc, argv);

    generateWord();
    glutMainLoop();
    exit(EXIT_SUCCESS);
}
static void key(unsigned char key, int x, int y)
{
    int id;
    switch (key)
    {
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
void drawString(string message){
    string::iterator it = message.begin();

    for (; it != message.end(); ++it){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *it);
    }

}
void drawLine(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1){
    glBegin(GL_LINE_STRIP);
        glColor3f(0, 1, 0);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
    glEnd();
}
void generateWord(){
    for( int d = 0, i = 0; d < depth; d++){
        for( int i = 0; i < word.size(); ){
            if( word[i] == 'F' ){
                word.insert(i, rule);
                word.erase(i, 1);
                i += rule.size();
            }else
                i++;
            // word.replace(i, 1, rule);
        }
    }

    // cout << "n = " << nivelProduccion << endl;
    // cout << axioma << endl;
}
void drawLSystem(){
    float lsystemX = CurrentWidth/2.0f;
    float lsystemY = 10.0f;

    float x0 = lsystemX;
    float y0 = lsystemY;
    float x1 = x0;
    float y1 = y0;

    stack<Turtle> savedStates;
    Turtle currentTurtle;

    float angleRot = 0.0f;  // horizontal

    if (false){
        angleRot = 90.0f;  // En vertical
    }

    for( int i = 0; i < word.size(); i++ ){
        switch(word[i]){
            case 'F':
                x1 = x0 + 5.0f * cos( angleRot * DEGTORAD );
                y1 = y0 + 5.0f * sin( angleRot * DEGTORAD );
                drawLine(x0, y0, x1, y1);
                x0 = x1;
                y0 = y1;
                break;
            case '[':
                currentTurtle.x = x1;
                currentTurtle.y = y1;
                currentTurtle.angle = angleRot;
                savedStates.push(currentTurtle);
                break;
            case ']':
                x0 = savedStates.top().x;
                y0 = savedStates.top().y;
                x1 = x0;
                y1 = y0;
                angleRot = savedStates.top().angle;
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
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}
void RenderFunction(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    DrawCircle(0.5, 0.5, 0.2, 5);

    /*glTranslatef(cameraX, 0, 0);
    glTranslatef(0, cameraY, 0);*/

    // Texto en pantalla
    glRasterPos2i(20, CurrentHeight - 40);
    drawString("Mover       : Keys WASD");
    glRasterPos2i(20, CurrentHeight - 55);
    drawString("Crecer arbol: Key +");
    glRasterPos2i(CurrentWidth/2 - 50, CurrentHeight - 40);
    drawString("L-SYSTEM 2D");
    
    drawLine(0, 0, 20, 20);
    //drawLSystem();

    ++FrameCount;

    glutSwapBuffers();
}
void Initialize(int argc, char* argv[]){
  GLenum GlewInitResult;

  InitWindow(argc, argv);

  GlewInitResult = glewInit();

  if (GLEW_OK != GlewInitResult) {
    fprintf(
      stderr,
      "ERROR: %s\n",
      glewGetErrorString(GlewInitResult)
    );
    exit(EXIT_FAILURE);
  }

  fprintf(
    stdout,
    "INFO: OpenGL Version: %s\n",
    glGetString(GL_VERSION)
  );

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[]){
  glutInit(&argc, argv);
  
  glutInitContextVersion(4, 0);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutSetOption(
    GLUT_ACTION_ON_WINDOW_CLOSE,
    GLUT_ACTION_GLUTMAINLOOP_RETURNS
  );
  
  glutInitWindowSize(CurrentWidth, CurrentHeight);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

  if(WindowHandle < 1) {
    fprintf(
      stderr,
      "ERROR: Could not create a new rendering window.\n"
    );
    exit(EXIT_FAILURE);
  }

  glutReshapeFunc(ResizeFunction);
  glutDisplayFunc(RenderFunction);
  glutIdleFunc(IdleFunction);
  glutTimerFunc(0, TimerFunction, 0);
  glutKeyboardFunc( key );
}

void ResizeFunction(int Width, int Height){
  CurrentWidth = Width;
  CurrentHeight = Height;
  glViewport(0, 0, CurrentWidth, CurrentHeight);
}
void IdleFunction(void){
  glutPostRedisplay();
}
void TimerFunction(int Value){
  if (0 != Value) {
    char* TempString = (char*)
      malloc(512 + strlen(WINDOW_TITLE_PREFIX));

    sprintf(
      TempString,
      "%s: %d Frames Per Second @ %d x %d",
      WINDOW_TITLE_PREFIX,
      FrameCount * 4,
      CurrentWidth,
      CurrentHeight
    );

    glutSetWindowTitle(TempString);
    free(TempString);
  }
  
  FrameCount = 0;
  glutTimerFunc(250, TimerFunction, 1);
}