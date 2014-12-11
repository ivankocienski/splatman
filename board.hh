
#pragma once

class Board {
private:
  
  unsigned char *m_grid;

  unsigned char read_grid( int, int );
  
public:

  Board();

  void reset();

  void draw();
  bool actor_can_go( int, int );

  int clear_pip( int, int );
  int clear_pill( int, int );
};

