
#include <iostream>
using namespace std;

#include <cstring>
#include <GLFW/glfw3.h>

#include "common.hh"
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

NewHighScore::NewHighScore( Application* a, Graphics* g, ScoreBoard* sb, AudioService* as ) : ModeBase( a, g, as ) {
  m_score_board = sb; 
}

void NewHighScore::activate() {
  memset( m_name, 0, sizeof(m_name));
  m_cur_pos  = 0;
  m_name_pos = 0;
  m_cur_mode = CM_CHAR;

  m_audio->play( 1, SP_NEW_SCORE_SHOW );
}

void NewHighScore::on_key_down(int k) {

  if( k == GLFW_KEY_SPACE ) {

    switch(m_cur_mode) {
      case CM_CHAR:
        m_name[m_name_pos] = char_palette[m_cur_pos];
        if(m_name_pos < 2) 
          m_name_pos++;
        else
          m_cur_mode = CM_OKAY;

        m_audio->play( 0, SP_NEW_SCORE_ENTER );
        break;

      case CM_DELETE:
        if(m_name_pos == 2) {
          if(m_name[2])
            m_name[2] = 0;
          else {
            m_name_pos--; 
            m_name[m_name_pos] = 0;
          }

        } else {
          if(m_name_pos) m_name_pos--;
          m_name[m_name_pos] = 0;
        }
        m_audio->play( 0, SP_NEW_SCORE_DELETE );
        break;

      case CM_OKAY:
        m_score_board->set_new_name(m_name);
        m_score_board->save();
        m_application->set_mode(Application::AM_SHOW_SCORES);
        break;

      case CM_CANCEL:
        m_application->set_mode(Application::AM_SPLASH);
        break;
    }
    return;
  }

  switch(m_cur_mode) {

    case CM_CHAR:

      // very hacky ...

      switch(k) {
        case GLFW_KEY_LEFT:
          m_cur_pos--; 
          if(m_cur_pos < 0) m_cur_pos = 36;
          m_audio->play( 0, SP_NEW_SCORE_MOVE );
          break;

        case GLFW_KEY_RIGHT: 
          m_cur_pos++;
          if(m_cur_pos > 36) m_cur_pos = 0;
          m_audio->play( 0, SP_NEW_SCORE_MOVE );
          break;

        case GLFW_KEY_UP:   
          m_cur_pos -= 10; 
          if(m_cur_pos < 0) {
            m_cur_mode = CM_CANCEL;
            m_cur_pos += 40;
          }
          
          if(m_cur_pos > 36) m_cur_pos -= 10;
          m_audio->play( 0, SP_NEW_SCORE_MOVE );
          break;

        case GLFW_KEY_DOWN:  
          m_cur_pos += 10; 
          if(m_cur_pos > 36) {
            m_cur_mode = CM_DELETE;
            m_cur_pos -= 40;
          }
          if(m_cur_pos <  0) m_cur_pos += 10;
          m_audio->play( 0, SP_NEW_SCORE_MOVE );
          break; 
      } 

      break;

    case CM_DELETE:
      if( k == GLFW_KEY_UP   ) m_cur_mode = CM_CHAR;
      if( k == GLFW_KEY_DOWN ) m_cur_mode = CM_OKAY;
      m_audio->play( 0, SP_NEW_SCORE_MOVE );
      break;

    case CM_OKAY:
      if( k == GLFW_KEY_UP   ) m_cur_mode = CM_DELETE;
      if( k == GLFW_KEY_DOWN ) m_cur_mode = CM_CANCEL;
      m_audio->play( 0, SP_NEW_SCORE_MOVE );
      break;

    case CM_CANCEL:
      if( k == GLFW_KEY_UP   ) m_cur_mode = CM_OKAY;
      if( k == GLFW_KEY_DOWN ) m_cur_mode = CM_CHAR;
      m_audio->play( 0, SP_NEW_SCORE_MOVE );
      break; 
  } 
}

void NewHighScore::draw() {

  // this may be a bit ugly

  char ch[2];

  m_graphics->draw_font_string( 0, 8, "ENTER NAME" );

  m_graphics->draw_font_string( 0, 40, "---" );
  m_graphics->draw_font_string( 0, 32, m_name );

  if((g_anim >> 5 ) & 1) {
    m_graphics->draw_font_string( m_name_pos * 8, 32, "#" );
  }

  int x = 0;
  int y = 4;

  ch[1] = 0;

  for( int i = 0; i < 37; i++ ) {

    ch[0] = char_palette[i];

    if( should_draw_char(i) ) 
      m_graphics->draw_font_string( x * 16, y * 16, ch );

    x++;
    if( x > 9 ) {
      x = 0;
      y++;
    }
  }

  y += 2;
  
  if( should_draw_mode(CM_DELETE) ) 
    m_graphics->draw_font_string( 0, y * 16, "DELETE" );

  y++;
  if( should_draw_mode(CM_OKAY) )
    m_graphics->draw_font_string( 0, y * 16, "OKAY" );

  y++;
  if( should_draw_mode(CM_CANCEL) )
    m_graphics->draw_font_string( 0, y * 16, "CANCEL" );
}

void NewHighScore::move() { }

bool NewHighScore::should_draw_char( int t ) {
  if( m_cur_mode != CM_CHAR ) return true;

  if( m_cur_pos != t ) return true;

  return (g_anim >> 5 ) & 1;
}

bool NewHighScore::should_draw_mode( int t ) {
  if( m_cur_mode != t ) return true;

  return (g_anim >> 5 ) & 1;
}

