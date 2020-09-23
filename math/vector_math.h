#pragma once
#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H
#include "common/concepts_ext.h"

namespace geom
{
  template<std::floating_point fp_t, int len>
  class vec_t
  {
    fp_t m_values[len];
  public:
    vec_t (fp_t value)
    {
      for (decltype (len) i = 0; i < len; i++)
        m_values[i] = value;
    }

    fp_t at (decltype (len) pos) const { return m_values[pos]; }

    fp_t &operator[] (decltype (len) pos) { return m_values[pos]; }

    fp_t *data () { return m_values; }

    const fp_t *data () const { return m_values; }

    constexpr decltype (len) size () const { return len; }

    vec_t &operator*= (fp_t mult)
    {
      for (decltype (len) i = 0; i < len; i++)
        m_values[i] *= mult;

      return *this;
    }

    vec_t &operator/= (fp_t mult)
    {
      for (decltype (len) i = 0; i < len; i++)
        m_values[i] /= mult;

      return *this;
    }

    vec_t &operator= (const vec_t &rhs)
    {
      for (decltype (len) i = 0; i < len; i++)
        m_values[i] = rhs.m_values[i];

      return *this;
    }
  };

  template<std::floating_point fp_t, int len>
  vec_t<fp_t, len> operator+ (const vec_t<fp_t, len> &a, const vec_t<fp_t, len> &b)
  {
    vec_t<fp_t, len> rhs = a;
    for (decltype (len) i = 0; i < len; i++)
      a += b;

    return rhs;
  }

  template<std::floating_point fp_t, int len>
  vec_t<fp_t, len> operator- (const vec_t<fp_t, len> &a, const vec_t<fp_t, len> &b)
  {
    vec_t<fp_t, len> rhs = a;
    for (decltype (len) i = 0; i < len; i++)
      a -= b;

    return rhs;
  }

  template<std::floating_point fp_t, int len>
  fp_t scalar_product (const vec_t<fp_t, len> &a, const vec_t<fp_t, len> &b)
  {
    fp_t scalar = 0.;

    for (decltype (len) i = 0; i < len; i++)
      scalar += a.at (i) * b.at (i);

    return scalar;
  }

  using vec2f_t = vec_t<float, 2>;
  using vec2_t = vec_t<double, 2>;
  using vec3f_t = vec_t<float, 3>;
  using vec3_t = vec_t<double, 3>;
}

#endif // VECTOR_MATH_H
