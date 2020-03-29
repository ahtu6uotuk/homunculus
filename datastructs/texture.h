#pragma once
#include <string>
#include <GL/gl.h>

class err_t;

enum class texture_type_t
{
  DIFFUSE = 0,
  COUNT,
  INVALID = COUNT
};

class texture_t
{
public:
  err_t load_custom (const std::string &file_content);

  texture_type_t m_texture_type;
  GLuint m_texture_id;
};
