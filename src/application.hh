
#pragma once

class Graphics;
class ModeBase;

#include "mode-base.hh" 
#include "round.hh"
#include "graphics.hh"

class Application {
private:

  Graphics m_graphics;

  ModeBase *m_current_mode;

  // application modes
  Round m_round;

public:

  enum { // app modes
    AM_SPLASH,
    AM_ROUND
  };

  Application();

  void init();
  void cleanup();

  void set_mode( int );

  ModeBase *current_mode();
};

