

#include <GLFW/glfw3.h>

#include "common.hh"
#include "splash-screen.hh"
#include "graphics.hh"
#include "application.hh"

SplashScreen::SplashScreen( Application *a, Graphics *g, AudioService *as ) : ModeBase( a, g, as ) { 
}

void SplashScreen::init() {
}

void SplashScreen::activate() {

  m_counter = 500;
}

void SplashScreen::on_key_down(int k) {

  if( k == GLFW_KEY_SPACE ) 
    m_application->set_mode( Application::AM_NEW_GAME );
}


void SplashScreen::draw() {

  for( int i = 0; i < 8; i++ ) {
    m_graphics->draw_logo( 48 + i * 16, 64, i );
  }

  center( 128, "By Ivan Kocienski." );
  center( 144, "$ 2015" );

  center( 180, "Original Game by Namco" );

  if( (g_anim >> 5) & 1 ) 
    center( 280, "PRESS SPACEBAR TO START.");
}

void SplashScreen::move() {

  if(m_counter) {
    m_counter--;
    return;
  }

  m_application->set_mode( Application::AM_SHOW_SCORES ); 
}
