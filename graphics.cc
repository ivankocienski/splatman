
#include <string.h>
#include <stdlib.h>
#include "third-party/png++/png.hpp"

#include "graphics.hh"


//static const char *file = "sprites.png";

Graphics::Graphics() {
  m_board  = 0;
  m_misc   = 0;
  m_player = 0;
  m_ghosts = 0;
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

  m_board = load_image( "board.png" );
  if(!m_board) return false;

  m_misc  = load_image( "misc.png" );
  if(!m_misc) return false;

  m_player = load_image( "player.png" );
  if(!m_player) return false;

  m_ghosts = load_image( "ghosts.png" );
  if(!m_ghosts) return false;

  return true;
}

void Graphics::cleanup() {

  if(m_board)   glDeleteTextures( 1, &m_board );
  if(m_misc)    glDeleteTextures( 1, &m_misc );
  if(m_player)  glDeleteTextures( 1, &m_player );
  if(m_ghosts)  glDeleteTextures( 1, &m_ghosts );
}

void Graphics::draw_board( int x, int y ) {

  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_board );

  glBegin( GL_QUADS );

  glTexCoord2d( 0, 0); glVertex2f(     x, y     );
  glTexCoord2d( 1, 0); glVertex2f( x+448, y     );
  glTexCoord2d( 1, 1); glVertex2f( x+448, y+496 );
  glTexCoord2d( 0, 1); glVertex2f(     x, y+496 );

  glEnd();
}

void Graphics::draw_pip(int x, int y) {

  float d = 1.0 / 12.0;

  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_misc );

  glBegin( GL_QUADS );

  glTexCoord2d( 0, 0); glVertex2f(    x, y    );
  glTexCoord2d( d, 0); glVertex2f( x+16, y    );
  glTexCoord2d( d, 1); glVertex2f( x+16, y+16 );
  glTexCoord2d( 0, 1); glVertex2f(    x, y+16 );

  glEnd();
}

void Graphics::draw_pill(int x, int y) {

  float d = 1.0 / 12.0;

  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_misc );

  glBegin( GL_QUADS );

  glTexCoord2d( d*1, 0); glVertex2f(    x, y    );
  glTexCoord2d( d*2, 0); glVertex2f( x+16, y    );
  glTexCoord2d( d*2, 1); glVertex2f( x+16, y+16 );
  glTexCoord2d( d*1, 1); glVertex2f(    x, y+16 );

  glEnd();
}

void Graphics::draw_player( int x, int y, int n ) {

  float d = 1.0 / 20.0;

  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_player );

  glBegin( GL_QUADS );

  glTexCoord2d( d*n,     0); glVertex2f(    x, y    );
  glTexCoord2d( d*(n+1), 0); glVertex2f( x+32, y    );
  glTexCoord2d( d*(n+1), 1); glVertex2f( x+32, y+32 );
  glTexCoord2d( d*n,     1); glVertex2f(    x, y+32 );

  glEnd();
}

void Graphics::draw_ghost( int x, int y, int n, int c ) {

  float dx = 1.0 / 8.0;
  float dy = 1.0 / 5.0;

  glColor3f( 1, 1, 1 );
  glBindTexture( GL_TEXTURE_2D, m_ghosts );

  glBegin( GL_QUADS );

  glTexCoord2d( dx*n,     dy*c);     glVertex2f(    x, y    );
  glTexCoord2d( dx*(n+1), dy*c);     glVertex2f( x+32, y    );
  glTexCoord2d( dx*(n+1), dy*(c+1)); glVertex2f( x+32, y+32 );
  glTexCoord2d( dx*n,     dy*(c+1)); glVertex2f(    x, y+32 );

  glEnd();
}
