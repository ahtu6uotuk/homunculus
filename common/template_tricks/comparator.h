#pragma once

#include "common/common.h"

template <class T>
struct is_unique_ptr : std::false_type
{};
template <class T, class D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
{};

template<typename T>
bool typed_is_default (const T &data)
{
  if constexpr (is_floating_point<T>::value)
    {
      return !fuzzycmp (data, 0);
    }
  else if constexpr (is_unique_ptr<T>::value)
    {
      return !data;
    }
  else
    {
      T temp {};
      return data == temp;
    }
}
