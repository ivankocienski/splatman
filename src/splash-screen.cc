
#include <iostream>
using std::cout;
using std::endl;

#include <string.h>

#include <GLFW/glfw3.h>

#include "common.hh"
#include "splash-screen.hh"
#include "graphics.hh"
#include "application.hh"

/*
 * support classes that wrap the guts of the animation
 *
 */

// Splashman
// =========

SplashMan::SplashMan( Graphics *g, SplashScreen& ss ) : m_arena(ss), m_graphics(g) {
}

void SplashMan::reset() {
  m_xpos = 260;
}

void SplashMan::move() {

  m_xpos--;

  if( m_xpos == -16 ) 
    m_arena.man_is_done(); 

  if( (m_xpos & 15) == 0 ) {

    int col = (m_xpos + 8) >> 4;

    if(col < 11) {
      int letter = col - 2;
      if( letter > -1 ) m_arena.trigger_logo_letter(letter);
    }
  }
}

void SplashMan::draw() {

  m_graphics->draw_player( m_xpos, 96, 0 );
}

bool SplashMan::is_done() {
  return m_xpos < -16;
}




/*
 * the splash screen main class that is what ties this
 * dog and pony show together
 *
 */

SplashScreen::SplashScreen( Application *a, Graphics *g, AudioService *as ) : ModeBase( a, g, as ), m_man( g, *this ) { 
}

void SplashScreen::activate() {

  memset( m_logo_pos, 0, sizeof(m_logo_pos));
  m_counter = 500;
  m_man.reset();
}

void SplashScreen::on_key_down(int k) {

  if( k == GLFW_KEY_SPACE ) 
    m_application->set_mode( Application::AM_NEW_GAME );
}


void SplashScreen::draw() {

  m_man.draw();

  for( int i = 0; i < 8; i++ ) {
    if(!m_logo_pos[i]) continue;
    m_graphics->draw_logo( 48 + i * 16, m_logo_pos[i], i );
  }

  center( 128, "By Ivan Kocienski." );

  if(m_man.is_done()) {
    center( 144, "$ 2015" );

    center( 180, "Original Game by Namco" );

    if( (g_anim >> 5) & 1 ) 
      center( 280, "PRESS SPACEBAR TO START.");
  }
}

void SplashScreen::move() {

  m_man.move();

  for( int i = 0; i < 8; i++ ) {
    if(!m_logo_pos[i]) continue;

    if(m_logo_pos[i] > 64 ) m_logo_pos[i]--;
  }

  if(m_counter) {
    m_counter--;
    return;
  }

  m_application->set_mode( Application::AM_SHOW_SCORES ); 

}

void SplashScreen::trigger_logo_letter( int ln ) {
  m_audio->play(0, SP_PICKUP_POWERUP );
  m_logo_pos[ln] = 96;
}

void SplashScreen::man_is_done() {
  m_audio->play(0, SP_START_LEVEL );
}
