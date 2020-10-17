#pragma once
#ifndef QUATERNION_T_H
#define QUATERNION_T_H
#include "math/basic_math.h"

namespace detail
{
  /// @brief Template class for quaternion number system
  /// @tparam fp_t floating-point type
  template<typename fp_t>
  class quaternion_t
  {
    fp_t m_numbers[4] = {0.};

  public:
    constexpr quaternion_t (fp_t w, fp_t i, fp_t j, fp_t k):
      m_numbers ({w, i, j, k})
    {}
    constexpr quaternion_t (const quaternion_t &b):
      m_numbers (b.m_numbers)
    {}

    constexpr double w () const { return m_numbers[0]; }
    constexpr double i () const { return m_numbers[1]; }
    constexpr double j () const { return m_numbers[2]; }
    constexpr double k () const { return m_numbers[3]; }
    double *data () { return m_numbers; }

    // Operators
    constexpr quaternion_t &operator= (const quaternion_t &b)
    {
      for (int i = 0; i < 4; i++)
        m_numbers[i] = b.m_numbers[i];
    }


    constexpr quaternion_t &operator+= (const quaternion_t &b)
    {
      for (int i = 0; i < 4; i++)
        m_numbers[i] += b.m_numbers[i];

      return *this;
    }
    constexpr quaternion_t operator+ (const quaternion_t &b) const
    {
      quaternion_t<fp_t> c = *this;
      c += b;
      return c;
    }
    constexpr quaternion_t &operator-= (const quaternion_t &b)
    {
      for (int i = 0; i < 4; i++)
        m_numbers[i] -= b.m_numbers[i];

      return *this;
    }
    constexpr quaternion_t operator- (const quaternion_t &b) const
    {
      quaternion_t<fp_t> c = *this;
      c -= b;
      return *this;
    }
    constexpr quaternion_t &operator*= (const quaternion_t &b)
    {
      const double w = m_w * b.m_w - m_i * b.m_i - m_j * b.m_j - m_k * b.m_k;
      const double i;
      const double j;
      const double k;
      m_w = w;
      m_i = i;
      m_j = j;
      m_k = k;

      return *this;
    }
    constexpr quaternion_t operator* (const quaternion_t &b) const
    {
      quaternion_t<fp_t> c = *this;
      c *= b;
      return c;
    }
    constexpr quaternion_t &operator/= (const quaternion_t &b)
    {
      // TODO;
      return *this;
    }
    constexpr quaternion_t operator/ (const quaternion_t &b) const
    {
      quaternion_t<fp_t> c = *this;
      c /= b;
      return c;
    }

    double compute_norm () const
    {
      double sum = 0.;
      for (int i = 0; i < 4; i++)
        {
          sum += m_numbers[i] * m_numbers[i];
        }
      return std::sqrt (sum);
    }

    void normalize ()
    {
      double norm = compute_norm ();
      if (norm > math::min_compare)
        {
          for (int i = 0; i < 4; i++)
            m_numbers[i] /= norm;
        }
    }
  };
}

using quaternion_t = detail::quaternion_t<double>;

#endif // QUATERNION_T_H
