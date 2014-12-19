
#pragma once

#include <GL/gl.h>

class Graphics {
private:

  GLuint m_board; 
  GLuint m_misc;
  GLuint m_player;
  GLuint m_ghosts;
  GLuint m_font;
  GLuint m_score_graphics;

  GLuint load_image(const char*);

public:

  Graphics();

  bool init();
  void cleanup();

  void draw_board( int, int );
  void draw_pip(int, int);
  void draw_pill(int, int);

  void draw_player( int, int, int );
  void draw_ghost( int, int, int, int );

  void draw_font_number( int, int, int );
  void draw_font_string( int, int, const char* );

  void draw_score( int, int, int );
};
