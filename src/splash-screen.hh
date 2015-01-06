
#pragma once

class Application;
class Graphics;

#include "mode-base.hh"

class SplashScreen : public ModeBase {
private:

  int m_counter;

public:

  SplashScreen( Application*, Graphics*, AudioService* );

  void init();

  void activate();

  void on_key_down(int);

  void draw();
  void move();
};
