
#pragma once

class Graphics;
class ModeBase;

#include "mode-base.hh" 
#include "round.hh"
#include "graphics.hh"
#include "splash-screen.hh"
#include "score-board.hh"
#include "show-scores.hh"
#include "new-high-score.hh"

class Application {
private:

  Graphics m_graphics;

  ModeBase *m_current_mode;

  // application modes
  Round m_round;
  SplashScreen m_splash_screen;
  ShowScores m_show_scores;
  NewHighScore m_new_high_score;

  ScoreBoard m_score_board;

public:

  enum { // app modes
    AM_SPLASH,
    AM_ROUND,
    AM_SHOW_SCORES,
    AM_NEW_HIGH_SCORE
  };

  Application();

  void init();
  void cleanup();

  void set_mode( int );

  ModeBase *current_mode();
};

