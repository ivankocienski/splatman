
#include "mode-base.hh"
#include "application.hh"
#include "graphics.hh"

#include <iostream>
using namespace std;

void ModeBase::set_mode(int m) {
  m_application->set_mode(m);
}

ModeBase::ModeBase( Application* a, Graphics* g ) {
  m_graphics    = g;
  m_application = a; 
}

void ModeBase::activate() { 
  cout << "ModeBase: activate()" << endl;
}

void ModeBase::on_key_down(int) { 
}

void ModeBase::on_key_up(int) { 
}

void ModeBase::move() { 
}

void ModeBase::draw() { 
}
