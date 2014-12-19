
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include <iostream>

#include "graphics.hh"
#include "round.hh"

using namespace std;

Round::Round(Application *a, Graphics *g) : ModeBase( a, g ), m_board( m_graphics ), m_player( this, &m_board, m_graphics ) {

  m_player.setup();
}

void Round::init() {

  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_RED ));
  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_YELLOW ));
  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_PINK ));
  m_ghosts.push_back( Ghost( &m_board, &m_player, m_graphics, Ghost::GC_BLUE ));

  reset_actors();
}

void Round::reset_actors() {
  
  m_score_multiplier = 2;

  m_score_graphics.clear();
  m_player.reset();

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ ) 
    it->reset();
}

void Round::move() {

  if( m_player.is_dead() ) {

    if( m_player.life_count() ) {
      reset_actors();

    } else {
      cout << "You have no lives left" << endl;
      exit(0);
    }

    return;
  }

  m_player.move();

  if( m_player.pip_count() == m_board.pip_count() ) {
    cout << "you have all the pips" << endl;
    exit(0);
  } 

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

void Round::eat_ghost( Ghost &g ) {

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
}

void Round::spawn_score_graphic( int x, int y, int n ) {
  m_score_graphics.push_front( ScoreGraphic( m_graphics, x, y, n ));
}

void Round::scare_ghosts() {

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
    it->trigger_scared();
}

void Round::draw() {

  m_graphics->draw_board( 179, 52 );

  m_graphics->draw_font_string( 179, 0, "Game score" );
  m_graphics->draw_font_number( 339, 16, m_player.score() );

  m_graphics->draw_font_string( 467, 0, "High score" );
  m_graphics->draw_font_number( 627, 16, 999999  );

  for( int i = 0; i < m_player.life_count(); i++ ) {
    m_graphics->draw_player( 179 + i * 32, 548, 4 );
  }
  
  m_board.draw();

  m_player.draw();


  if( !m_player.is_dying() ) {
    for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
      it->draw();

    for( list<ScoreGraphic>::iterator it = m_score_graphics.begin(); it != m_score_graphics.end(); it++ ) {
      it->draw();
    }
  }
}

void Round::on_key_down( int k ) {

  switch( k ) {

    case GLFW_KEY_UP:    m_player.want_move_up();    break;
    case GLFW_KEY_DOWN:  m_player.want_move_down();  break;
    case GLFW_KEY_LEFT:  m_player.want_move_left();  break;
    case GLFW_KEY_RIGHT: m_player.want_move_right(); break;

    case GLFW_KEY_T:

     for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )

       it->trigger_eyes();

     break;

    case GLFW_KEY_K:
     m_player.kill();
     break;

  }
}

/* score graphics stuff */

const int ScoreGraphic::s_step_size = 20;

bool ScoreGraphic::is_alive() {
  return m_count;
}

void ScoreGraphic::move() {

  if(m_step) {
    m_step--;
    return;
  }

  m_step = s_step_size;

  m_count--;
  m_ypos--;
}

void ScoreGraphic::draw() {
  m_graphics->draw_score( m_xpos + 179, m_ypos + 52, m_sprite );
}

ScoreGraphic::ScoreGraphic( Graphics *g, int x, int y, int n ) {

  m_graphics = g;

  m_xpos  = x;
  m_ypos  = y;
  m_count = 32;
  m_step  = s_step_size;

  switch(n) {
    case  2: m_sprite = 0; break;
    case  4: m_sprite = 1; break;
    case  8: m_sprite = 2; break;
    case 16: m_sprite = 3; break;
  }
}
