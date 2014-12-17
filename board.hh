
#pragma once

class Board {
private:
  
  unsigned char *m_grid;

  int m_pip_count;
  
public:

  Board();

  void reset();

  void draw();
  bool actor_can_go( int, int );

  int clear_pip( int, int );
  int clear_pill( int, int );
  int pip_count();
};

