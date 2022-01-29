#pragma once

enum class renderer_type_t
{
  opengl,
  vulkan,
  software,
  count
};

const char *to_cstr (renderer_type_t type);
