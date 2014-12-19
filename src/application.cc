
#include "application.hh"

Application::Application() : m_round( (Application*)this, &m_graphics ) {
}

void Application::init() {

  m_graphics.init();
  
  m_round.init();

  set_mode( AM_ROUND );
}

void Application::cleanup() {

  m_graphics.cleanup();
}

void Application::set_mode( int m ) {

  switch(m) {
    case AM_ROUND:
      m_current_mode = (ModeBase *)&m_round;
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
