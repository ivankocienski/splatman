
#pragma once

#include <vector>
#include <list>

#include "graphics.hh"

#include "board.hh"
#include "player.hh"
#include "ghost.hh"

class ScoreGraphic {
private:

  static const int s_step_size;
  
  Graphics &m_graphics;

  int m_count;
  int m_sprite;
  int m_xpos;
  int m_ypos;
  int m_step;

public:
  
  ScoreGraphic( Graphics&, int, int, int );

  bool is_alive();
  void draw();
  void move();
};

class Application {
private:

  Graphics m_graphics;

  Board m_board;
  Player m_player;
  
  int m_score_multiplier;
  std::list<ScoreGraphic> m_score_graphics;

  std::vector<Ghost> m_ghosts;

  int m_curx;
  int m_cury;
  bool m_okay;
  unsigned char m_pulse;

  void reset_actors();
  void eat_ghost( Ghost& );

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

  void scare_ghosts();
  void spawn_score_graphic( int, int, int );
};

