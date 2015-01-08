
#include "sounds.hh"

#define BEEP( _ap, _as, _wf, _v, _f, _d ) (_ap).beep( (_as).oscillator(AudioService::_wf), _v, _f, _d )

void define_sounds( AudioService &as ) {

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SQUARE,  0.5, 1800, 50 );
    BEEP( ap, as, WF_SQUARE,  0.5,  900, 50 );
    BEEP( ap, as, WF_SILENCE, 0.0,    0, 700 );

    BEEP( ap, as, WF_SQUARE,  0.3, 1800, 50 );
    BEEP( ap, as, WF_SQUARE,  0.3,  900, 50 );
    BEEP( ap, as, WF_SILENCE, 0.0,    0, 700 );

    BEEP( ap, as, WF_SQUARE,  0.1, 1800, 50 );
    BEEP( ap, as, WF_SQUARE,  0.1,  900, 50 );
    BEEP( ap, as, WF_SILENCE, 0.0,    0, 700 );

    as.set_pattern( SP_START_LEVEL, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SINE, 0.3, 500, 20 );
    BEEP( ap, as, WF_SINE, 0.3, 700, 20 );
    BEEP( ap, as, WF_SINE, 0.3, 500, 20 );

    as.set_pattern( SP_PICKUP_PIL, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_TRIANGLE, 0.5, 500, 20 );
    BEEP( ap, as, WF_TRIANGLE, 0.5, 1000, 20 );
    BEEP( ap, as, WF_TRIANGLE, 0.5, 1500, 20 );
    BEEP( ap, as, WF_TRIANGLE, 0.5, 2000, 20 );
    BEEP( ap, as, WF_TRIANGLE, 0.4, 2500, 10 );
    BEEP( ap, as, WF_TRIANGLE, 0.3, 2500, 10 );
    BEEP( ap, as, WF_TRIANGLE, 0.2, 2500, 10 );
    BEEP( ap, as, WF_TRIANGLE, 0.1, 2500, 10 );

    as.set_pattern( SP_PICKUP_POWERUP, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SAWTOOTH, 0.5, 900, 200 );
    BEEP( ap, as, WF_TRIANGLE, 0.5, 900, 200 );
    BEEP( ap, as, WF_SQUARE,   0.5, 900, 200 );
    BEEP( ap, as, WF_SINE,     0.5, 900, 200 );

    as.set_pattern( SP_EAT_GHOST, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SQUARE, 0.7,  2000, 250 );
    BEEP( ap, as, WF_SQUARE, 0.7,  1900, 250 );
    BEEP( ap, as, WF_SQUARE, 0.65, 1800, 250 );
    BEEP( ap, as, WF_SQUARE, 0.5,  1600, 150 );
    BEEP( ap, as, WF_SQUARE, 0.4,  1400, 150 );
    BEEP( ap, as, WF_SQUARE, 0.3,  1000, 150 );
    BEEP( ap, as, WF_SQUARE, 0.2,   600, 100 );
    BEEP( ap, as, WF_SQUARE, 0.1,   200, 100 );
    BEEP( ap, as, WF_NOISE,  0.5,  2000, 400 );

    as.set_pattern( SP_DIED, ap );
  }
  
  {
    AudioPattern ap;

    BEEP( ap, as, WF_SINE, 0.2, 400, 40 );
    BEEP( ap, as, WF_SINE, 0.2, 500, 40 );
    BEEP( ap, as, WF_SINE, 0.2, 400, 20 );
    BEEP( ap, as, WF_SINE, 0.2, 500, 20 );

    as.set_pattern( SP_CHANGE_DIR, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SINE, 0.2, 500, 50 );
    BEEP( ap, as, WF_SINE, 0.1, 500, 50 );

    as.set_pattern( SP_NEW_SCORE_MOVE, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SINE, 0.4,  500, 100 );
    BEEP( ap, as, WF_SINE, 0.4, 1000, 100 );
    BEEP( ap, as, WF_SINE, 0.4, 1500, 100 );
    BEEP( ap, as, WF_SINE, 0.4, 2000, 100 );

    BEEP( ap, as, WF_SILENCE, 0, 0, 100 );

    BEEP( ap, as, WF_SINE, 0.3,  500, 100 );
    BEEP( ap, as, WF_SINE, 0.3, 1000, 100 );
    BEEP( ap, as, WF_SINE, 0.3, 1500, 100 );
    BEEP( ap, as, WF_SINE, 0.3, 2000, 100 );

    BEEP( ap, as, WF_SILENCE, 0, 0, 100 );

    BEEP( ap, as, WF_SINE, 0.1,  500, 100 );
    BEEP( ap, as, WF_SINE, 0.1, 1000, 100 );
    BEEP( ap, as, WF_SINE, 0.1, 1500, 100 );
    BEEP( ap, as, WF_SINE, 0.1, 2000, 100 );

    as.set_pattern( SP_NEW_SCORE_SHOW, ap );
  }
  
  {
    AudioPattern ap;

    BEEP( ap, as, WF_SINE, 0.2, 700, 50 );
    BEEP( ap, as, WF_SINE, 0.1, 700, 50 );

    as.set_pattern( SP_NEW_SCORE_ENTER, ap );
  }

  {
    AudioPattern ap;

    BEEP( ap, as, WF_SINE, 0.2, 300, 50 );
    BEEP( ap, as, WF_SINE, 0.1, 300, 50 );

    as.set_pattern( SP_NEW_SCORE_DELETE, ap );
  }

}
