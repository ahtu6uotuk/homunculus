#pragma once
#include <forward_list>
#include <functional>
#include <utility>

namespace impl
{
  template<typename ...args_t>
  using slot_function_t = std::function<void (args_t...)>;
}

template<typename ...args_t>
class signal_t
{
  std::forward_list<impl::slot_function_t<args_t...>> m_slots;
public:
  signal_t () = default;
  void operator() (args_t ...args)
  {
    for (auto &slot : m_slots)
      slot (args...);
  }
  void connect (signal_t &signal)
  {
    m_slots.emplace_front ([&signal] (args_t ...args) { signal (args...); });
  }
  void connect (impl::slot_function_t<args_t...> func)
  {
    m_slots.emplace_front (std::move (func));
  }
  ~signal_t () = default;
};

