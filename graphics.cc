
#include <string.h>
#include <stdlib.h>
#include "third-party/png++/png.hpp"

#include "graphics.hh"


//static const char *file = "sprites.png";

Graphics::Graphics() {

}

Graphics::~Graphics() {

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
  

  return true;
}


void Graphics::draw8(int dx, int dy, int n) {

  // ... profit!
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
