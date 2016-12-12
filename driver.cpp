//CS370 Computer Graphics
//Final Project
//By Maxwell Meier, Samual Kahsay, Saw Yan Naung, Victor Zuniga
//3D Maze Driver


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "mazealg.cpp"
#define PI 3.1415926
using namespace std;

GLdouble eye_x = 2, eye_y = 6, eye_z = 0, look_x = 2, look_y = 2, look_z = 2, rotation = 1, rotang = PI/10;
GLdouble p_eye_x, p_eye_z, p_look_x, p_look_z; //To save the player's position
bool maze[MAX_X][MAX_Z];

//<<<<<<<<<<<<<<<<<Keyboard to move around>>>>>>>>>>>>>>>>>>>>>

void keyboard(unsigned char key, int x, int y){
  double space = 0.2;
  switch(key){
  case 27:
    exit(0);
  case 'w':
    eye_z += space*cos(rotation);
    eye_x += space*sin(rotation);
    look_z += space*cos(rotation);
    look_x += space*sin(rotation);
    p_eye_x = eye_x;
    p_eye_z = eye_z;
    p_look_x = look_x;
    p_look_z = look_z;
    // cout << "eye_x = " << eye_x << endl;
    // cout << "eye_z = " << eye_z << endl;
    // cout << "look_x = " << look_x << endl;
    // cout << "look_z = " << look_z << endl;
    break;
  case 's':
    eye_z -= space*cos(rotation);
    eye_x -= space*sin(rotation);
    look_z -= space*cos(rotation);
    look_x -= space*sin(rotation);
    p_eye_x = eye_x;
    p_eye_z = eye_z;
    p_look_x = look_x;
    p_look_z = look_z;
    // cout << "eye_x = " << eye_x << endl;
    // cout << "eye_z = " << eye_z << endl;
    // cout << "look_x = " << look_x << endl;
    // cout << "look_z = " << look_z << endl;
    break;
  case 'a':
    rotation += rotang;
    look_z = eye_z + cos(rotation);
    look_x = eye_x + sin(rotation);
    p_look_x = look_x;
    p_look_z = look_z;
    // cout << "eye_x = " << eye_x << endl;
    // cout << "eye_z = " << eye_z << endl;
    // cout << "look_x = " << look_x << endl;
    // cout << "look_z = " << look_z << endl;
    break;
  case 'd':
    rotation -= rotang;
    look_z = eye_z + cos(rotation);
    look_x = eye_x + sin(rotation);
    p_look_x = look_x;
    p_look_z = look_z;
    // cout << "eye_x = " << eye_x << endl;
    // cout << "eye_z = " << eye_z << endl;
    // cout << "look_x = " << look_x << endl;
    // cout << "look_z = " << look_z << endl;
    break; 
  case 'e':      //eagle-eye mode
     eye_x = 6; eye_y = 4; eye_z = 6; look_x = 2; look_y = 0; look_z = 1.5;
    break;
  case 'q':      //first person mode
    eye_x = p_eye_x; eye_z = p_eye_z; look_x = p_look_x; look_z = p_look_z;
    break;
    
  }
  gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0,1.0,0.0);

  glutPostRedisplay();
}

//<<<<<<<<<<<<<<< wall >>>>>>>>>>>>>>>>
void wall()
{ 
  glPushMatrix();
  glTranslated(0.5, 0.5, 0.5);
  glScaled(0.1, 0.1, 0.1);
  glutSolidCube(1.0);
  glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<< DrawMaze >>>>>>>>>>>>>>>>>>>>>>
void drawmaze(void)
{
  // set properties of the surface material
  GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f}; // gray
  GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat mat_shininess[] = {50.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

  // set the light source properties
  GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

  // set the camera
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double winHt = 1.0; // half-height of the window
  glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0.0,1.0,0.0);

  // start drawing
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
  
  for(unsigned int x = 0; x < sizeof(maze)/sizeof(maze[0]); x++)
    {
      for(unsigned int z = 0; z < sizeof(maze)/sizeof(maze[0]); z++)
        {
          if (maze[x][z] == true)
            {
              glPushMatrix();
              glTranslated((0.1*x), 0, (0.1*z));
              wall();
              glPopMatrix();
            }
        }
    }   
  glFlush();
}

int main(int argc, char **argv)
{
  //Initiating the array
  for(unsigned int a = 0; a < sizeof(maze)/sizeof(maze[0]); a++){
    for(unsigned int b = 0; b < sizeof(maze[0])/sizeof(maze[0][0]); b++){
      maze[a][b] = true;
    }
  }
  generate_maze(&maze); //generating 2D array
  for(unsigned int c = 0; c < sizeof(maze)/sizeof(maze[0]); c++){
    for(unsigned int d = 0; d < sizeof(maze[0])/sizeof(maze[0][0]); d++){     
      cout<<maze[c][d]<<" ";
    }
    cout<<endl;
  }
 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("3D Maze Final Project");
  glutDisplayFunc(drawmaze);
  glEnable(GL_LIGHTING); // enable the light source
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST); // for hidden surface removal
  glEnable(GL_NORMALIZE); // normalize vectors for proper shading
  glClearColor(0.1f,0.1f,0.1f,0.0f); // background is light gray
  glViewport(0, 0, 640, 480);
  glutKeyboardFunc(keyboard);
  cout << "KEYS TO CONTROL" << endl;
  cout << "Press W to go forwards" << endl;
  cout << "Press S to go backwards" << endl;
  cout << "Press A to turn left" << endl;
  cout << "Press D to turn right" << endl;
  cout << "Press E to activate eaglemode (see from above)" << endl;
  cout << "Press Q to return to player mode" << endl;
  cout << "Press Esc to quit the program" << endl;
  glutMainLoop();
  
  return 0;
}
