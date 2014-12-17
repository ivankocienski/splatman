
#pragma once

#include <GL/gl.h>

class Graphics {
private:

  GLuint m_board;

  GLuint m_surface;

  GLuint load_image(const char*);

public:

  Graphics();
  ~Graphics();

  bool init();
  void cleanup();

  void draw8(int, int, int);

  void draw_board( int, int );
};
