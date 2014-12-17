
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
      set_mode( GM_WANDER, 0);
      break;

    case GC_YELLOW:
      set_step(20);
      set_mode(GM_PARKED, 300);
      m_dir  = AD_UP;
      break;

    case GC_PINK:
      set_step(20);
      set_mode(GM_PARKED, 0);
      m_dir  = AD_UP;
      break;

    case GC_BLUE:
      set_step(20);
      set_mode(GM_PARKED, 700);
      break;
  }

}

void Ghost::draw() {

  if(!m_board) return;

  glBegin( GL_QUADS );

  if( m_mode == GM_SCARED ) {

    float v = 0;

    if(m_mode_hold < 200 && (m_mode_hold >> 4) & 1) {
      v = 1;
    } 

    glColor3f( v, v, 1 );

  } else
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
        set_mode(GM_WANDER, 200);
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

    if( m_mode == GM_SCARED ) 
      set_mode(GM_WANDER, 200);

    else 
      set_mode(GM_HUNT, 0);

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

  set_mode(GM_WANDER, 100 + rand() % 400);
}

void Ghost::move_scared() {

  move_wander();
}

void Ghost::move_eyes() {

  if( !is_at_intersection() ) {
    move_actor(m_dir);
    return;
  }

  cout << "x=" << m_xpos << "  y=" << m_ypos << endl;

  if( m_xpos == 232 ) {
//    cout << "xxx" << endl;
    if( m_ypos == 200 ) {
//      cout << "yyy" << endl;
      m_dir = AD_DOWN;
      move_actor( m_dir );
      return;
    }

    if( m_ypos == 232 ) {
      set_mode(GM_PARKED, 0);
      m_dir = AD_UP;
      return;
    }
      
  }

  int i = 0;

  if( can_move( AD_UP    )) i++;
  if( can_move( AD_DOWN  )) i++;
  if( can_move( AD_LEFT  )) i++;
  if( can_move( AD_RIGHT )) i++;

  cout << "i=" << i << endl;

  if( i < 3 ) {
    if(can_move( m_dir )) {
      move_actor( m_dir );
      return;
    }
  }

  cout << "eyes: target" << endl;



  if( m_ypos < 176 || m_ypos > 272 ) {

    if( m_ypos > 192 ) {
      if( can_move( AD_UP )) {
        m_dir = AD_UP;
        move_actor(m_dir);
        return;
      }

    } else {
      if( can_move( AD_DOWN )) {
        m_dir = AD_DOWN;
        move_actor(m_dir);
        return;
      }
    }

    if( m_dir == AD_UP || m_dir == AD_DOWN ) {

      if( m_xpos > 224 ) {
        if( can_move( AD_LEFT ))  m_dir = AD_LEFT;  else m_dir = AD_RIGHT;

      } else {
        if( can_move( AD_RIGHT )) m_dir = AD_RIGHT; else m_dir = AD_LEFT;

      }
    }

    move_actor(m_dir);
    return; 
  }



  if( m_xpos > 224 ) {
    if( can_move( AD_LEFT )) {
      m_dir = AD_LEFT;
      move_actor(m_dir);
      return;
    }

  } else {
    if( can_move( AD_RIGHT )) {
      m_dir = AD_RIGHT;
      move_actor(m_dir);
      return;
    }
  }

  if( m_ypos > 192 ) {
    if( can_move( AD_UP  ))  m_dir = AD_UP;  else m_dir = AD_DOWN;

  } else {
    if( can_move( AD_DOWN )) m_dir = AD_DOWN; else m_dir = AD_UP;

  }

  move_actor(m_dir);
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
      move_scared();
      break;

    case GM_EYES:
      move_eyes();
      break;
  }

}

static const char* names[] = { "parked", "wander", "hunt", "scared", "eyes" };
static const char* colors[] = { "red", "yellow", "pink", "blue" };

void Ghost::set_mode( int m, int h ) {
  m_mode = m;
  m_mode_hold = h;

  cout << colors[m_color] << " set_mode " << names[m_mode] << endl;

  switch(m) { 
    case GM_PARKED:
    case GM_WANDER:
    case GM_HUNT:
      set_step(10);
      break;

    case GM_SCARED:
      set_step(25);
      break;

    case GM_EYES:
      set_step(5);
      break;
  }
}

void Ghost::trigger_scared() {
  set_mode(GM_SCARED, 1000);
}

void Ghost::trigger_eyes() {
  set_mode(GM_EYES, 0);
}

bool Ghost::is_scared() {
  return m_mode == GM_SCARED;
}

bool Ghost::is_eyes() {
  return m_mode == GM_EYES;
}
