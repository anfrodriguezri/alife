
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

#include "helpers/helpers.h"
#include "LSystems/LSystem.h"
#include "Flocking/Boid.h"
#include "PredatorPrey/PredatorPrey.h"
#include "PredatorPrey/Predator.h"
#include "Sugarscape/Sugarscape.h"
#include "TuringPattern/TuringPattern.h"


#define WINDOW_TITLE_PREFIX "Alife"

#define ESC 27
#define SPACEBAR 32

using namespace std;

const float VIEW_WIDTH = 1200;
const float VIEW_HEIGHT = 700;

float velocityFactor;

unsigned FrameCount;

int step;

int cameraX;
int cameraY;
int cameraZ;

float r, g, b;

vector<LSystem> lsystems;
PredatorPrey<Boid, Predator> predatorPrey;
Sugarscape sugarscape;

bool showMenu;
bool showTrees;

bool debugMode;
bool spaceBarPressed;

int ticks;

string lastKeyCombination;

vector<string> commands {
    "Toggle Menu: m",
    "Toggle Trees: t",
    "Toggle Preys: p",
    "Toggle Predators: ALT + p",
    "Toggle Sugarscape: ALT + s",
    "Toggle Death From Starvation: ALT + d",
    "Toggle Alls: ALT + a",
    "Reset: r",
    "Debug Mode: 0",
    "Play/Pause: SPACEBAR",
    "Exit: q or ESC",
};

TuringPattern tp;
GLuint texture;


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
    glClearColor(1, 1, 1, 1);

    glEnable(GL_DEPTH_TEST);

    setup();
    
    glutMainLoop();

    return EXIT_SUCCESS;
}
void drawWalls(bool draw){
    glColor3f(1, 1, 1);
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

        Vector2d treePosition = ls.getPosition();

        sugarscape.addSandpile( Sandpile(treePosition, 7, sugarscape.getCapacity() ) );
    }
}
void setup(){
    velocityFactor = 1;
    FrameCount = 0;
    ticks = 0;

    step = 20;

    cameraX = 40;
    cameraY = 0;
    cameraZ = 0;

    lsystems = vector<LSystem>();

    showMenu = true;
    showTrees = false;

    debugMode = false;
    spaceBarPressed = false;

    lastKeyCombination = "";

    tp = TuringPattern();
    texture = tp.create();

    predatorPrey = PredatorPrey<Boid, Predator>();
    // Add an initial set of boids into the system


    r = randFloat(0.5,1);
    g = randFloat(0, 0.5);
    b = 0;
    for (int i = 0; i < 3; i++) {
        predatorPrey.addPredator( Predator(0.1*VIEW_WIDTH, 0.1*VIEW_HEIGHT, r, g, b, texture) );
    }

    r = 0;
    g = randFloat(0, 0.5);
    b = randFloat(0.5,1);
    
    for (int i = 0; i < 15; i++) {
        float x = randFloat(0, 1) * VIEW_WIDTH;
        float y = randFloat(0, 1) * VIEW_HEIGHT;
        predatorPrey.addPrey( Boid(x, y, r, g, b, texture) );
    }

    sugarscape = Sugarscape(100);
    createTrees(2);
}

static void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(cameraX, 0, 0);
    glTranslatef(0, cameraY, 0);

    drawWalls(true);

    if( showMenu ){        
        drawString("Alife", VIEW_WIDTH/2 - 50, VIEW_HEIGHT - 50);

        for( int i = 0, h = 100; i < commands.size(); i++, h+=30){
            drawString(commands[i], 0.02 * VIEW_WIDTH, VIEW_HEIGHT - h);
        }

        vector<pair<string, string>> dynamicCommands;

        int preysNum = predatorPrey.getPreysPresent() ? predatorPrey.getPreys().size() : 0;
        int predatorNum = predatorPrey.getPredatorsPresent() ? predatorPrey.getPredators().size() : 0;

        dynamicCommands.push_back( make_pair("Last Key Combination: ", lastKeyCombination) );
        dynamicCommands.push_back( make_pair("Preys: ", to_string(preysNum)) );
        dynamicCommands.push_back( make_pair("Predators: ", to_string(predatorNum)) );
        dynamicCommands.push_back( make_pair("Velocity Factor: ", to_string(velocityFactor)) );

        for( int i = 0, h = 100; i < dynamicCommands.size(); i++, h+=30){
            string dynamicCommand = dynamicCommands[i].first + dynamicCommands[i].second;
            drawString(dynamicCommand, 0.65 * VIEW_WIDTH, VIEW_HEIGHT - h);
        }
    }

    if( showTrees ){
        for(int i = 0; i < lsystems.size(); i++){
            lsystems[i].draw();
        }   
    }
    if( ticks % 200 == 0 || ticks % 200 == 1 ){
        predatorPrey.toggleReproducing();
    }
    if( !debugMode && spaceBarPressed || debugMode && spaceBarPressed ){
        if( debugMode)
            spaceBarPressed = false;

        sugarscape.run();
    }else{
        int numOfReproductions = predatorPrey.run(sugarscape, velocityFactor, VIEW_WIDTH, VIEW_HEIGHT);
        //cout << numOfReproductions << endl;
        for( int i = 0; i < numOfReproductions; i++ ){
            float x = randFloat(0, 1) * VIEW_WIDTH;
            float y = randFloat(0, 1) * VIEW_HEIGHT;
            predatorPrey.addPrey( Boid(x, y, r, g, b, texture) );            
        }

        predatorPrey.render();

        sugarscape.render();
    }

    ++FrameCount;
    ticks++;
    glutSwapBuffers();
    glFlush();
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
            if( glutGetModifiers() & GLUT_ACTIVE_ALT ){
                lastKeyCombination += " + ALT";
                sugarscape.togglePresence();
                predatorPrey.toggleDeathFromStarvation();
                predatorPrey.togglePreys();
                predatorPrey.togglePredators();
                showTrees = !showTrees;
                break;
            }
            cameraX += step;
            break;
        case 'D':
        case 'd':
            if( glutGetModifiers() & GLUT_ACTIVE_ALT ){
                lastKeyCombination += " + ALT";
                predatorPrey.toggleDeathFromStarvation();
                break;
            }
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
        case 'R':
        case 'r':
            setup();
            break;
        case '+':
            velocityFactor += 0.1;
            break;
        case '-':
            velocityFactor -= 0.1;
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
