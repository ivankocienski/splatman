
#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <string.h>

#include "board.hh"
#include "board-data.hh"

Board::Board() {
  m_grid = new  unsigned char [ 28 * 31 ];
  if(!m_grid) { throw "failed to alloc grid buffer"; }
  
  reset();
}

void Board::reset() {

  memcpy( m_grid, board_data, 28 * 31);
}

void Board::draw() {

  unsigned char *b = m_grid;

  int x;
  int y;


  glBegin( GL_QUADS );

  for( y = 0; y < 31; y++ )
    for( x = 0; x < 28; x++ ) {

      int cx = x * 16 + 8;
      int cy = y * 16 + 8;

      switch( *b) {
        case '#':
          glColor3f( 0, 0, 1 );

          glVertex2f( cx - 8, cy - 8 );
          glVertex2f( cx + 8, cy - 8 );
          glVertex2f( cx + 8, cy + 8 );
          glVertex2f( cx - 8, cy + 8 );
          break;

        case '.':
          glColor3f( 0.6, 0.6, 0.6 );

          glVertex2f( cx - 2, cy - 2 );
          glVertex2f( cx + 2, cy - 2 );
          glVertex2f( cx + 2, cy + 2 );
          glVertex2f( cx - 2, cy + 2 );
          break;

      }

      b++;
    }
      

  glEnd();
}

bool Board::actor_can_go( int x, int y ) {

  x >>= 4;
  y >>= 4;

  // the mid map warp points hack
  if( y == 14 ) {
    if( x <  1 ) return true;
    if( x > 26 ) return true;
  }

  if(x < 0 || x >= 27) return false;
  if(y < 0 || y >= 30) return false;

  unsigned  char c = m_grid[ (y * 28) + x ];


  return c != '#' && c != '-';
}

int Board::clear_pip( int x, int y ) {

  x >>= 4;
  y >>= 4;


  if(x < 0 || x > 28) return 0;
  if(y < 0 || y > 31) return 0;

  unsigned char *c = m_grid + (y * 28) + x;

  if(*c == '.') {
    *c = ' ';
    return 1;
  }

  return 0;
}
