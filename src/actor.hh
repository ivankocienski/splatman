
#pragma once

class Board;

class Actor {
protected:

  static const int dir_xinc[];
  static const int dir_yinc[];

  enum { // actor dir
    AD_STATIONARY,
    AD_UP,
    AD_DOWN,
    AD_LEFT,
    AD_RIGHT
  };

  int m_xpos;
  int m_ypos;

  int m_dir;
  int m_step_counter;
  int m_step;

  Board *m_board;

  bool is_at_intersection();
  bool can_move(int);
  void move_actor(int);
  bool step_0();

  void set_step(int);

public:

  Actor();

  virtual void setup( Board* );

  virtual void draw();
  virtual void move();

  int xpos();
  int ypos();
};

