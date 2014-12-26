
#include "splash-screen.hh"
#include "graphics.hh"
#include "application.hh"

SplashScreen::SplashScreen( Application *a, Graphics *g ) : ModeBase( a, g ) { 
}

void SplashScreen::init() {
}

void SplashScreen::activate() {

  m_counter = 4000;
}

void SplashScreen::on_key_down(int) {

}

void SplashScreen::draw() {

  m_graphics->draw_font_string( 0, 0, "Splatterman" );
}

void SplashScreen::move() {

  if(m_counter) {
    m_counter--;
    return;
  }

  m_application->set_mode( Application::AM_SHOW_SCORES ); 
}
