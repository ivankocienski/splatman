
#pragma once

class Graphics;
class ModeBase;

#include "mode-base.hh" 
#include "game.hh"
#include "graphics.hh"
#include "splash-screen.hh"
#include "score-board.hh"
#include "show-scores.hh"
#include "new-high-score.hh"
#include "audio/audio.hh"

class Application {
private:

  Graphics m_graphics;

  ModeBase *m_current_mode;

  // application modes
  Game m_game;
  SplashScreen m_splash_screen;
  ShowScores m_show_scores;
  NewHighScore m_new_high_score;

  ScoreBoard m_score_board;

  AudioService m_audio;

public:

  enum { // app modes
    AM_SPLASH,
    AM_NEW_GAME,
    AM_NEXT_ROUND,
    AM_SHOW_SCORES,
    AM_NEW_HIGH_SCORE
  };

  Application();
  ~Application();

  void cleanup();

  void set_mode( int );
  
  Graphics & graphics();

  ModeBase *current_mode();
};

