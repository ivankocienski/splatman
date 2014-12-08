
#include <iostream>
using namespace std;

#include <GL/gl.h>


#include "player.hh"
#include "board.hh"

static const int dir_xinc[] = { 0,  0, 0, -1, 1 };
static const int dir_yinc[] = { 0, -1, 1,  0, 0 };

Player::Player( Board *b ) {
  m_board    = b;
  m_xpos     = 14 * 16 + 8;
  m_ypos     = 23 * 16 + 8;
  m_dir      = PD_STATIONARY;
  m_want_dir = PD_STATIONARY;
  m_step     = 0;
  m_delay    = 0;
}

void Player::draw() {
  
  //if( (m_delay >> 6) & 1 ) return;

  glBegin( GL_QUADS );

  glColor3f( 1, 1, 0 );

  int cx = m_xpos;
  int cy = m_ypos;

  glVertex2f( cx - 8, cy - 8 );
  glVertex2f( cx + 8, cy - 8 );
  glVertex2f( cx + 8, cy + 8 );
  glVertex2f( cx - 8, cy + 8 );

  glEnd(); 
}

void Player::move() {

  m_delay--;
  if( m_delay ) return;

  m_delay = 30;



  if( m_dir ) {

    int xm = m_dir == PD_LEFT ? 9 : 8;
    int ym = m_dir == PD_UP   ? 9 : 8;

    int nx = m_xpos + dir_xinc[m_dir] * xm;
    int ny = m_ypos + dir_yinc[m_dir] * ym;

    if( m_board->player_can_go( nx, ny ) ) {

      m_xpos += dir_xinc[m_dir];
      m_ypos += dir_yinc[m_dir];

    } else {
//      cout << "hit wall" << endl;
      m_dir = PD_STATIONARY;
    }

    int mx = m_xpos & 15;
    int my = m_ypos & 15;

    if( mx == 8 && my == 8 ) {
      if( m_board->clear_pip( nx, ny ) ) {

      }
    }
  }



  
//  m_delay++;
//  if( m_delay & 1 ) return;
//
//  if( m_step ) {
//    m_step--;
//
//  } else {
//    m_step = 16;

  int mx = m_xpos & 15;
  int my = m_ypos & 15;

  //cout << "mx=" << mx << "  my=" << my << endl;

  if( mx == 8 && my == 8 ) {

    int xm = m_want_dir == PD_LEFT ? 9 : 8;
    int ym = m_want_dir == PD_UP   ? 9 : 8;

    int wx = m_xpos + dir_xinc[m_want_dir] * xm;
    int wy = m_ypos + dir_yinc[m_want_dir] * ym;

    //cout << "wd=" << m_want_dir << "  d=" << m_dir << endl;

    if( m_board->player_can_go( wx, wy ) ) {
      m_dir = m_want_dir;
    }

  }

}

void Player::want_move_up() {
  if(m_dir != PD_DOWN ) m_want_dir = PD_UP;
}

void Player::want_move_down() {
  if(m_dir != PD_UP ) m_want_dir = PD_DOWN;
}

void Player::want_move_left() {
  if(m_dir != PD_RIGHT ) m_want_dir = PD_LEFT;
}

void Player::want_move_right() {
  if(m_dir != PD_LEFT ) m_want_dir = PD_RIGHT;
}

