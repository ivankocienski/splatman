
#pragma once

#include "actor.hh"
#include "ghost.hh"

class Game;
class Graphics;
class AudioService;

class Player : public Actor {
private:

  Game *m_game;
  Graphics *m_graphics;
  AudioService *m_audio;

  int m_want_dir;
//  bool m_start;

  int m_pip_count;
  int m_lives;
  int m_score;
  int m_mode;
  int m_death_anim;
  int m_bonus_score;
  
  bool is_start();
  
public:

  enum {
    PM_START,
    PM_ALIVE,
    PM_DYING,
    PM_DEAD
  };

  Player() {}

  Player( Game*, Board*, Graphics*, AudioService* );

  void reset_for_game();
  void reset_for_retry();
  void reset_for_round();

  void draw();
  void move();
  
  void want_move_up();
  void want_move_down();
  void want_move_left();
  void want_move_right();

  int relative_dir_from( int, int );
  int relative_dir_from2( int, int, int );

  int pip_count();

  int score();
  void has_eaten_ghost( int );

  bool is_touching( Ghost& );
  void kill();
  bool is_dead();
  bool is_dying();
  int  life_count();
  bool has_score_bonused();

  void nudge_score();
};
