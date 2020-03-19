#pragma once

#include <optional>
#include <chrono>
#include "common/common.h"
class gui_textline_t;

class frame_manager
{
  using time_point_t = std::chrono::time_point<std::chrono::steady_clock>;
  using duration_t = std::chrono::nanoseconds;

public:
  frame_manager (gui_textline_t &indicator);

  void start_frame ();
  void end_frame();

  constexpr static double frame_length = 1. / 60.;
  constexpr static duration_t frame_length_d = duration_t {16666667};

private:
  gui_textline_t &m_indicator;

  static double to_double (const duration_t &d);
  std::optional<time_point_t> m_last_frame_start;
};
