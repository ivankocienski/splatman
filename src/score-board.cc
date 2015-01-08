
#include <iostream>
using namespace std;

#include <cstdio>
#include <cstring>
#include <time.h>

#include "score-board.hh"

const char* ScoreBoard::c_score_file = "scores.bin";

ScoreBoard::ScoreBoard() {
  m_new_position = -1;
  reset();
}

void ScoreBoard::reset() {

  m_new_position = -1;

  for( int i = 0; i < 10; i++ ) {
    m_scores[i].score = (10 - i) * 8500;
    m_scores[i].day   = 1;
    m_scores[i].month = 1;
    m_scores[i].year  = 1980;
    m_scores[i].name[0] = 'A' + i;
    m_scores[i].name[1] = 'A' + i;
    m_scores[i].name[2] = 'A' + i;
  }
}

void ScoreBoard::load() {

  FILE *file = fopen( c_score_file, "rb" );
  if(!file) return;

  fread( m_scores, sizeof(T_SCORE), 10, file );

  fclose(file);
}

void ScoreBoard::save() {

  FILE *file = fopen( c_score_file, "wc" );
  if(!file) return;

  fwrite( m_scores, 10, sizeof(T_SCORE), file );

  fclose(file);
}

string ScoreBoard::name_at(int i) {
  return string(m_scores[i].name, 3);
}

int ScoreBoard::score_at(int i) {
  return m_scores[i].score; 
}

void ScoreBoard::date_at( int i, char *buffer, int buflen ) { 
  snprintf( buffer, buflen, "%02d-%02d-%4d", m_scores[i].day, m_scores[i].month, m_scores[i].year );
}

bool ScoreBoard::is_on_high_scores(int s) {
  return s >= m_scores[9].score;
}

int ScoreBoard::loweset_score() {
  return m_scores[9].score;
}

void ScoreBoard::push_new_score( int ns ) {

  if( !is_on_high_scores(ns) ) return;

  m_new_position = 0;

  while( m_new_position < 9 ) {

    if( ns >= m_scores[m_new_position].score ) break;

    m_new_position++; 
  }

  for( int i = 8; i >= m_new_position; i-- ) {
    m_scores[i + 1] = m_scores[i];
  }

  time_t tm; 
  time(&tm); 
  struct tm * date = gmtime(&tm);

  m_scores[m_new_position].score = ns;
  m_scores[m_new_position].day   = date->tm_mday;
  m_scores[m_new_position].month = date->tm_mon;
  m_scores[m_new_position].year  = date->tm_year + 1900;
}

void ScoreBoard::set_new_name( char * nn ) {

  if(m_new_position == -1) return;

  m_scores[m_new_position].name[0] = nn[0];
  m_scores[m_new_position].name[1] = nn[1];
  m_scores[m_new_position].name[2] = nn[2];
}

int ScoreBoard::new_score_pos() {
  return m_new_position;
}

void ScoreBoard::clear_new_score_pos() {
  m_new_position = -1;
}

