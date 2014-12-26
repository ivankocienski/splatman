
#include <stdio.h>

#include "show-scores.hh"
#include "score-board.hh"
#include "application.hh"
#include "graphics.hh"

ShowScores::ShowScores( Application* a, Graphics* g, ScoreBoard *sb ) : ModeBase( a, g ) {
  m_score_board = sb;
}

void ShowScores::init() {
}

void ShowScores::activate() {
  m_counter = 4000;
}

void ShowScores::on_key_down( int ) {
}

void ShowScores::move() {
  if(m_counter) {
    m_counter--;
    return;
  }

  m_application->set_mode( Application::AM_SPLASH );
}

void ShowScores::draw() {

  char buffer[64];
  char date_buffer[20];

  m_graphics->draw_font_string( 0, 0, "HIGH SCORES" );

  int y = 16;
  for(int i = 0; i < 10; i++) {

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
    y += 16;
  }
}

