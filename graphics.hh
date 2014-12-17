
#pragma once

#include <GL/gl.h>

class Graphics {
private:

  GLuint m_board; 
  GLuint m_misc;
  GLuint m_player;

  GLuint load_image(const char*);

public:

  Graphics();

  bool init();
  void cleanup();

  void draw8(int, int, int);

  void draw_board( int, int );
  void draw_pip(int, int);
  void draw_pill(int, int);

  void draw_player( int, int, int );
  
};
