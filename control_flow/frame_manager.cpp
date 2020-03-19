#include "frame_manager.h"

#include <chrono>
#include <thread>

#include "engine/gui/gui_textline.h"
#include "common/string/string_utils.h"

using namespace std::chrono;

frame_manager::frame_manager (gui_textline_t &indicator) : m_indicator (indicator) {}

void frame_manager::start_frame ()
{
  assert_check (!m_last_frame_start.has_value (), "Don't call start twice in a row");

  m_last_frame_start = steady_clock::now ();
}

double frame_manager::to_double (const frame_manager::duration_t &d)
{
  return duration_cast<duration<double>> (d).count ();
}

void frame_manager::end_frame ()
{
  assert_check (m_last_frame_start.has_value (), "Don't call end before start");

  time_point_t end_time = steady_clock::now ();

  duration_t time_passed = duration_cast<duration_t> (end_time - *m_last_frame_start);
  m_last_frame_start = std::nullopt;

  if (time_passed >= frame_length_d)
    {
      m_indicator.set_text ("Freezing!");
      return;
    }

  duration_t sleep_for = frame_length_d - time_passed;
  std::this_thread::sleep_for (sleep_for);
  double ratio = to_double (sleep_for) / to_double (frame_length_d);

  m_indicator.set_text (string_printf ("Performance ratio: %.2lf", ratio));
}
