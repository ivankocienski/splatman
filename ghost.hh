
#pragma once

#include "actor.hh"

class Player;

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

  static const int alt_ghost_dir_1[];
  static const int alt_ghost_dir_2[]; 

  int m_mode;
  int m_mode_hold;
  int m_color;

  bool behind_me(int);

  void move_parked();
  void move_wander();
  void move_hunt();
  void move_scared();
  void move_eyes();

public:

  enum {
    GC_RED,
    GC_YELLOW,
    GC_PINK,
    GC_BLUE
  };

  Ghost();
  void setup( Board*, Player*, int, int, int );

  void draw();
  void move();
};
