#pragma once

#include "common/err_t.h"
#include "datastructs/shader_fwd.h"

template<shader_type_t SHADER_TYPE>
class subshader_t
{
  unsigned int m_id = 0;
public:
  subshader_t () {}
  err_t load_custom (const std::string &asset_name);
  subshader_t (const subshader_t &) = delete;
  subshader_t (subshader_t &&) = delete;
  unsigned int get_id () const {return m_id;}
  err_t check () const;
  ~subshader_t ();
};

using vertex_shader_t = subshader_t<shader_type_t::VERTEX>;
using fragment_shader_t = subshader_t<shader_type_t::FRAGMENT>;

class shader_t
{
private:
  unsigned int m_id = 0;
public:
  err_t load_custom (const std::string &asset_name);
  shader_t () = default;
  shader_t (const shader_t &) = delete;
  shader_t (shader_t &&) = delete;
  shader_t (unsigned int m_vertex_id, unsigned int m_fragment_id);
  void init (unsigned int m_vertex_id, unsigned int m_fragment_id);
  void use () const;
  void set_uniform_1i (const std::string &var_name, const int value) const;
  void set_uniform_1f (const std::string &var_name, const float value) const;
  void set_uniform_1d (const std::string &var_name, const double value) const;
  void set_uniform_3f (const std::string &var_name, const float v1, const float v2, const float v3) const;
  void set_uniform_3f (const std::string &var_name, const float *vec3) const;
  void set_uniform_mat4 (const std::string &var_name, const float *mat4, const bool is_transpose = false) const;
  unsigned int get_program_id () const {return m_id;}
  err_t check ();
  ~shader_t ();
};
