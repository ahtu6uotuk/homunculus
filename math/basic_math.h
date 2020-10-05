#pragma once
#ifndef BASIC_MATH_H
#define BASIC_MATH_H
#include <cmath>

namespace math
{
  constexpr double min_compare = 1.e-16;

  constexpr bool equal (double a, double b, double eps = min_compare)
  {
    return std::fabs (b - a) < eps;
  }
}

#endif // BASIC_MATH_H
