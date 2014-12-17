
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include <iostream>

#include "application.hh"

using namespace std;

Application::Application() : m_player( this, &m_board, &m_graphics ), m_board( &m_graphics ) {

  m_player.setup();

  m_curx = 0;
  m_cury = 0;
  m_okay = false;
}

void Application::init() {

  m_graphics.init();
  
  m_ghosts.resize(4);

  reset_actors();
}

void Application::reset_actors() {
  
  m_player.reset();

  m_ghosts[0].setup( &m_board, &m_player, 14, 12, Ghost::GC_RED );
  m_ghosts[1].setup( &m_board, &m_player, 12, 14, Ghost::GC_YELLOW );
  m_ghosts[2].setup( &m_board, &m_player, 14, 14, Ghost::GC_PINK );
  m_ghosts[3].setup( &m_board, &m_player, 16, 14, Ghost::GC_BLUE );
}

void Application::cleanup() {

  m_graphics.cleanup();
}

void Application::move() {
  m_player.move();

  if( m_player.pip_count() == m_board.pip_count() ) {
    cout << "you have all the pips" << endl;
    exit(0);
  }

  return;

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ ) {
    it->move();

/*     if( m_player.is_touching( *it )) {
 * 
 *       if( it->is_scared()) {
 *         it->trigger_eyes();
 * 
 *       } else {
 * 
 *         if( !it->is_eyes() ) {
 * 
 *           // TODO: death animation
 *           cout << "loses life" << endl;
 *           
 *           m_player.decrement_lives();
 *           if( m_player.life_count() ) {
 *           
 *             reset_actors();
 *           } else {
 *             cout << "You have no lives left" << endl;
 *             exit(0);
 * 
 *           }
 *         }
 * 
 *       }
 *     }
 */
  }
}

void Application::scare_ghosts() {

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
    it->trigger_scared();
}

void Application::draw() {

  glEnable(GL_TEXTURE_2D);
  m_graphics.draw_board( 0, 0 );
  
  m_board.draw();

  m_player.draw();
  glDisable(GL_TEXTURE_2D);

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
    it->draw();


  m_pulse++;
  if( (m_pulse >> 7 ) & 1 ) return;

  if(m_okay)
    glColor3f( 0, 1, 0 );
  else
    glColor3f( 1, 0, 0 );


  glBegin( GL_LINE_LOOP );

  float rx = m_curx * 16;
  float ry = m_cury * 16;

  glVertex2f( rx, ry );
  glVertex2f( rx + 15, ry );
  glVertex2f( rx + 15, ry + 15);
  glVertex2f( rx, ry + 15);
  glEnd();
}

void Application::on_mouse_down( ) {


//  if( m_curx < 0 || m_curx > 27 ) return;
//  if( m_cury < 0 || m_cury > 30 ) return;
//
//  if( m_board.actor_can_go( m_curx, m_cury ) )

  //if( m_okay )  m_ghosts[0].setup( &m_board, &m_player, m_curx, m_cury, Ghost::GC_RED );
}

void Application::on_mouse_up( ) {
}

void Application::on_mouse_move( int x, int y ) {
  m_curx = (x ) >> 4;
  m_cury = (y) >> 4;

  m_okay = false;

  if( m_curx < 0 || m_curx > 27 ) return;
  if( m_cury < 0 || m_cury > 30 ) return;

  if( m_board.actor_can_go( m_curx << 4, m_cury << 4) )
    m_okay = true;
}

void Application::on_key_down( int k ) {

  switch( k ) {

    case GLFW_KEY_UP:    m_player.want_move_up();    break;
    case GLFW_KEY_DOWN:  m_player.want_move_down();  break;
    case GLFW_KEY_LEFT:  m_player.want_move_left();  break;
    case GLFW_KEY_RIGHT: m_player.want_move_right(); break;

    case GLFW_KEY_T:

     for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )

       it->trigger_scared();

     break;

  }
}

void Application::on_key_up( int k ) {

}
