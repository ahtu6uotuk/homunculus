#pragma once
#ifndef SHADER_FWD_H
#define SHADER_FWD_H

enum class shader_type_t
{
  VERTEX,
  FRAGMENT
};

template<shader_type_t SHADER_TYPE>
class subshader_t;

using vertex_shader_t = subshader_t<shader_type_t::VERTEX>;
using fragment_shader_t = subshader_t<shader_type_t::FRAGMENT>;

class shader_t;

#endif // SHADER_FWD_H
