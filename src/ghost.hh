
#pragma once

#include "actor.hh"

class Player;
class Graphics;

class Ghost : public Actor{
private:

  enum { // ghost mode
    GM_PARKED,
    GM_WANDER,
    GM_HUNT,
    GM_SCARED,
    GM_EYES
  };

  Player *m_player;
  Graphics *m_graphics;
  
  static const int alt_ghost_dir_1[];
  static const int alt_ghost_dir_2[]; 

  int m_mode;
  int m_mode_hold;
  int m_color;
  int m_wander_time;
  
  bool behind_me(int);

  void move_parked();
  void move_wander();
  void move_hunt();
  void move_scared();
  void move_eyes();

  void set_mode(int, int);

public:

  enum {
    GC_RED,
    GC_BLUE,
    GC_PINK,
    GC_YELLOW
  };

  Ghost( Board*, Player*, Graphics*, int );
  void reset(int);

  void draw();
  void move();

  void trigger_scared(int);
  void trigger_eyes();

  bool is_scared();
  bool is_eyes();
};
