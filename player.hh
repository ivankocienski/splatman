
#pragma once

#include "actor.hh"
#include "ghost.hh"

class Application;
class Graphics;

class Player : public Actor {
private:

  Application *m_application;
  Graphics *m_graphics;

  int m_want_dir;

  int m_step;
  unsigned char m_delay;

  int m_pip_count;
  int m_lives;
  
public:

  Player( Application*, Board*, Graphics* );

  void setup();
  void reset();

  void draw();
  void move();

  void want_move_up();
  void want_move_down();
  void want_move_left();
  void want_move_right();

  int relative_dir_from( int, int );
  int relative_dir_from2( int, int, int );

  int pip_count();

  bool is_touching( Ghost& );

  void decrement_lives();
  int life_count();
};
