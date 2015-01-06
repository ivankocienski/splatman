
#include <string.h>
#include <stdlib.h>
#include "third-party/png++/png.hpp"

#include "graphics.hh"

// 42 glyphs
static const int font_ascii[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
  0, 40, 39, 42, 41,  0,  0,  0,  0,  0,  0,  0,  0, 39,  0, 37, 
 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,  0,  0,  0,  0,  0, 
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 
 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,  0,  0,  0,  0,  0, 
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 
 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,  0,  0,  0,  0,  0
};

//static const char *file = "sprites.png";

Graphics::Graphics() {
  m_board  = 0;
  m_misc   = 0;
  m_player = 0;
  m_ghosts = 0;
  m_score_graphics = 0;
  m_logo   = 0;
}


GLuint Graphics::load_image( const char *from ) {

  GLuint tex;

  png::image< png::rgba_pixel >image;
  image.read(from);

  int w = image.get_width();
  int h = image.get_height();

  unsigned char *data = NULL;
  data = (unsigned char*)calloc( w * h * 4, sizeof(unsigned char));
  if(!data) return 0;

  unsigned char *d = data;

  for( int y = 0; y < h; y++ ) {

    png::image< png::rgba_pixel >::row_type const & row = image.get_row(y);

    for(int x = 0; x < w; x++ ) {

      *d = row.at(x).red;   d++;
      *d = row.at(x).green; d++;
      *d = row.at(x).blue;  d++;
      *d = row.at(x).alpha; d++;
    }
  }


  glGenTextures( 1, &tex );
  glBindTexture( GL_TEXTURE_2D, tex );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    w,
    h,
    0, // border
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    data 
  );

  free(data);

  return tex;
}

bool Graphics::init() {

  m_board = load_image( "data/board.png" );
  if(!m_board) return false;

  m_misc  = load_image( "data/misc.png" );
  if(!m_misc) return false;

  m_player = load_image( "data/player.png" );
  if(!m_player) return false;

  m_ghosts = load_image( "data/ghosts.png" );
  if(!m_ghosts) return false;

  m_font = load_image( "data/font.png" );
  if(!m_font) return false;

  m_score_graphics = load_image( "data/score-graphics.png" );
  if(!m_score_graphics) return false;

  m_logo = load_image( "data/logo.png" );
  if(!m_logo) return false;

  return true;
}

void Graphics::cleanup() {

  if(m_board)   glDeleteTextures( 1, &m_board );
  if(m_misc)    glDeleteTextures( 1, &m_misc );
  if(m_player)  glDeleteTextures( 1, &m_player );
  if(m_ghosts)  glDeleteTextures( 1, &m_ghosts );
  if(m_font)    glDeleteTextures( 1, &m_font );
  if(m_score_graphics) glDeleteTextures( 1, &m_score_graphics );
  if(m_logo)    glDeleteTextures( 1, &m_logo );
}

void Graphics::draw_board( int x, int y ) {

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_board );

  glBegin( GL_QUADS );

  glTexCoord2d( 0, 0); glVertex2f(     x, y     );
  glTexCoord2d( 1, 0); glVertex2f( x+224, y     );
  glTexCoord2d( 1, 1); glVertex2f( x+224, y+248 );
  glTexCoord2d( 0, 1); glVertex2f(     x, y+248 );

  glEnd();
}

void Graphics::draw_pip(int x, int y) {

  float d = 1.0 / 12.0;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_misc );

  glBegin( GL_QUADS );

  glTexCoord2d( 0, 0); glVertex2f(   x, y   );
  glTexCoord2d( d, 0); glVertex2f( x+8, y   );
  glTexCoord2d( d, 1); glVertex2f( x+8, y+8 );
  glTexCoord2d( 0, 1); glVertex2f(   x, y+8 );

  glEnd();
}

void Graphics::draw_pill(int x, int y) {

  float d = 1.0 / 12.0;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_misc );

  glBegin( GL_QUADS );

  glTexCoord2d( d*1, 0); glVertex2f(   x, y   );
  glTexCoord2d( d*2, 0); glVertex2f( x+8, y   );
  glTexCoord2d( d*2, 1); glVertex2f( x+8, y+8 );
  glTexCoord2d( d*1, 1); glVertex2f(   x, y+8 );

  glEnd();
}

void Graphics::draw_player( int x, int y, int n ) {

  float d = 1.0 / 20.0;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_player );

  glBegin( GL_QUADS );

  glTexCoord2d( d*n,     0); glVertex2f(    x, y    );
  glTexCoord2d( d*(n+1), 0); glVertex2f( x+16, y    );
  glTexCoord2d( d*(n+1), 1); glVertex2f( x+16, y+16 );
  glTexCoord2d( d*n,     1); glVertex2f(    x, y+16 );

  glEnd();
}

void Graphics::draw_logo( int x, int y, int n ) {

  float d = 1.0 / 8.0;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_logo );

  glBegin( GL_QUADS );

  glTexCoord2d( d*n,     0); glVertex2f(    x, y    );
  glTexCoord2d( d*(n+1), 0); glVertex2f( x+16, y    );
  glTexCoord2d( d*(n+1), 1); glVertex2f( x+16, y+16 );
  glTexCoord2d( d*n,     1); glVertex2f(    x, y+16 );

  glEnd();
}

void Graphics::draw_ghost( int x, int y, int n, int c ) {

  float dx = 1.0 / 8.0;
  float dy = 1.0 / 5.0;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_ghosts );

  glBegin( GL_QUADS );

  glTexCoord2d( dx*n,     dy*c);     glVertex2f(    x, y    );
  glTexCoord2d( dx*(n+1), dy*c);     glVertex2f( x+16, y    );
  glTexCoord2d( dx*(n+1), dy*(c+1)); glVertex2f( x+16, y+16 );
  glTexCoord2d( dx*n,     dy*(c+1)); glVertex2f(    x, y+16 );

  glEnd();
}

void Graphics::draw_font_string( int x, int y, const char *c ) {

  float d = 1.0 / 43;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_font );

  glBegin( GL_QUADS );

  while(*c) {

    float dx = font_ascii[(unsigned char)*c] * d;

    glTexCoord2d( dx,   0); glVertex2f(   x, y   );
    glTexCoord2d( dx+d, 0); glVertex2f( x+8, y   );
    glTexCoord2d( dx+d, 1); glVertex2f( x+8, y+8 );
    glTexCoord2d( dx,   1); glVertex2f(   x, y+8 );

    c++;
    x += 8;
  }

  glEnd();
}

void Graphics::draw_font_number( int x, int y, int n ) {

  float d = 1.0 / 43;

//  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_font );

  glBegin( GL_QUADS );

  x -= 8;
  if(!n) {

    float dx = 27 * d;

    glTexCoord2d( dx,   0); glVertex2f(   x, y   );
    glTexCoord2d( dx+d, 0); glVertex2f( x+8, y   );
    glTexCoord2d( dx+d, 1); glVertex2f( x+8, y+8 );
    glTexCoord2d( dx,   1); glVertex2f(   x, y+8 );
  }

  while(n) {

    float dx = ((n % 10) + 27) * d;

    glTexCoord2d( dx,   0); glVertex2f(   x, y   );
    glTexCoord2d( dx+d, 0); glVertex2f( x+8, y   );
    glTexCoord2d( dx+d, 1); glVertex2f( x+8, y+8 );
    glTexCoord2d( dx,   1); glVertex2f(   x, y+8 );

    n /= 10;
    x -= 8;
  }

  glEnd();
}

void Graphics::draw_score( int x, int y, int n ) {
  float d = 1.0 / 4.0;

  glBindTexture( GL_TEXTURE_2D, m_score_graphics );

  glBegin( GL_QUADS );

  glTexCoord2d( d*n,     0); glVertex2f(    x, y    );
  glTexCoord2d( d*(n+1), 0); glVertex2f( x+16, y    );
  glTexCoord2d( d*(n+1), 1); glVertex2f( x+16, y+16 );
  glTexCoord2d( d*n,     1); glVertex2f(    x, y+16 );

  glEnd();
}
