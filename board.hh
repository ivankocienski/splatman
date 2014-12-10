
#pragma once

class Board {
private:

  
  
  unsigned char *m_grid;


public:

  Board();

  void reset();

  void draw();
  bool actor_can_go( int, int );

  int clear_pip( int, int );
};

