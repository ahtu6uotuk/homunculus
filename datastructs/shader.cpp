#include "shader.h"

#include <vector>
#include <GL/glew.h>

#include "common/string/string_utils.h"
#include "resource/resource_manager.h"

shader_t::shader_t (GLuint m_vertex_id, GLuint m_fragment_id)
{
  init (m_vertex_id, m_fragment_id);
}

void shader_t::init (GLuint m_vertex_id, GLuint m_fragment_id)
{
  m_id = glCreateProgram ();
  glAttachShader (m_id, m_vertex_id);
  glAttachShader (m_id, m_fragment_id);
  glLinkProgram (m_id);
}

void shader_t::use () const
{
  glUseProgram (m_id);
}

void shader_t::set_uniform_1i (const std::string &var_name, const int value) const
{
  glUniform1i (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_uniform_1f (const std::string &var_name, const float value) const
{
  glUniform1f (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_uniform_1d (const std::string &var_name, const double value) const
{
  glUniform1d (glGetUniformLocation (m_id, var_name.c_str ()), value);
}

void shader_t::set_uniform_3f (const std::string &var_name, const float v1, const float v2, const float v3) const
{
  glUniform3f (glGetUniformLocation (m_id, var_name.c_str ()), v1, v2, v3);
}

void shader_t::set_uniform_3f (const std::string &var_name, const float *vec3) const
{
  return set_uniform_3f (var_name.c_str (), vec3[0], vec3[1], vec3[2]);
}

void shader_t::set_uniform_mat4 (const std::string &var_name, const float *mat4, const bool is_transpose) const
{
  glUniformMatrix4fv (glGetUniformLocation (m_id, var_name.c_str ()), 1, is_transpose, mat4);
}

err_t shader_t::check ()
{
  GLint status = 0;
  glGetProgramiv (m_id, GL_LINK_STATUS, &status);
  if (!status)
    {
      std::string buffer (1024, 0);
      glGetProgramInfoLog (m_id, 1024, nullptr, buffer.data ());
      return err_t (buffer);
    }
  return ERR_OK;
}

shader_t::~shader_t ()
{
  if (glIsProgram (m_id))
    glDeleteProgram (m_id);
}

constexpr GLenum shader_type_to_GLenum (shader_type_t shader_type)
{
  switch (shader_type)
    {
    case shader_type_t::VERTEX:
      return GL_VERTEX_SHADER;
    case shader_type_t::FRAGMENT:
      return GL_FRAGMENT_SHADER;
    }
  abort (); // you shouldn't be here
}

template<shader_type_t SHADER_TYPE>
err_t subshader_t<SHADER_TYPE>::load_custom (const std::string &source_code)
{
  if (source_code.empty ())
    return std::string ("Empty shader data!");

  std::vector<char> source_code_copy (source_code.begin (), source_code.end ());
  source_code_copy.push_back ('\0');
  const char *cchr = &source_code_copy[0];

  m_id = glCreateShader (shader_type_to_GLenum (SHADER_TYPE));
  glShaderSource (m_id, 1, &cchr, nullptr);
  glCompileShader (m_id);

  return ERR_OK;
}

template<shader_type_t SHADER_TYPE>
err_t subshader_t<SHADER_TYPE>::check () const
{
  GLint status;
  glGetShaderiv (m_id, GL_COMPILE_STATUS, &status);
  if (!status)
    {
      std::string buffer (1024, 0);
      glGetShaderInfoLog (m_id, 1024, nullptr, buffer.data ());
      return err_t (buffer);
    }
  return ERR_OK;
}

template<shader_type_t SHADER_TYPE>
subshader_t<SHADER_TYPE>::~subshader_t ()
{
  if (glIsShader (m_id))
    glDeleteShader (m_id);
}

template class subshader_t<shader_type_t::VERTEX>;
template class subshader_t<shader_type_t::FRAGMENT>;

err_t shader_t::load_custom (const std::string &file_contents)
{
  std::vector<std::string> two_shader_names = string_split (file_contents, '\n');
  if (two_shader_names.size () != 2)
    return std::string ("Shader file is supposed to have two names");

  // Its not great to explicitly call resource manager here. It would be better if asset_ptr did it.
  // But since shaders have this weird file-data structure, lets leave it like this for now.
  vertex_shader_t *v_shader = resource_manager::instance ().get_resource<vertex_shader_t> (two_shader_names[0]);
  fragment_shader_t *f_shader = resource_manager::instance ().get_resource<fragment_shader_t> (two_shader_names[1]);

  if (!v_shader || !f_shader)
    return string_printf (
        "Could not load shaders from %s and %s", two_shader_names[0].c_str (),
        two_shader_names[1].c_str ());

  init (v_shader->get_id (), f_shader->get_id ());
  return ERR_OK;
}
