
#pragma once

class Board;

class Player {
private:

  enum { // player dir
    PD_STATIONARY,
    PD_UP,
    PD_DOWN,
    PD_LEFT,
    PD_RIGHT
  };

  Board *m_board;

  int m_xpos;
  int m_ypos;
  
  int m_dir;
  int m_want_dir;

  int m_step;
  unsigned char m_delay;

public:

  Player( Board* );


  void draw();
  void move();

  void want_move_up();
  void want_move_down();
  void want_move_left();
  void want_move_right();
};
