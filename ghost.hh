
#pragma once

class Board;

class Ghost {
private:

  enum { // ghost dir
    GD_STATIONARY,
    GD_UP,
    GD_DOWN,
    GD_LEFT,
    GD_RIGHT
  };

  int m_xpos;
  int m_ypos;

  int m_dir;
  int m_hold;

  Board *m_board;

  bool is_at_intersection();
  bool can_move(int);
  void stop_and_go();

public:

  Ghost();
  void setup( Board*, int, int );

  void draw();
  void move();
};
