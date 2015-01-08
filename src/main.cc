

#include <iostream>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "application.hh"
#include "common.hh"

using namespace std;

byte g_anim = 0;

static Application *p_app = NULL; // aaah. 
static const int p_fps    = 45;

const char *g_title = "splatman";
const int   g_xres  = 800; 
const int   g_yres  = 600;

static GLuint s_scale_texture   = 0;
static GLFWwindow* main_window = NULL;

static void on_key( GLFWwindow* win, int key, int scancode, int action, int mods ) {

  if( action == GLFW_PRESS ) 
    p_app->current_mode()->on_key_down( key );
  else
    p_app->current_mode()->on_key_up( key );
}

static void run() {

  char buffer[200]; 
  float previous; 

  struct timespec ts;

  Application app;
  p_app = &app;

  previous = glfwGetTime();
  ts.tv_sec  = 0;
  ts.tv_nsec = ( 1.0 / (float)p_fps) * 1000;

  int dx1 = g_xres / 2 - 224;
  int dy1 = g_yres / 2 - 288;
  int dx2 = g_xres / 2 + 224;
  int dy2 = g_yres / 2 + 288;

  while(!glfwWindowShouldClose(main_window)) {

    float now = glfwGetTime();
    float fps = (1.0 / (now - previous));
    previous = now;

    snprintf( buffer, 200, "%s (%.2f fps)", g_title, fps );
    glfwSetWindowTitle( main_window, buffer );
    
    //glLoadIdentity();
    
    app.current_mode()->move();

    // render game
    glClear( GL_COLOR_BUFFER_BIT );
    app.current_mode()->draw();
    
    glFlush();

    // copy to back buffer
    glBindTexture( GL_TEXTURE_2D, s_scale_texture );
    glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 0, g_yres - 288, 224, 288, 0 );

    glClear( GL_COLOR_BUFFER_BIT );

    // scale and center ...
    glBegin( GL_QUADS );

    glTexCoord2d( 0, 1); glVertex2f( dx1, dy1 );
    glTexCoord2d( 1, 1); glVertex2f( dx2, dy1 );
    glTexCoord2d( 1, 0); glVertex2f( dx2, dy2 );
    glTexCoord2d( 0, 0); glVertex2f( dx1, dy2 );

    glEnd();

    // uh, CRT emulator. make this use shaders.
/*     glDisable( GL_TEXTURE_2D );
 *     glColor4f( 0, 0, 0, 0.4 );
 *     glBegin( GL_LINES );
 *     for(int i = 0; i < g_yres; i += 2 ) {
 *       glVertex2f( 0, i );
 *       glVertex2f( g_xres, i );
 *     }
 *     glEnd();
 * 
 *     glColor4f( 1, 1, 1, 1 );
 *     glEnable( GL_TEXTURE_2D );
 */

    glfwSwapBuffers(main_window);
    glfwPollEvents();

    //nanosleep( &ts, NULL ); 

    g_anim++;
  }
}

static void init() {

  srand(time(NULL));

  //glfwSetErrorCallback(on_glfw_error);

  if(!glfwInit()) {
    cerr << "could not init glfw" << endl;
    exit(-1);
  }

  main_window = glfwCreateWindow(g_xres, g_yres, g_title, NULL, NULL);

  if(!main_window) {
    cerr << "could not create window" << endl;
    exit(-1);
  } 

  glfwMakeContextCurrent(main_window);

  glfwSetKeyCallback( main_window, on_key );

  glViewport(0, 0, g_xres, g_yres);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0.0, g_xres, g_yres, 0.0, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f( 1, 1, 1 );

  glGenTextures( 1, &s_scale_texture );
  glBindTexture( GL_TEXTURE_2D, s_scale_texture );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGB,
    224,
    288,
    0, // border
    GL_RGB,
    GL_UNSIGNED_BYTE,
    0 
  );
}

int main(int argc, char ** argv ) {

  init();
  
  run();

  glfwTerminate();

  return 0;
}


