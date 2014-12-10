
#pragma once

#include "actor.hh"

class Player : public Actor {
private:

  int m_want_dir;

  int m_step;
  unsigned char m_delay;

public:

  Player( Board* );

  void setup();
  void draw();
  void move();

  void want_move_up();
  void want_move_down();
  void want_move_left();
  void want_move_right();

  int relative_dir_from( int, int );
  int relative_dir_from2( int, int, int );
};
