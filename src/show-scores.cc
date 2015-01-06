
#include <stdio.h>

#include "common.hh"
#include "show-scores.hh"
#include "score-board.hh"
#include "application.hh"
#include "graphics.hh"

ShowScores::ShowScores( Application* a, Graphics* g, ScoreBoard *sb, AudioService *as ) : ModeBase( a, g, as ) {
  m_score_board = sb;
}

void ShowScores::init() {
}

void ShowScores::activate() {
  if(m_score_board->new_score_pos() != -1) {
    m_counter = 1000;

  } else
    m_counter = 500;
}

void ShowScores::on_key_down( int ) {
}

void ShowScores::move() {

  if(m_counter) {
    m_counter--;
    return;
  }

  m_score_board->clear_new_score_pos();

  m_application->set_mode( Application::AM_SPLASH );
}

void ShowScores::draw() {

  char buffer[64];
  char date_buffer[20];

  center( 8, "HIGH  SCORES" );

  int y = 48;
  for( int i = 0; i < 10; i++, y += 16 ) {

    if( m_score_board->new_score_pos() == i ) {
      if( (g_anim >> 3 ) & 1 ) continue;
    }

    m_score_board->date_at( i, date_buffer, 20 );

    snprintf(
        buffer,
        64,
        "%2d %s %s %5d",
        i + 1,
        date_buffer,
        m_score_board->name_at(i),
        m_score_board->score_at(i)
    );

    m_graphics->draw_font_string( 16, y, buffer );
  }
  
  if( (g_anim >> 5) & 1 ) 
    center( 280, "PRESS SPACEBAR TO START.");
}

