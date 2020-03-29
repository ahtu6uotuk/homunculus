#include "texture.h"

#include "engine/io/tga_image.h"
#include "common/err_t.h"

err_t texture_t::load_custom (const std::string &file_content)
{
  tga_image_t tga;
  RETURN_IF_FAIL (tga.load (file_content));
  m_texture_id = tga.to_gl ();

  return ERR_OK;
}
