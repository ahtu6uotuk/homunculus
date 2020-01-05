#include "renderer.h"
#include <GL/glew.h>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

renderer_t::renderer_t ()
{}

err_t renderer_t::init ()
{
  glewExperimental = GL_TRUE;
  if (glewInit () != GLEW_OK)
    return err_t ("failed to init OpenGL!");

  FT_Library ft;
  if (FT_Init_FreeType (&ft))
    return err_t ("failed to init FreeType Library!");

  return ERR_OK;
}
