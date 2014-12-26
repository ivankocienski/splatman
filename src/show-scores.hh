
#pragma once

class ScoreBoard;

#include "mode-base.hh"

class ShowScores : public ModeBase {
private:

  ScoreBoard *m_score_board;

  int m_counter;

public:

  ShowScores( Application*, Graphics*, ScoreBoard* );
  void init(); 

  void activate();
  void on_key_down( int ); 
  void move();
  void draw();
};

