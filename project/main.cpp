
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
#include "PredatorPrey/Predator.h"
#include "Sugarscape/Sugarscape.h"


#define WINDOW_TITLE_PREFIX "Alife"

#define ESC 27
#define SPACEBAR 32

using namespace std;

const float VIEW_WIDTH = 1200;
const float VIEW_HEIGHT = 700;

float velocityFactor = 1.5;

unsigned FrameCount = 0;

int step = 20;

int cameraX = 40;
int cameraY = 0;
int cameraZ = 0;

vector<LSystem> lsystems;
PredatorPrey<Boid, Predator> predatorPrey;
Sugarscape sugarscape;

bool showMenu = true;
bool showTrees = false;

bool debugMode = false;
bool spaceBarPressed = false;

string lastKeyCombination = "";

vector<string> commands {
    "Toggle Menu: 'm'",
    "Toggle Trees: 't'",
    "Toggle Preys: 'p'",
    "Toggle Predators: 'alt + p'",
    "Toggle Sugarscape: 'alt + s'",
    "Debug Mode: '0'",
    "Play/Pause: 'SPACEBAR'",
    "Exit: 'q or ESC'",
};

void drawWalls(bool);
void createTrees(int);
void setup();
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
    glutCreateWindow(WINDOW_TITLE_PREFIX);
    glutReshapeFunc( resize );
    glutDisplayFunc( display );
    glutKeyboardFunc( key );
    glutTimerFunc(0, TimerFunction, 0);
    glutIdleFunc( idle );
    glClearColor(0, 0, 0, 1);

    setup();
    
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
void setup(){
    createTrees(4);

    predatorPrey = PredatorPrey<Boid, Predator>();
    // Add an initial set of boids into the system
    for (int i = 0; i < 15; i++) {
        predatorPrey.addPrey( Boid(VIEW_WIDTH/2, VIEW_WIDTH/2) );
    }

    for (int i = 0; i < 3; i++) {
        predatorPrey.addPredator( Predator(0, 0) );
    }

    sugarscape = Sugarscape(20);

    sugarscape.addSandpile( Sandpile(400, 400, 3, sugarscape.getCapacity()) );
}
static void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(cameraX, 0, 0);
    glTranslatef(0, cameraY, 0);

    glColor3f(1, 1, 1);

    drawWalls(true);

    if( showMenu ){
        glRasterPos2f(VIEW_WIDTH/2 - 50, VIEW_HEIGHT - 20);
        drawString("Alife");

        for( int i = 0, h = 50; i < commands.size(); i++, h+=20){
            glRasterPos2f(0.02 * VIEW_WIDTH, VIEW_HEIGHT - h);    
            drawString(commands[i]);
        }

        vector<pair<string, string>> dynamicCommands;

        dynamicCommands.push_back( make_pair("Last Key Combination: ", lastKeyCombination) );

        for( int i = 0, h = 50; i < dynamicCommands.size(); i++, h+=20){
            glRasterPos2f(0.75 * VIEW_WIDTH, VIEW_HEIGHT - h);    
            drawString(dynamicCommands[i].first + dynamicCommands[i].second);
        }
    }

    if( showTrees ){
        for(int i = 0; i < lsystems.size(); i++){
            lsystems[i].draw();
        }   
    }

    if( !debugMode && spaceBarPressed || debugMode && spaceBarPressed ){
        if( debugMode)
            spaceBarPressed = false;

        predatorPrey.run(velocityFactor, VIEW_WIDTH, VIEW_HEIGHT);

        sugarscape.run();
    }else{
        predatorPrey.render();

        sugarscape.render();
    }

    ++FrameCount;

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y){
    lastKeyCombination = key;
    switch (key){
        case ESC :
        case 'Q':
        case 'q':
            exit(0);
            break;
        case 'W':
        case 'w':
            cameraY -= step;
            break;
        case 'S':
        case 's':
            if( glutGetModifiers() & GLUT_ACTIVE_ALT ){
                lastKeyCombination += " + ALT";
                sugarscape.togglePresence();
                break;
            }
            cameraY += step;
            break;
        case 'A':
        case 'a':
            cameraX += step;
            break;
        case 'D':
        case 'd':
            cameraX -= step;
            break;
        case 'M':
        case 'm':
            showMenu = !showMenu;
            break;
        case 'T':
        case 't':
            showTrees = !showTrees;
            break;
        case 'P':
        case 'p':
            if( glutGetModifiers() & GLUT_ACTIVE_ALT ){
                lastKeyCombination += " + ALT";
                predatorPrey.togglePredators();
                break;
            }
            predatorPrey.togglePreys();
            break;
        case '0':
            debugMode = !debugMode;
            break;
        case SPACEBAR:
            lastKeyCombination = "SPACEBAR";
            spaceBarPressed = !spaceBarPressed;
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
