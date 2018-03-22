/*
* C++ - Plantas en 2D usando L-System
* Copyright 2014 Martin Cruz Otiniano
* Description: Genera plantas usando una gramática (regla) para su crecimiento.
* Site: martincruz.me
*/
 
// #include <windows.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <utility>
#include <vector>

#define PI  3.14159265358979323846
#define DEGTORAD PI/180.0f  // Grados a radianes

using namespace std;

// Ancho y alto de ventana
const float WIN_WIDTH = 800;
const float WIN_HEIGHT = 750;

// Movimiento de camara en 2D
int cameraX = 0;
int cameraY = 0;
int cameraZ = 0;

// Caracteristicas del LSysstem
string   AXIOMA  = "";
string   REGLA = "";
unsigned NIVEL_PRODUCCION = 0;
float    ANGULO    = 0.0f;
bool     orientacionLinea;   // verticial(true) u horizontal(false)

struct LSystem2D {
    string              axioma;             // palabra inicial
    pair<char, string>  regla;              // Ejm: F -> F+[F+F]F ...
    float               angulo;
};

// Estructura para guardar posicion y angulo cuando recorremos el axioma
struct Nodo {
    float x_;
    float y_;
    float angle_;
};

void inline DrawString(string message)
{
    string::iterator it = message.begin();

    for (; it != message.end(); ++it)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *it);

}

void DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glBegin(GL_LINE_STRIP);
        glColor3f(0, 1, 0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}

void LSystem(string w, float inicioX, float inicioY)
{
    unsigned i = 0;

    float xo = inicioX;
    float yo = inicioY;
    float xf = xo;
    float yf = yo;

    stack<Nodo> nodos;
    Nodo nodoActual;

    float angleRot = 0.0f;  // horizontal

    if (orientacionLinea){
        angleRot = 90.0f;  // En vertical
    }

    while ( i < w.size() )
    {
        switch (w[i])
        {
            case 'F' :
                xf = xo + 5.0f * cos( angleRot * DEGTORAD );
                yf = yo + 5.0f * sin( angleRot * DEGTORAD );
                DrawLine(xo, yo, xf, yf);
                xo = xf;
                yo = yf;
                break;

            case '[' :
                nodoActual.x_ = xf;
                nodoActual.y_ = yf;
                nodoActual.angle_ = angleRot;
                nodos.push(nodoActual);
                break;

            case ']' :
                xo = nodos.top().x_;
                yo = nodos.top().y_;
                xf = xo;
                yf = yo;
                angleRot = nodos.top().angle_;
                nodos.pop();
                break;

            case '+' :
                angleRot += ANGULO;
                break;

            case '-' :
                angleRot -= ANGULO;
                break;
        }

        i++;
    }
}

string GenerarPalabra(string axioma, string F, unsigned nivelProduccion)
{
    // Cuenta la posición de la cadena (axioma) donde se ecuentra
    unsigned n = 0;

    while (n <= nivelProduccion)
    {
        int cont = 0;

        while ( cont < axioma.size() )
        {
            if ( axioma[cont]== 'F' )
            {
                axioma.insert(cont, F);  // Insertamos la cadena, es decir regla F
                cont += F.size();        // Se actualiza la posicion al aumentar el tamaño del axioma
                axioma.erase(cont, 1);   // Se elimina el F anterior
            }
            else
            {
                cont++;
            }
        }

        n++;
    }

    cout << "n = " << nivelProduccion << endl;
    cout << axioma << endl;

    return axioma;
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(cameraX, 0, 0);
    glTranslatef(0, cameraY, 0);

    // Texto en pantalla
    glRasterPos2f(20, WIN_HEIGHT - 40);
    DrawString("Mover       : Keys WASD");
    glRasterPos2f(20, WIN_HEIGHT - 55);
    DrawString("Crecer arbol: Key +");
    glRasterPos2f(WIN_WIDTH/2 - 50, WIN_HEIGHT - 40);
    DrawString("L-SYSTEM 2D");

    // Dibujado del LSystem
    LSystem(AXIOMA, WIN_WIDTH/2, 10);

    glutSwapBuffers();
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

        case '+':
            AXIOMA = GenerarPalabra(AXIOMA, REGLA, 0);
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

void menuOpcion()
{
    cout << "\t L-System"               << endl << endl;
    cout << " 1. FF-[-F+F+F]+[+F-F-F]"  << endl;
    cout << " 2. F[+F]F[-F]F"           << endl;
    cout << " 3. F[+F]F[-F][F]"         << endl;
    cout << " 4. Salir"                 << endl << endl;
    cout << " Opcion > ";
}

int main(int argc, char *argv[]){
    unsigned opcion;

    /// L-System predefinidos
    struct LSystem2D LS1, LS2, LS3;

    LS1.axioma = "F";
    LS1.regla = make_pair('F', "FF-[-F+F+F]+[+F-F-F]");
    LS1.angulo = 22.5f;

    LS2.axioma = "F";
    LS2.regla = make_pair('F', "F[+F]F[-F]F");
    LS2.angulo = 25.7f;

    LS3.axioma = "++++F";
    LS3.regla = make_pair('F', "F[+F]F[-F][F]");
    LS3.angulo = 20.0f;

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(100, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("L-System 2D");
    glutReshapeFunc( resize );
    glutDisplayFunc( display );
    glutKeyboardFunc( key );
    glutIdleFunc( idle );
    glClearColor(0, 0, 0, 1);

    do
    {
        menuOpcion(); cin >> opcion; cout << endl;

        switch (opcion)
        {
            case 1:
                AXIOMA = LS1.axioma;
                REGLA  = LS1.regla.second;
                ANGULO = LS1.angulo;
                NIVEL_PRODUCCION = 0;
                orientacionLinea = true;  // vertical

                AXIOMA = GenerarPalabra(AXIOMA, REGLA, NIVEL_PRODUCCION);
                glutMainLoop();
                break;

            case 2:

                AXIOMA = LS2.axioma;
                REGLA  = LS2.regla.second;
                ANGULO = LS2.angulo;
                NIVEL_PRODUCCION = 0;
                orientacionLinea = true;  // vertical

                AXIOMA = GenerarPalabra(AXIOMA, REGLA, NIVEL_PRODUCCION);
                glutMainLoop();
                break;
            case 3:
                AXIOMA = LS3.axioma;
                REGLA  = LS3.regla.second;
                ANGULO = LS3.angulo;
                NIVEL_PRODUCCION = 0;
                orientacionLinea = false;  // horizontal

                AXIOMA = GenerarPalabra(AXIOMA, REGLA, NIVEL_PRODUCCION);
                glutMainLoop();
        }

    } while (opcion != 4);

    return EXIT_SUCCESS;
}
//gcc main.c -o OpenGLExample -lglut -lGL -lGLEW -lGLU