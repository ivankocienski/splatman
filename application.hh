
#pragma once

#include <vector>

#include "board.hh"
#include "player.hh"
#include "ghost.hh"

class Application {
private:

  Board m_board;
  Player m_player;
  
  std::vector<Ghost> m_ghosts;

public:

  Application();

  void init();
  void cleanup();

  void draw();
  void move();

  void on_mouse_down( );
  void on_mouse_up( );
  void on_mouse_move( int, int );

  void on_key_down( int );
  void on_key_up( int );
};

