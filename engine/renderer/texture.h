#pragma once
#include <GL/gl.h>

enum class texture_type_t
{
  DIFFUSE = 0,
  COUNT,
  ERROR = COUNT
};

class texture_t
{
  texture_type_t m_texture_type;
  GLuint m_texture_id;
};
