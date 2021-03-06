
#include <iostream>
using namespace std;

#include <stdlib.h>

#include "actor.hh"

#include "board.hh"

const int Actor::dir_xinc[] = { 0,  0, 0, -1, 1 };
const int Actor::dir_yinc[] = { 0, -1, 1,  0, 0 };

Actor::Actor() {
  m_xpos  = 0;
  m_ypos  = 0;
  m_dir   = AD_STATIONARY;
  m_board = NULL;
  m_step_counter = 0;
  m_step  = 0;
}

bool Actor::is_at_intersection( ) {

  int mx = m_xpos & 7;
  int my = m_ypos & 7;

  return mx == 4 && my == 4;
}

bool Actor::can_move( int d ) {
  
  if( !is_at_intersection() ) return true;

  int xm = d == AD_LEFT ? 5 : 4;
  int ym = d == AD_UP   ? 5 : 4;

  int nx = m_xpos + dir_xinc[d] * xm;
  int ny = m_ypos + dir_yinc[d] * ym;

  return m_board->actor_can_go( nx, ny );
}

void Actor::setup( Board* b ) {
  m_board = b;
}

void Actor::draw() { }

void Actor::move() { }

bool Actor::step_0() {

  if( m_step ) {

    if( m_step_counter ) {
      m_step_counter--;
      return false;
    }

    m_step_counter = m_step;
  }

  return true; 
}

void Actor::set_step( int i ) {
  m_step_counter = i;
  m_step = i;
}

void Actor::move_actor( int d ) {
  m_xpos += dir_xinc[d];
  m_ypos += dir_yinc[d];

  // mid map warp points hack
  if(m_ypos == 14 * 8 + 4) {
    if( m_xpos <  -8 )    m_xpos += 30 * 8;
    if( m_xpos >= 29 * 8) m_xpos -= 29 * 8;
  }
}

int Actor::xpos() { return m_xpos; }
int Actor::ypos() { return m_ypos; }
