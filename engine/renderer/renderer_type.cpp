#include "renderer_type.h"

const char *to_cstr (renderer_type_t type)
{
  switch (type)
    {
    case renderer_type_t::opengl:
      return "opengl";
    case renderer_type_t::software:
      return "software";
    case renderer_type_t::vulkan:
      return "vulkan";
    case renderer_type_t::count:
      break;
    }

  return "";
}
