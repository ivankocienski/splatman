
#pragma once

#include "board.hh"

class Application {
private:

  Board m_board;

public:

  Application();

  void init();
  void cleanup();

  void draw();

  void on_mouse_down( );
  void on_mouse_up( );
  void on_mouse_move( int, int );
};

