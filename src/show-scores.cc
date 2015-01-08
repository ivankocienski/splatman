
#include <stdio.h>

#include "common.hh"
#include "show-scores.hh"
#include "score-board.hh"
#include "application.hh"
#include "graphics.hh"
#include "sounds.hh"

#include <iostream>
using namespace std;

// score entry class
// =================

ScoreEntry::ScoreEntry( int pos, ScoreBoard* sb ) {
  m_position    = pos;
  m_score_board = sb;
  m_blink       = false;
  m_ypos        = 48 + pos * 16;
}

void ScoreEntry::reload( int hilight_pos ) {

  char buffer[25];
  char date_buffer[12];

  memset(buffer, 0, sizeof(buffer));
  memset(date_buffer, 0, sizeof(date_buffer));

  m_score_board->date_at( m_position, date_buffer, 12 );

  snprintf(
    buffer,
    25,
    "%2d %s %3s %6d",
    m_position + 1,
    date_buffer,
    m_score_board->name_at(m_position).c_str(),
    m_score_board->score_at(m_position)
  );

  m_text  = buffer;
  m_blink = (hilight_pos == m_position);
}

void ScoreEntry::draw( Graphics *g ) {

  if( m_blink && (g_anim >> 3 ) & 1 ) return;

  g->draw_font_string( 16, m_ypos, m_text.c_str() );
}

// show scores class
// =================

ShowScores::ShowScores( Application* a, Graphics* g, ScoreBoard *sb, AudioService *as ) : ModeBase( a, g, as ) {
  m_score_board = sb;

  for( int i = 0; i < 10; i++ )
    m_score_entries.push_back( ScoreEntry( i, sb ));
}

void ShowScores::activate() {

  for( list<ScoreEntry>::iterator it = m_score_entries.begin(); it != m_score_entries.end(); it++ ) 
    it->reload(m_score_board->new_score_pos());

  if(m_score_board->new_score_pos() != -1) {
    m_counter = 1000;

  } else
    m_counter = 500;

  m_score_board->clear_new_score_pos();
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

  center( 8, "HIGH  SCORES" );

  for( list<ScoreEntry>::iterator it = m_score_entries.begin(); it != m_score_entries.end(); it++ ) 
    it->draw( m_graphics );
  
  if( (g_anim >> 5) & 1 ) 
    center( 280, "PRESS SPACEBAR TO START.");
}

