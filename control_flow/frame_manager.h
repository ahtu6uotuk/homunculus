#pragma once

#include <optional>
#include <chrono>
#include "common/common.h"

class frame_manager
{
  using time_point_t = chrono::time_point<chrono::steady_clock>;
  using duration_t = chrono::nanoseconds;

public:
  frame_manager ();

  void start_frame ();
  string end_frame();

  constexpr static double frame_length = 1. / 60.;
  constexpr static duration_t frame_length_d = duration_t {16666667};

private:
  static double to_double (const duration_t &d);
  optional<time_point_t> m_last_frame_start;
};