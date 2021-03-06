
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "common.hh"
#include "graphics.hh"
#include "game.hh"
#include "application.hh"
#include "score-board.hh"

using namespace std;

Game::Game(Application *a, Graphics *g, ScoreBoard *sb, AudioService *as ) : 
  ModeBase( a, g, as ), 
  m_board( m_graphics ),
  m_player( this, &m_board, m_graphics, as ),
  m_score_board(sb)
{
  m_freeze = 0;
  m_freeze_message = FM_NONE;

  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_RED ));
  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_YELLOW ));
  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_PINK ));
  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_BLUE ));
}

void Game::reset_for_game() {

  m_player.reset_for_game();
  
  m_ghost_scare_time  = 750;
  m_ghost_wander_time = 750;

  next_round();
}

void Game::reset_for_round() {
  
  m_score_multiplier = 2;

  m_freeze = 80;
  m_freeze_message = FM_READY;
  m_blink_score    = 0;

  m_score_graphics.clear();
  m_player.reset_for_retry();

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ ) 
    it->reset(m_ghost_wander_time);

  m_audio->play( 1, SP_START_LEVEL );
}

void Game::next_round() {

  m_ghost_wander_time -= 50;
  m_ghost_scare_time  -= 50;

  if( m_ghost_wander_time < 0 ) m_ghost_wander_time = 0;
  if( m_ghost_scare_time  < 0 ) m_ghost_scare_time  = 0;

  m_board.reset();
  m_player.reset_for_round();

  reset_for_round();
}

void Game::move() {

  if( m_freeze ) {
    m_freeze--;

    if(!m_freeze) {
      if( m_freeze_message == FM_GAME_OVER ) {
        
        if( m_score_board->is_on_high_scores( m_player.score() )) {

          m_score_board->push_new_score( m_player.score() );
          m_application->set_mode( Application::AM_NEW_HIGH_SCORE );

        } else
          m_application->set_mode( Application::AM_SPLASH );
      }
      m_freeze_message = FM_NONE;
    }
    return;
  }

  m_player.move();

  if( m_player.is_dead() ) {

    if( m_player.life_count() ) {

      reset_for_round();
      m_freeze = 80;
      m_freeze_message = FM_READY;

    } else {

      m_freeze = 200;
      m_freeze_message = FM_GAME_OVER;
    }

    return;
  }

  if( m_player.has_score_bonused() ) {
    m_blink_score = 400;
  }

  if( m_player.pip_count() == m_board.pip_count() ) {
    next_round();
    return;
  } 

  if( m_player.is_dying() ) return;

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ ) {
    it->move();

    if( m_player.is_touching( *it )) {

      if( it->is_scared()) {
        
        eat_ghost( *it ); 

      } else {

        if( !it->is_eyes() ) 
          m_player.kill(); 
      }
    }
  }

  for( list<ScoreGraphic>::iterator it = m_score_graphics.begin(); it != m_score_graphics.end(); ) {

    it->move();

    if( it->is_alive() ) {
      it++;

    } else {
      it = m_score_graphics.erase(it);
    }
  }

}

void Game::eat_ghost( Ghost &g ) {

  g.trigger_eyes();

  m_player.has_eaten_ghost( m_score_multiplier );

  bool any_scared = false;

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ ) {

    if( !it->is_scared() ) continue;
    any_scared = true;
    break;
  }

  if( any_scared ) {
    if( m_score_multiplier < 16 ) m_score_multiplier <<= 1;
  } else
    m_score_multiplier = 2;

  m_audio->play( 1, SP_EAT_GHOST );
}

void Game::spawn_score_graphic( int x, int y, int n ) {
  m_score_graphics.push_front( ScoreGraphic( m_graphics, x, y, n ));
}

void Game::scare_ghosts() {

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
    it->trigger_scared(m_ghost_scare_time);
}

void Game::draw() {

  m_graphics->draw_board( 0, 16 );

  m_graphics->draw_font_string( 0, 0, "Game score" );
  if(m_blink_score) {

    m_blink_score--;
    if( (m_blink_score >> 5) & 1)
      m_graphics->draw_font_number( 79, 8, m_player.score() );

  } else
    m_graphics->draw_font_number( 79, 8, m_player.score() );

  m_graphics->draw_font_string( 144, 0, "High score" );

  if( m_score_board->is_on_high_scores( m_player.score() )) {

    if( (g_anim >> 3 ) & 1 )
      m_graphics->draw_font_number( 224, 8, m_player.score() );

  } else
    m_graphics->draw_font_number( 224, 8, m_score_board->loweset_score()  );

  for( int i = 0; i < m_player.life_count(); i++ ) {
    m_graphics->draw_player( i * 16, 274, 4 );
  }
  
  m_board.draw();

  if( m_freeze ) {

    switch(m_freeze_message) {
      case FM_READY:     m_graphics->draw_font_string( 112-(6<<2),  17*8+16, "READY!"); break;
      case FM_GAME_OVER: m_graphics->draw_font_string( 112-(10<<2), 17*8+16, "GAME OVER!"); break;
    }

    return;
  } 

  m_player.draw();

  if( !m_player.is_dying() ) {
    for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
      it->draw();

    for( list<ScoreGraphic>::iterator it = m_score_graphics.begin(); it != m_score_graphics.end(); it++ ) {
      it->draw();
    }
  }

  // little hack to block out actors when they wrap
  // around on the edges of the map
  //m_graphics->draw_ghost( 627, 16 * 16 + 9, 7, 4 );
  //m_graphics->draw_ghost( 147, 16 * 16 + 9, 7, 4 );
}

void Game::on_key_down( int k ) {

  switch( k ) {

    case GLFW_KEY_UP:    m_player.want_move_up();    break;
    case GLFW_KEY_DOWN:  m_player.want_move_down();  break;
    case GLFW_KEY_LEFT:  m_player.want_move_left();  break;
    case GLFW_KEY_RIGHT: m_player.want_move_right(); break;

    case GLFW_KEY_T:

      m_player.nudge_score();
      break;

  }
}

/* score graphics stuff */

bool ScoreGraphic::is_alive() {
  return m_count;
}

void ScoreGraphic::move() {

  if(m_count) m_count--;
  m_ypos -= 2;
}

void ScoreGraphic::draw() {
  m_graphics->draw_score( m_xpos, m_ypos + 16, m_sprite );
}

ScoreGraphic::ScoreGraphic( Graphics *g, int x, int y, int n ) {

  m_graphics = g;

  m_xpos  = x;
  m_ypos  = y;
  m_count = 32;

  switch(n) {
    case  2: m_sprite = 0; break;
    case  4: m_sprite = 1; break;
    case  8: m_sprite = 2; break;
    case 16: m_sprite = 3; break;
  }
}
