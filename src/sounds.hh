
#pragma once

#include "audio/audio.hh"

enum { // sound pattern identifiers
  SP_START_LEVEL,

  // player
  SP_PICKUP_PIL,
  SP_PICKUP_POWERUP,
  SP_EAT_GHOST,
  SP_DIED,
  SP_CHANGE_DIR,

  SP_NEW_SCORE_MOVE,
  SP_NEW_SCORE_SHOW
  

};

void define_sounds( AudioService& );
