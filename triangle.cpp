#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include <SOIL.h>

using namespace std;

GLuint texture[1];

int LoadGLTextures()
{
    texture[0] = SOIL_load_OGL_texture
        (
        "./project/skins/alpha.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(texture[0] == 0)
        return false;


    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;
}

void ChangeSize(int w, int h)
{
    if(h == 0)
    {
        h = 1;
    }
    float ratio = 1.0f * w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,6.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
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
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    drawTriangle(0, 0, 0, .2);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.2f,  0.2f);
    glTexCoord2f(.5f, 0.0f); glVertex3f( 0.2f, -0.2f,  0.2f);
    glTexCoord2f(.5f, 0.2f); glVertex3f( 0.2f,  0.2f,  0.2f);
    glTexCoord2f(0.0f, .5f); glVertex3f(-0.2f,  0.2f,  0.2f);

    glEnd();

    glFlush();
}

void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("ZC");

    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glEnable(GL_DEPTH_TEST);

    LoadGLTextures();

    glutMainLoop();
}