#include "renderer.h"
#include <GL/glew.h>


renderer_t::renderer_t ():
  m_font ("FreeSerif.ttf")
{}

err_t renderer_t::init ()
{
  glewExperimental = GL_TRUE;
  if (glewInit () != GLEW_OK)
    return err_t ("failed to init OpenGL!");

  auto ret = m_font.load ();
  if (!ret.ok ())
    return ret;

  return ERR_OK;
}
