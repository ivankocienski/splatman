
#pragma once

class Application;
class Graphics;

#include "mode-base.hh"

class SplashScreen;

class SplashMan {
private:

  SplashScreen& m_arena;
  Graphics *m_graphics;

  int m_xpos;
  
public:

  SplashMan( Graphics*, SplashScreen& );

  void reset();
  void move();
  void draw();

  bool is_done();
};

//class TimedText {

//};

class SplashScreen : public ModeBase {
private:

  SplashMan m_man;
  
  int m_counter;
  int m_logo_pos[8];

public:

  SplashScreen( Application*, Graphics*, AudioService* );

  void activate();

  void on_key_down(int);

  void draw();
  void move();

  void trigger_logo_letter(int);
  void man_is_done();
};
