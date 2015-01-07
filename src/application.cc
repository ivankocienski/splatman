
#include <iostream>
using namespace std;

#include "application.hh"
#include "sounds.hh"

Application::Application() : 
  m_game( (Application*)this, &m_graphics, &m_score_board, &m_audio ), 
  m_splash_screen( (Application*)this, &m_graphics, &m_audio ),
  m_show_scores( (Application*)this, &m_graphics, &m_score_board, &m_audio ),
  m_new_high_score( (Application*)this, &m_graphics, &m_score_board, &m_audio )
{

  m_score_board.load();

  m_audio.init();
  m_audio.start();

  define_sounds( m_audio );

  m_graphics.init();
  
  set_mode( AM_SPLASH );
}

Application::~Application() {

  m_graphics.cleanup();

  try {
    m_audio.stop();

  } catch( const AudioException& x ) {

    cerr << "error: (" << x.function() << ") " << x.message() << endl;
  }
}

void Application::set_mode( int m ) {

  switch(m) {
    case AM_SHOW_SCORES:
      m_current_mode = (ModeBase *)&m_show_scores;
      break;

    case AM_SPLASH:
      m_current_mode = (ModeBase *)&m_splash_screen;
      break;

    case AM_NEW_GAME:
      m_game.reset_for_game();
      m_current_mode = (ModeBase *)&m_game;
      break;

    case AM_NEXT_ROUND:
      m_game.reset_for_round();
      m_current_mode = (ModeBase *)&m_game;
      break;

    case AM_NEW_HIGH_SCORE:
      m_current_mode = (ModeBase *)&m_new_high_score;
      break;

    default:
      throw "Application::set_mode(): mode identifier not recognised";
      break;
  }

  m_current_mode->activate();
}

ModeBase *Application::current_mode() {
  return m_current_mode;
}

Graphics & Application::graphics() {
  return m_graphics;
}
