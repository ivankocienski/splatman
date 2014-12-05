
#include <GL/gl.h>

#include "board.hh"
#include "board-data.hh"

Board::Board() {}

void Board::draw() {

  const char *b = board_data;

  int x;
  int y;

  glColor3f( 0, 0, 1 );

  glBegin( GL_QUADS );

  for( y = 0; y < 31; y++ )
    for( x = 0; x < 28; x++ ) {

      if( *b == '#' ) {
        glVertex2f( x * 16, y * 16 );
        glVertex2f( x * 16 + 16, y * 16 );
        glVertex2f( x * 16 + 16, y * 16 + 16);
        glVertex2f( x * 16, y * 16 + 16);
      }

      b++;
    }
      

  glEnd();
}
