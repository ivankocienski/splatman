
#pragma once

class ScoreBoard;

#include "mode-base.hh"

class NewHighScore : public ModeBase {
private:

  ScoreBoard *m_score_board;

  char m_name[3];

  int m_name_pos;
  int m_cur_pos;
  int m_cur_mode;

  bool should_draw_char(int);
  bool should_draw_mode(int);

  enum {
    CM_CHAR,
    CM_DELETE,
    CM_OKAY,
    CM_CANCEL
  };

public:
  
  NewHighScore( Application*, Graphics*, ScoreBoard* );

  void activate();
  void on_key_down(int);
  void draw();
  void move();
};

