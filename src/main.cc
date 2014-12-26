
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "application.hh"


using namespace std;

static Application app;

const char *g_title = "splatterman";
const int   g_xres  = 800; 
const int   g_yres  = 600;


static GLFWwindow* main_window = NULL;

static void on_key( GLFWwindow* win, int key, int scancode, int action, int mods ) {

  if( action == GLFW_PRESS ) 
    app.current_mode()->on_key_down( key );
  else
    app.current_mode()->on_key_up( key );
}

static void cleanup() {

  app.cleanup();

  glfwTerminate();
}

int main(int argc, char ** argv ) {

  struct timespec ts;


//  char buffer[200]; 
//  float previous; 

  atexit(cleanup);

  srand(time(NULL));

  //glfwSetErrorCallback(on_glfw_error);

  if(!glfwInit()) {
    cerr << "could not init glfw" << endl;
    return -1;
  }

  atexit(cleanup);

  main_window = glfwCreateWindow(g_xres, g_yres, g_title, NULL, NULL);

  if(!main_window) {
    cerr << "could not create window" << endl;
    return -1;
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

  app.init();

//  previous = glfwGetTime();
  ts.tv_sec  = 0;
  ts.tv_nsec = 50 * 1000;

  while(!glfwWindowShouldClose(main_window)) {

/*     float now = glfwGetTime();
 *     float fps = (1.0 / (now - previous));
 *     previous = now;
 * 
 *     snprintf( buffer, 200, "%s (%.2f fps)", g_title, fps );
 *     glfwSetWindowTitle( main_window, buffer );
 */
    

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    app.current_mode()->move();

    app.current_mode()->draw();

    glfwSwapBuffers(main_window);
    glfwPollEvents();

    nanosleep( &ts, NULL ); 
  }


  return 0;
}


