#include "texture.h"

#include "datastructs/io/tga_image.h"
#include "common/err_t.h"

err_t texture_t::load_custom (const std::string &asset_name)
{
  tga_image_t tga;
  RETURN_IF_FAIL (tga.load (asset_name));
  m_texture_id = tga.to_gl ();

  return ERR_OK;
}
