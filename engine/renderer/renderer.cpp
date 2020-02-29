#include "renderer.h"
#include <GL/glew.h>
#include "engine/engine.h"
#include "engine/gui/gui_context.h"
#include "engine/renderer/shader.h"


renderer_t::renderer_t (engine_t &engine):
  m_engine (engine),
  m_window (engine.get_sfml_window ()),
  m_gui (engine.get_gui_system ()),
  m_font ("FreeSerif.ttf", 48),
  m_camera (glm::vec3 (0.f, 0.f, 0.f))
{}

err_t renderer_t::init ()
{
  glewExperimental = GL_TRUE;
  if (glewInit () != GLEW_OK)
    return err_t ("failed to init OpenGL!");

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  auto ret = m_font.load ();
  if (!ret.ok ())
    return ret;

  glViewport (0., 0., 800, 600);

  return ERR_OK;
}

void renderer_t::render ()
{
  glClearColor (0., 0., 0., 0.);
  glClear (GL_COLOR_BUFFER_BIT);
  //... Draw something here
  glPushMatrix ();
  gluOrtho2D (0., 800, 0., 600.);
  m_gui.draw ();
  glPopMatrix ();
}

renderer_t::~renderer_t ()
{}
