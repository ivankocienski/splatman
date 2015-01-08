
#pragma once

#include <list>
#include <string>

class ScoreBoard;
class AudioService;

#include "mode-base.hh"

class ScoreEntry {
private:

  ScoreBoard *m_score_board;

  std::string m_text;

  int  m_position;
  bool m_blink;
  int  m_ypos;

public:

  ScoreEntry( int, ScoreBoard* );

  void reload(int);
  void draw(Graphics*);
};

class ShowScores : public ModeBase {
private:

  std::list<ScoreEntry> m_score_entries;

  ScoreBoard *m_score_board;

  int m_counter;
  
public:

  ShowScores( Application*, Graphics*, ScoreBoard*, AudioService* );

  void activate();
  void on_key_down( int ); 
  void move();
  void draw();
};

