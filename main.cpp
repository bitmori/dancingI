#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

namespace BigI {
void draw() {
  glColor3f(244/255.0, 127/255.0, 36/255.0); // set current color to orange
  glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0.3, 1, 0.4);//1
      glVertex3f(0, 1, 0.4);//2
      glVertex3f(0, 0.8, 0.4);//3
      glVertex3f(0.2, 0.8, 0.4);//4
      glVertex3f(0.2, 0.2, 0.4);//5
      glVertex3f(0.4, 0.2, 0.4);//6
      glVertex3f(0.4, 0.8, 0.4);//7
      glVertex3f(0.6, 0.8, 0.4);//8
      glVertex3f(0.6, 1, 0.4);//9
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.4);//10
    glVertex3f(0.0, 0.2, 0.4);//11
    glVertex3f(0.2, 0.2, 0.4);//12
    glVertex3f(0.4, 0.2, 0.4);//13
    glVertex3f(0.6, 0.2, 0.4);//14
    glVertex3f(0.6, 0.0, 0.4);//15
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0.3, 1, 0.6);//1
      glVertex3f(0, 1, 0.6);//2
      glVertex3f(0, 0.8, 0.6);//3
      glVertex3f(0.2, 0.8, 0.6);//4
      glVertex3f(0.2, 0.2, 0.6);//5
      glVertex3f(0.4, 0.2, 0.6);//6
      glVertex3f(0.4, 0.8, 0.6);//7
      glVertex3f(0.6, 0.8, 0.6);//8
      glVertex3f(0.6, 1, 0.6);//9
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(0.0, 0.2, 0.6);//10
      glVertex3f(0.2, 0.2, 0.6);//11
      glVertex3f(0.0, 0.0, 0.6);//12
      glVertex3f(0.4, 0.2, 0.6);//13
      glVertex3f(0.6, 0.0, 0.6);//14
      glVertex3f(0.6, 0.2, 0.6);//15
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glVertex3f(0, 0, 0.4);
    glVertex3f(0, 0, 0.6);
    glVertex3f(0, 0.2, 0.4);
    glVertex3f(0, 0.2, 0.6);
    glVertex3f(0.2, 0.2, 0.4);
    glVertex3f(0.2, 0.2, 0.6);
    glVertex3f(0.2, 0.8, 0.4);
    glVertex3f(0.2, 0.8, 0.6);
    glVertex3f(0, 0.8, 0.4);
    glVertex3f(0, 0.8, 0.6);
    glVertex3f(0, 1, 0.4);
    glVertex3f(0, 1, 0.6);
    glVertex3f(0.6, 1, 0.4);
    glVertex3f(0.6, 1, 0.6);
    glVertex3f(0.6, 0.8, 0.4);
    glVertex3f(0.6, 0.8, 0.6);
    glVertex3f(0.4, 0.8, 0.4);
    glVertex3f(0.4, 0.8, 0.6);
    glVertex3f(0.4, 0.2, 0.4);
    glVertex3f(0.4, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.4);
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0, 0.4);
    glVertex3f(0.6, 0, 0.6);
    glVertex3f(0, 0, 0.4);
    glVertex3f(0, 0, 0.6);
  glEnd();
}

char window_title[64];
void calculateFPS()
{
  static float fps=0.0f;                    //the value of fps
  static float frames    = 0.0f;            // the number of frame that has been rendered
  static float previousTime   = 0.0f;       // previous moment
  float currentTime =  glutGet(GLUT_ELAPSED_TIME)* 0.001f;//the elapsed time
  ++frames;
  if( currentTime - previousTime > 1.0f )// update fps every second
  {
      fps=frames;
      sprintf(window_title, "CS 418 MP1 keyang4 - FPS: %.0f", fps);
      previousTime = currentTime;
      frames= 0;
  }
  // print value to titlebar
  glutSetWindowTitle(window_title);
}
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  BigI::draw();
  BigI::calculateFPS();
  glFlush();
  glutSwapBuffers();
}

void timer(int v) {
  static GLfloat u = 0.0;
  u += 0.01;
  glLoadIdentity();
  // the animation is actually the movement of the camera along the curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2)
  // the camera will always looking at the center of the I
  // the changing up vector will give out an interesting effect.
  gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
  glutPostRedisplay();
  glutTimerFunc(1000/60.0, timer, v);
}

// callback when window is reshaped
void reshape(int w, int h) {
  // set the viewport as (0, 0) to (w, h)
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // camera having a 60 degree vertical, aspect ratio = w/h, near = 0.5, far = 40
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

// The big I is not a convex polyhedron, thus we should not enable back face culling
void init() {
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  glClearColor(0,60/255.0,125/255.0,1.0); // set background to navy
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw wireframe model
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 27) //ESC
  {
    printf("demonstration finished.\n");
    exit(0);
  }
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //set double buffering and rgb mode
  glutInitWindowSize(800, 600);
  glutCreateWindow("Initializing..");

  glutTimerFunc(100, timer, 0);// a periodic timer. Usually used for updating animation
  glutDisplayFunc(display); // called when drawing
  glutReshapeFunc(reshape); // called when change window size
  glutKeyboardFunc(keyboard); // called when received keyboard interaction
  
  init(); // init some key features

  glutMainLoop();
}