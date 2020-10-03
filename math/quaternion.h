#pragma once
#ifndef QUATERNION_T_H
#define QUATERNION_T_H
#include <cmath>

/// @brief Template class for quaternion number system
/// @tparam fp_t floating-point type
template<typename fp_t>
class quaternion_t
{
  union
  {
    struct
    {
      double m_w;
      double m_i;
      double m_j;
      double m_k;
    };
    fp_t m_numbers[4];
  };

public:

  // Constructors
  constexpr quaternion_t ():
    m_w (0.), m_i (0.), m_j (0.), m_k (0.)
  {}
  constexpr quaternion_t (fp_t w, fp_t i, fp_t j, fp_t k):
    m_w (w), m_i (i), m_j (j), m_k (k)
  {}
  constexpr quaternion_t (const quaternion_t &b):
    m_w (b.m_w), m_i (b.m_i), m_j (b.m_j), m_k (b.m_k)
  {}

  // Operators
  constexpr quaternion_t &operator= (const quaternion_t &b)
  {
    m_w = b.m_w;
    m_i = b.m_i;
    m_j = b.m_j;
    m_k = b.m_k;
  }
  constexpr quaternion_t &operator+= (const quaternion_t &b)
  {
    for (int i = 0; i < 4; i++) { m_numbers[i] += b.m_numbers[i]; }
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
    for (int i = 0; i < 4; i++) { m_numbers[i] -= b.m_numbers[i]; }
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

  // Functions
  constexpr fp_t *data ()
  {
    return m_numbers;
  }
  constexpr const fp_t *cdata () const
  {
    return m_numbers;
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
    if (std::fabs (norm) > 1.e-16)
      {
        for (int i = 0; i < 4; i++)
          m_numbers[i] /= norm;
      }
  }
};

#endif // QUATERNION_T_H
