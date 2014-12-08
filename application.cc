
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "application.hh"

using namespace std;

Application::Application() : m_player( &m_board ) {
}

void Application::init() {

  m_ghosts.resize(1);

  m_ghosts[0].setup( &m_board, 14, 12 );
}

void Application::cleanup() {
}

void Application::move() {
  m_player.move();

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
    it->move();
}

void Application::draw() {
  m_board.draw();
  m_player.draw();

  for( vector<Ghost>::iterator it = m_ghosts.begin(); it != m_ghosts.end(); it++ )
    it->draw();
}

void Application::on_mouse_down( ) {
}

void Application::on_mouse_up( ) {
}

void Application::on_mouse_move( int x, int y ) {
}

void Application::on_key_down( int k ) {

  switch( k ) {

    case GLFW_KEY_UP:    m_player.want_move_up();    break;
    case GLFW_KEY_DOWN:  m_player.want_move_down();  break;
    case GLFW_KEY_LEFT:  m_player.want_move_left();  break;
    case GLFW_KEY_RIGHT: m_player.want_move_right(); break;

  }
}

void Application::on_key_up( int k ) {

}
