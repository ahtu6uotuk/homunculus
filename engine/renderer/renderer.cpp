#include "renderer.h"
#include <GL/glew.h>
#include "engine/engine.h"


renderer_t::renderer_t (engine_t &engine):
  m_engine (engine),
  m_window (engine.get_sfml_window ()),
  m_gui (engine.get_gui_system ()),
  m_font ("FreeSerif.ttf")
{}

err_t renderer_t::init ()
{
  glewExperimental = GL_TRUE;
  if (glewInit () != GLEW_OK)
    return err_t ("failed to init OpenGL!");

  glEnable (GL_CULL_FACE);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto ret = m_font.load ();
  if (!ret.ok ())
    return ret;

  glViewport (0, 0, m_window.getSize ().x, m_window.getSize ().y);

  return ERR_OK;
}

void renderer_t::render ()
{
  gluOrtho2D (0., 0., m_window.getSize ().x, m_window.getSize ().y);
  m_gui.draw ();
}
