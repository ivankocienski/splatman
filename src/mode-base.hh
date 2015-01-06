
#pragma once

class Graphics;
class Application;
class AudioService;


class ModeBase {
protected:

  Application *m_application;
  Graphics *m_graphics;
  AudioService *m_audio;

  void set_mode(int);
  void center( int, const char* );

public:
  
  ModeBase( Application*, Graphics*, AudioService* );

  virtual void activate();
 
  virtual void on_key_down(int);
  virtual void on_key_up(int);

  virtual void move();
  virtual void draw();
};

