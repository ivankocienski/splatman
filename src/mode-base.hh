
#pragma once

class Graphics;
class Application;

class ModeBase {
protected:

  Application *m_application;
  Graphics *m_graphics;

  void set_mode(int);

public:
  
  ModeBase( Application*, Graphics* );

  virtual void activate();
 
  virtual void on_key_down(int);
  virtual void on_key_up(int);

  virtual void move();
  virtual void draw();
};

