#ifndef RENDERER_H
#define RENDERER_H
#include "common/err_t.h"
#include "engine/renderer/font.h"

class engine_t;
class gui_system_t;
namespace sf
{
  class RenderWindow;
}

class renderer_t
{
  engine_t &m_engine;
  sf::RenderWindow &m_window;
  gui_system_t &m_gui;
  font_t m_font;
public:
  renderer_t (engine_t &engine);
  err_t init ();
  void render ();
  font_t &get_font () {return m_font;}
};

#endif // RENDERER_H
