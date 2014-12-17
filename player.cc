
#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <stdlib.h>


#include "player.hh"
#include "board.hh"
#include "application.hh"

static const int anim_sprites[] = {
  0, 0, 0, 0, // stationary
  0, 7, 8, 7, // up
  0, 5, 6, 5, // down
  0, 3, 4, 3, // left
  0, 1, 2, 1  // right
};


Player::Player( Application *a, Board *b, Graphics *g ) : Actor() {

  Actor::setup(b);

  m_graphics    = g;
  m_application = a;
  
  m_want_dir = AD_STATIONARY;
  m_delay    = 0;
}

void Player::setup() {

  reset();

  m_pip_count = 0;
  m_lives = 3;

  set_step( 10 );
}

void Player::reset() {
  m_xpos = 14 * 16 + 8;
  m_ypos = 23 * 16 + 8;
}

void Player::draw() {
  
  int offset = 0;

  switch( m_dir ) {
    case AD_UP:
    case AD_DOWN:
      offset = (m_ypos >> 3) & 3;
      break;

    case AD_LEFT:
    case AD_RIGHT:
      offset = (m_xpos >> 3) & 3;
      break;
  }



  
  m_graphics->draw_player( m_xpos - 16, m_ypos - 16, anim_sprites[ (m_dir << 2) + offset ]);

//  int cx = m_xpos;
//  int cy = m_ypos;
//
//  glVertex2f( cx - 8, cy - 8 );
//  glVertex2f( cx + 8, cy - 8 );
//  glVertex2f( cx + 8, cy + 8 );
//  glVertex2f( cx - 8, cy + 8 );
//
//  glEnd(); 
}

void Player::move() {

  if( !step_0() ) return;

  if( m_dir ) {

    if( can_move( m_dir )) {
      move_actor( m_dir );

    } else {
      m_dir = AD_STATIONARY;
    }

    if( is_at_intersection() ) {
      if( m_board->clear_pip( m_xpos, m_ypos ) ) {
        m_pip_count++;
        cout << "player: pip_count=" << m_pip_count << endl;
      }

      if( m_board->clear_pill( m_xpos, m_ypos )) {
        m_application->scare_ghosts();
      }
    }
  }

  if( is_at_intersection() && can_move( m_want_dir ))
    m_dir = m_want_dir;
  
}

void Player::want_move_up() {
  if(m_dir != AD_DOWN ) m_want_dir = AD_UP;
}

void Player::want_move_down() {
  if(m_dir != AD_UP ) m_want_dir = AD_DOWN;
}

void Player::want_move_left() {
  if(m_dir != AD_RIGHT ) m_want_dir = AD_LEFT;
}

void Player::want_move_right() {
  if(m_dir != AD_LEFT ) m_want_dir = AD_RIGHT;
}

int Player::pip_count() {
  return m_pip_count;
}

bool Player::is_touching( Ghost &g ) {
  
  int dx = abs(m_xpos - g.xpos());
  int dy = abs(m_ypos - g.ypos());

  return dx < 8 && dy < 8;
}

int Player::relative_dir_from( int px, int py ) {

  // return which direction would take (px,py) to get to player

  px -= m_xpos;
  py -= m_ypos;

  if(!px && !py) return AD_STATIONARY;

  if(!px) return py < 0 ? AD_DOWN  : AD_UP;
  if(!py) return px < 0 ? AD_RIGHT : AD_LEFT;

  int dx = abs(px);
  int dy = abs(py);

  if(py < 0) {

    if(py < -dx) return AD_DOWN;

  } else {

    if(py >= dx) return AD_UP;
  }

  if(px < 0) {

    if(px < -dy) return AD_RIGHT;

  } else {

    if(px >= dy) return AD_LEFT; 
  }

  return AD_STATIONARY;
}

int Player::relative_dir_from2( int d, int x, int y ) {

  // return approximate direction

  switch(d) {

    case AD_UP:
    case AD_DOWN:
      return x < m_xpos ? AD_RIGHT : AD_LEFT;

      
    case AD_LEFT:
    case AD_RIGHT:
      return y < m_ypos ? AD_DOWN : AD_UP;

      break;
  }

  return AD_STATIONARY;
}

void Player::decrement_lives() {
  m_lives--;
}

int Player::life_count() {
  return m_lives;
}

#if 0


  int dx = abs( m_xpos - px);
  int dy = abs( m_ypos - py);

  if( dx == 0 ) {
    if( m_ypos < py ) return AD_UP;
    if( m_ypos > py ) return AD_DOWN;
  }

  if( dy == 0 ) {
    if( m_xpos < px ) return AD_RIGHT;
    if( m_xpos > px ) return AD_LEFT;
  }

  if( dx > dy ) {
    if( m_xpos < px ) return AD_RIGHT;
    if( m_xpos > px ) return AD_LEFT;
  }

  if( m_ypos < py ) return AD_UP;
  if( m_ypos > py ) return AD_DOWN;

  return AD_STATIONARY;
#endif

