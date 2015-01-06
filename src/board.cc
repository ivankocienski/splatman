
#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <string.h>

#include "board.hh"
#include "board-data.hh"
#include "graphics.hh"

Board::Board( Graphics *g ) {
  
  m_graphics = g;

  m_grid = new  unsigned char [ 28 * 31 ];
  if(!m_grid) { throw "failed to alloc grid buffer"; }
  
  reset();
}

void Board::reset() {

  memcpy( m_grid, board_data, 28 * 31);

  m_pip_count = 0;

  for( int i = 0; i < 28 * 31; i++ ) {
    if( m_grid[i] == '.' ) m_pip_count++;
  }

  cout << "board:: pip_count=" << m_pip_count << endl;
}

void Board::draw() {

  unsigned char *b = m_grid;

  int x;
  int y;

  for( y = 0; y < 31; y++ )
    for( x = 0; x < 28; x++ ) {

      switch( *b) {
        case '.':
          m_graphics->draw_pip( (x << 3), (y << 3) + 16 );
          break;

        case '*':
          m_graphics->draw_pill( (x << 3), (y << 3) + 16 );
          break;
      }

      b++;
    }
}

bool Board::actor_can_go( int x, int y ) {

  x >>= 3;
  y >>= 3;

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

  x >>= 3;
  y >>= 3;

  if(x < 0 || x > 28) return 0;
  if(y < 0 || y > 31) return 0;

  unsigned char *c = m_grid + (y * 28) + x;

  if(*c == '.') {
    *c = ' ';
    return 1;
  }

  return 0;
}

int Board::clear_pill( int x, int y ) {

  x >>= 3;
  y >>= 3;

  if(x < 0 || x > 28) return 0;
  if(y < 0 || y > 31) return 0;

  unsigned char *c = m_grid + (y * 28) + x;

  if(*c == '*') {
    *c = ' ';
    return 1;
  }

  return 0;
}

int Board::pip_count() {
  return m_pip_count;
}

