
#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <stdlib.h>

#include "board.hh"
#include "ghost.hh"

static const int dir_xinc[] = { 0,  0, 0, -1, 1 };
static const int dir_yinc[] = { 0, -1, 1,  0, 0 };

Ghost::Ghost() {
  m_xpos  = 0;
  m_ypos  = 0;
  m_board = NULL;

  stop_and_go();
}

void Ghost::setup( Board *b, int x, int y ) {

  m_xpos  = x * 16 + 8;
  m_ypos  = y * 16 + 8;
  m_board = b;
}

void Ghost::draw() {

  glBegin( GL_QUADS );

  glColor3f( 1, 0, 0 );

  int cx = m_xpos;
  int cy = m_ypos;

  glVertex2f( cx - 8, cy - 8 );
  glVertex2f( cx + 8, cy - 8 );
  glVertex2f( cx + 8, cy + 8 );
  glVertex2f( cx - 8, cy + 8 );

  glEnd(); 
}

bool Ghost::is_at_intersection( ) {

  int mx = m_xpos & 15;
  int my = m_ypos & 15;

  return mx == 8 && my == 8;
}

bool Ghost::can_move( int d ) {
  
  if( !is_at_intersection() ) return true;

  int xm = d == GD_LEFT ? 9 : 8;
  int ym = d == GD_UP   ? 9 : 8;

  int nx = m_xpos + dir_xinc[d] * xm;
  int ny = m_ypos + dir_yinc[d] * ym;

  return m_board->player_can_go( nx, ny );
}

void Ghost::stop_and_go() {

  m_dir = GD_STATIONARY;
  m_hold = 20 + rand() % 100;
}

void Ghost::move() {

  cout << "hold=" << m_hold << "  dir=" << m_dir << endl;

  switch( m_dir ) { 
    case GD_STATIONARY:
      if( m_hold ) {
        m_hold--;
        return;
      }

      while( m_dir == GD_STATIONARY ) {

        int nd = 1 + rand() % 4;

        if( can_move(nd) ) {
          m_dir = nd;
        }

      }
      break;

    case GD_UP:
      if( is_at_intersection() && (rand() % 10 < 2 )) {

        if( rand() & 1 ) {
          if( can_move(GD_LEFT) ) m_dir = GD_LEFT;

        } else {
          if( can_move(GD_RIGHT) ) m_dir = GD_RIGHT;
        }

        return;
      }

      if( can_move(GD_UP) )
        m_ypos--;
      else
        stop_and_go();
      break;

    case GD_DOWN:

      if( is_at_intersection() && (rand() % 10 < 2 )) {

        if( rand() & 1 ) {
          if( can_move(GD_LEFT) ) m_dir = GD_LEFT;

        } else {
          if( can_move(GD_RIGHT) ) m_dir = GD_RIGHT;
        }

        return;
      }

      if( can_move(GD_DOWN) )
        m_ypos++;
      else
        stop_and_go();
      break;

    case GD_LEFT:

      if( is_at_intersection() && (rand() % 10 < 2 )) {

        if( rand() & 1 ) {
          if( can_move(GD_UP) ) m_dir = GD_UP;

        } else {
          if( can_move(GD_DOWN) ) m_dir = GD_DOWN;
        }

        return;
      }

      if( can_move(GD_LEFT) )
        m_xpos--;
      else
        stop_and_go();
      break;

    case GD_RIGHT:

      if( is_at_intersection() && (rand() % 10 < 2 )) {

        if( rand() & 1 ) {
          if( can_move(GD_UP) ) m_dir = GD_UP;

        } else {
          if( can_move(GD_DOWN) ) m_dir = GD_DOWN;
        }

        return;
      }

      if( can_move(GD_RIGHT) )
        m_xpos++;
      else
        stop_and_go();
      break;
  }
}

