
#include <iostream>
using namespace std;

#include <cstring>
#include <GLFW/glfw3.h>

#include "new-high-score.hh"

#include "application.hh"
#include "graphics.hh"
#include "score-board.hh"

const static char char_palette[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
  'U', 'V', 'W', 'X', 'Y', 'Z', '!', '0', '1', '2', 
  '3', '4', '5', '6', '7', '8', '9'
};

NewHighScore::NewHighScore( Application* a, Graphics* g, ScoreBoard* sb ) : ModeBase( a, g ) {
  m_score_board = sb; 
}

void NewHighScore::activate() {
  memset( m_name, 0, sizeof(m_name));
  m_cur_pos  = 0;
  m_name_pos = 0;
  m_cur_mode = CM_CHAR;
}

void NewHighScore::on_key_down(int k) {

  switch(m_cur_mode) {

    case CM_CHAR:

      // very hacky ...

      switch(k) {
        case GLFW_KEY_LEFT:
          m_cur_pos--; 
          if(m_cur_pos < 0) m_cur_pos = 36;
          break;

        case GLFW_KEY_RIGHT: 
          m_cur_pos++;
          if(m_cur_pos > 36) m_cur_pos = 0;
          break;

        case GLFW_KEY_UP:   
          m_cur_pos -= 10; 
          if(m_cur_pos < 0) {
            m_cur_mode = CM_CANCEL;
            m_cur_pos += 40;
          }
          
          if(m_cur_pos > 36) m_cur_pos -= 10;
          break;

        case GLFW_KEY_DOWN:  
          m_cur_pos += 10; 
          if(m_cur_pos > 36) {
            m_cur_mode = CM_DELETE;
            m_cur_pos -= 40;
          }
          if(m_cur_pos <  0) m_cur_pos += 10;
          break; 
      } 

      break;

    case CM_DELETE:
      if( k == GLFW_KEY_UP   ) m_cur_mode = CM_CHAR;
      if( k == GLFW_KEY_DOWN ) m_cur_mode = CM_OKAY;
      break;

    case CM_OKAY:
      if( k == GLFW_KEY_UP   ) m_cur_mode = CM_DELETE;
      if( k == GLFW_KEY_DOWN ) m_cur_mode = CM_CANCEL;
      break;

    case CM_CANCEL:
      if( k == GLFW_KEY_UP   ) m_cur_mode = CM_OKAY;
      if( k == GLFW_KEY_DOWN ) m_cur_mode = CM_CHAR;
      break; 
  } 
}

void NewHighScore::draw() {

  char ch[2];

  m_graphics->draw_font_string( 0, 0, "ENTER NAME" );

  int x = 0;
  int y = 0;

  ch[1] = 0;

  for( int i = 0; i < 37; i++ ) {

    ch[0] = char_palette[i];

    if( should_draw_char(i) ) 
      m_graphics->draw_font_string( x * 32 + 32, y * 32 + 64, ch );

    x++;
    if( x > 9 ) {
      x = 0;
      y++;
    }
  }

  x = 64;
  y++;
  
  if( should_draw_mode(CM_DELETE) ) 
    m_graphics->draw_font_string( x, y * 32 + 64, "DELETE" );

  y++;
  if( should_draw_mode(CM_OKAY) )
    m_graphics->draw_font_string( x, y * 32 + 64, "OKAY" );

  y++;
  if( should_draw_mode(CM_CANCEL) )
    m_graphics->draw_font_string( x, y * 32 + 64, "CANCEL" );

  y += 2;
  x = 2;
  m_graphics->draw_font_string( x * 16 + 32, y * 32 + 64, m_name );

  if((m_anim_count >> 7 ) & 1) {
    m_graphics->draw_font_string( (x + m_name_pos) * 16 + 32, y * 32 + 64, "#" );
  }
}

void NewHighScore::move() {
  m_anim_count++;
}

bool NewHighScore::should_draw_char( int t ) {
  if( m_cur_mode != CM_CHAR ) return true;

  if( m_cur_pos != t ) return true;

  return (m_anim_count >> 7 ) & 1;
}

bool NewHighScore::should_draw_mode( int t ) {
  if( m_cur_mode != t ) return true;

  return (m_anim_count >> 7 ) & 1;
}

