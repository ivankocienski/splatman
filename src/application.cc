
#include "application.hh"

Application::Application() : 
  m_round( (Application*)this, &m_graphics, &m_score_board ), 
  m_splash_screen( (Application*)this, &m_graphics ),
  m_show_scores( (Application*)this, &m_graphics, &m_score_board ),
  m_new_high_score( (Application*)this, &m_graphics, &m_score_board )
{ }

void Application::init() {

  m_score_board.load();

  m_graphics.init();
  
  m_round.init();
  //m_splash_screen.init();
  //m_show_scores.init();
  //m_new_high_score.init();

  set_mode( AM_SPLASH );
//  set_mode( AM_NEW_HIGH_SCORE );

  m_score_board.push_new_score( 50000 );
}

void Application::cleanup() {

  m_graphics.cleanup();
}

void Application::set_mode( int m ) {

  switch(m) {
    case AM_SHOW_SCORES:
      m_current_mode = (ModeBase *)&m_show_scores;
      break;

    case AM_SPLASH:
      m_current_mode = (ModeBase *)&m_splash_screen;
      break;

    case AM_ROUND:
      m_current_mode = (ModeBase *)&m_round;
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
