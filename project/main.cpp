
/*
 * main.cpp
 *
 *  Created on: Apr 30, 2018
 *      Author: anfrodriguezri
 */

#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <iterator>
#include <tuple>

#include "helpers/oglhelpers.h"
#include "LSystems/LSystem.h"
#include "Flocking/Boid.h"
#include "PredatorPrey/PredatorPrey.h"


#define WINDOW_TITLE_PREFIX "Alife"

using namespace std;

const float VIEW_WIDTH = 1200;
const float VIEW_HEIGHT = 700;

unsigned FrameCount = 0;

int step = 20;

int cameraX = 40;
int cameraY = 0;
int cameraZ = 0;

vector<LSystem> lsystems;
PredatorPrey<Boid> flock;


void drawWalls(bool);
void createTrees(int);
static void display(void);
static void key(unsigned char, int, int);
void TimerFunction(int);
static void resize(int width, int height);
static void idle(void);

int main(int argc, char *argv[]){
    srand( time(NULL) );
    glutInit(&argc, argv);
    glutInitWindowSize(VIEW_WIDTH, VIEW_HEIGHT);
    glutInitWindowPosition(100, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("L-System 2D");
    glutReshapeFunc( resize );
    glutDisplayFunc( display );
    glutKeyboardFunc( key );
    glutTimerFunc(0, TimerFunction, 0);
    glutIdleFunc( idle );
    glClearColor(0, 0, 0, 1);

    createTrees(4);

    flock = PredatorPrey<Boid>();
    // Add an initial set of boids into the system
    for (int i = 0; i < 50; i++) {
        flock.addBoid( Boid(VIEW_WIDTH/2, VIEW_WIDTH/2) );
    }

    glutMainLoop();

    return EXIT_SUCCESS;
}
void drawWalls(bool draw){
    if( draw ){
        drawLine(0, 0, 0, VIEW_HEIGHT);
        drawLine(0, 0, VIEW_WIDTH, 0);
        drawLine(0, VIEW_HEIGHT, VIEW_WIDTH, VIEW_HEIGHT);
        drawLine(VIEW_WIDTH, 0, VIEW_WIDTH, VIEW_HEIGHT);
    }

}
void createTrees(int numTrees){
    for( int i = 0; i < numTrees; i++ ){
        LSystem ls = LSystem(VIEW_WIDTH, VIEW_HEIGHT, true);
        ls.setRandom();
        lsystems.push_back(ls);
    }
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(cameraX, 0, 0);
    glTranslatef(0, cameraY, 0);

    glRasterPos2f(20, VIEW_HEIGHT - 55);
    drawString("Crecer arbol: Key +");
    glRasterPos2f(VIEW_WIDTH/2 - 50, VIEW_HEIGHT - 40);
    drawString("L-SYSTEM 2D");

    drawWalls(true);
    
    for(int i = 0; i < lsystems.size(); i++){
        lsystems[i].draw();
    }    

    flock.run(VIEW_WIDTH, VIEW_HEIGHT);

    ++FrameCount;

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y){
    switch (key){
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'w':
            cameraY -= step;
            break;

        case 's':
            cameraY += step;
            break;

        case 'a':
            cameraX += step;
            break;

        case 'd':
            cameraX -= step;
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
      VIEW_WIDTH,
      VIEW_HEIGHT
    );

    glutSetWindowTitle(TempString);
    free(TempString);
  }

  FrameCount = 0;
  glutTimerFunc(250, TimerFunction, 1);
}
static void resize(int width, int height){
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
