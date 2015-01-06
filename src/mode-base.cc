
#include <string.h>

#include "mode-base.hh"
#include "application.hh"
#include "graphics.hh"
#include "sounds.hh"

void ModeBase::set_mode(int m) {
  m_application->set_mode(m);
}

ModeBase::ModeBase( Application* a, Graphics* g, AudioService *s ) {
  m_graphics    = g;
  m_application = a; 
  m_audio       = s;
}

void ModeBase::activate() { }

void ModeBase::center( int y, const char *s ) {
  int x = 112 - strlen(s) * 4;

  m_graphics->draw_font_string( x, y, s );
}

void ModeBase::on_key_down(int) { 
}

void ModeBase::on_key_up(int) { 
}

void ModeBase::move() { 
}

void ModeBase::draw() { 
}
