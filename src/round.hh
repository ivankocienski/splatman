
#pragma once

#include <vector>
#include <list>

class ScoreBoard;

#include "mode-base.hh"

#include "board.hh"
#include "player.hh"
#include "ghost.hh"

class ScoreGraphic {
private:

  static const int s_step_size;
  
  Graphics *m_graphics;
  
  int m_count;
  int m_sprite;
  int m_xpos;
  int m_ypos;
  int m_step;

public:
  
  ScoreGraphic( Graphics*, int, int, int );

  bool is_alive();
  void draw();
  void move();
};

class Round : public ModeBase {
public:

  Round(Application*, Graphics*, ScoreBoard*);

  void set_round_number(int);
  void activate();

  void init();
  void cleanup();

  void draw();
  void move();

  void on_key_down( int );

  void scare_ghosts();
  void spawn_score_graphic( int, int, int ); 

private:

  enum { // freeze message
    FM_NONE,
    FM_READY,
    FM_GAME_OVER
  };

  Board m_board;
  Player m_player;
  
  int m_score_multiplier;
  std::list<ScoreGraphic> m_score_graphics;

  std::vector<Ghost> m_ghosts;

  ScoreBoard *m_score_board;

  int m_freeze;
  int m_freeze_message;
  int m_blink_score;

  int m_ghost_wander_time;
  int m_ghost_scare_time;

  void reset_actors();
  void next_round();
  void eat_ghost( Ghost& );
};

