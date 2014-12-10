
#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <stdlib.h>

#include "board.hh"
#include "ghost.hh"
#include "player.hh"

const int Ghost::alt_ghost_dir_1[] = { Actor::AD_STATIONARY,  Actor::AD_LEFT, Actor::AD_RIGHT,   Actor::AD_UP, Actor::AD_DOWN };
const int Ghost::alt_ghost_dir_2[] = { Actor::AD_STATIONARY, Actor::AD_RIGHT,  Actor::AD_LEFT, Actor::AD_DOWN, Actor::AD_UP   };

float ghost_color_r[] = {   1,   1,   1, 0.5 };
float ghost_color_g[] = { 0.2,   1, 0.5, 0.5 };
float ghost_color_b[] = {   0, 0.3, 0.5,   1 };

Ghost::Ghost() : Actor() {
}

void Ghost::setup( Board *b, Player *p, int x, int y, int c ) {

  Actor::setup(b);

  set_step(10);

  m_player = p;

  m_xpos  = x * 16 + 8;
  m_ypos  = y * 16 + 8;
  m_color = c;

  switch(c) {
    case GC_RED:
      m_mode_hold = 0;
      m_mode = GM_WANDER;
      break;

    case GC_YELLOW:
      set_step(20);
      m_mode_hold = 300;
      m_mode = GM_PARKED;
      m_dir  = AD_UP;
      break;

    case GC_PINK:
      set_step(20);
      m_mode_hold = 0;
      m_mode = GM_PARKED;
      m_dir  = AD_UP;
      break;

    case GC_BLUE:
      set_step(20);
      m_mode_hold = 700;
      m_dir  = AD_DOWN;
      break;
  }

}

void Ghost::draw() {

  if(!m_board) return;

  glBegin( GL_QUADS );

  glColor3f( ghost_color_r[m_color], ghost_color_g[m_color], ghost_color_b[m_color] );

  int cx = m_xpos;
  int cy = m_ypos;

  glVertex2f( cx - 8, cy - 8 );
  glVertex2f( cx + 8, cy - 8 );
  glVertex2f( cx + 8, cy + 8 );
  glVertex2f( cx - 8, cy + 8 );

  glEnd(); 
}

// when in the little cell
void Ghost::move_parked() {
  
  if( m_mode_hold ) {
    m_mode_hold--;

    if( can_move( m_dir )) 
      move_actor( m_dir );
    else
      m_dir = m_dir == AD_UP ? AD_DOWN : AD_UP;

    return;
  }

  if( !is_at_intersection() ) {
    move_actor(m_dir);
    return;
  }

  switch( m_xpos ) {

    case 12 * 16 + 8: 
      m_dir = AD_RIGHT;
      break;

    case 14 * 16 + 8: 
      if( m_ypos == 12 * 16 + 8 ) {
        set_step(10);
        m_mode_hold = 200;
        m_mode = GM_WANDER;
        return;
      }
      m_dir = AD_UP;
      break;

    case 16 * 16 + 8: 
      m_dir = AD_LEFT;
      break;
  }

  move_actor(m_dir);
}

void Ghost::move_wander() {

  if( m_mode_hold ) {
    m_mode_hold--;

  } else {

    cout << "go hunt" << endl;
    m_mode = GM_HUNT;
    return;
  }

  if( m_dir == AD_STATIONARY ) {

    while( m_dir == AD_STATIONARY ) {

      int nd = 1 + rand() % 4;

      if( can_move(nd) ) {
        m_dir = nd;
      }

    }
    return;
  }

  if( is_at_intersection() && (rand() % 10 < 2 )) {

    if( rand() & 1 ) {
      if( can_move( alt_ghost_dir_1[m_dir] )) m_dir = alt_ghost_dir_1[m_dir];

    } else {
      if( can_move( alt_ghost_dir_2[m_dir] )) m_dir = alt_ghost_dir_2[m_dir];
    }
  }

  if( can_move(m_dir) )
    move_actor(m_dir);
  else
    m_dir = AD_STATIONARY;

}

bool Ghost::behind_me( int d ) {

  if( d == AD_STATIONARY ) return true;
  
  if( m_dir == AD_UP    && d == AD_DOWN  ) return true;
  if( m_dir == AD_DOWN  && d == AD_UP    ) return true;

  if( m_dir == AD_LEFT  && d == AD_RIGHT ) return true;
  if( m_dir == AD_RIGHT && d == AD_LEFT  ) return true;

  return false;
}

void Ghost::move_hunt() {

  if( !is_at_intersection() ) {
    move_actor(m_dir);
    return;
  }

  // do we have line of sight to player?
  int a_dir = m_player->relative_dir_from( m_xpos, m_ypos );
  if( can_move( a_dir ) && !behind_me( a_dir )) {
    
    cout << "hunt: target" << endl;

    m_dir = a_dir;
    move_actor( m_dir );
    return;

  } 

  // can we move around the obstacle between us?
  int b_dir = m_player->relative_dir_from2( a_dir, m_xpos, m_ypos );
  if( can_move( b_dir ) && !behind_me( b_dir )) {
    
    cout << "hunt: target2" << endl;

    m_dir = b_dir;
    move_actor( m_dir );
    return;

  } 

  // no, fallback to meandering around then...
  
  cout << "go wander" << endl;

  m_mode = GM_WANDER;
  m_mode_hold = 100 + rand() % 400;
}

void Ghost::move_scared() {

  move_wander();
}

void Ghost::move_eyes() {

}

void Ghost::move() {

  if( !m_board ) return;

  if( !step_0() ) return;

  switch( m_mode ) {
    case GM_PARKED:
      move_parked();
      break;

    case GM_WANDER:
      move_wander();
      break;

    case GM_HUNT:
      move_hunt();
      break;

    case GM_SCARED:
      //move_scared();
      move_wander();
      break;

    case GM_EYES:
      move_eyes();
      break;
  }

}

