#pragma once

#include "common/common.h"

template <class T>
struct is_unique_ptr : std::false_type
{};
template <class T, class D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
{};

template<typename T>
bool typedCompare (const T &lhs, const T &rhs)
{
  if constexpr (is_floating_point<T>::value)
    {
      return !fuzzycmp (lhs, rhs, 0);
    }
  else if constexpr (is_unique_ptr<T>::value)
    {
      return uptrs_are_equal (lhs, rhs);
    }
  else
    {  // add other if-else here
      return lhs == rhs;
    }
}
