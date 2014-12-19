
#pragma once

#include "actor.hh"
#include "ghost.hh"

class Round;
class Graphics;

class Player : public Actor {
private:

  Round *m_round;
  Graphics *m_graphics;

  int m_want_dir;
//  bool m_start;

  int m_pip_count;
  int m_lives;
  int m_score;
  int m_mode;
  int m_death_anim;

  bool is_start();
  
public:

  enum {
    PM_START,
    PM_ALIVE,
    PM_DYING,
    PM_DEAD
  };

  Player( Round*, Board*, Graphics* );

  void setup();
  void reset();

  void draw();
  void move();
  //int  mode();
  
  void want_move_up();
  void want_move_down();
  void want_move_left();
  void want_move_right();

  int relative_dir_from( int, int );
  int relative_dir_from2( int, int, int );

  int pip_count();

  int score();
  void has_eaten_ghost( int );

  bool is_touching( Ghost& );
  void kill();
  bool is_dead();
  bool is_dying();
  int  life_count();
};
