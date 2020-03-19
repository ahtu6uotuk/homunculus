#include "run_calc_thread.h"

#include "math.h"

#include "control_flow/control_flow.h"
#include "control_flow/make_gui_content.h"
#include "logic/world.h"
#include "engine/event.h"
#include "common/thread_info.h"
#include "control_flow/request_to_gui.h"
#include "control_flow/request_to_calc.h"

void run_calc_thread (std::unique_ptr<thread_info_t> thr_info, control_flow &flow)
{
  std::unique_ptr<request_to_calc_base> &old_request_to_calc = flow.m_old_request_to_calc;
  std::unique_ptr<request_to_gui_base> &new_request_to_gui = flow.m_new_request_to_gui;
  world_t &world = *flow.m_world;
  engine_t &engine = *flow.m_engine;

  thr_info->sync_with_main ();
  while (!old_request_to_calc->is_exit ())
    {
      old_request_to_calc->exec_assert (world, *thr_info);

      // pretending to do something
      int j = 0;
      for (int i = 0; i < 10000; i++)
        j = j + sin (i);
      for (int i = 0; i < 15; i++)
        thr_info->sync ();
      //

      make_gui_content (engine, world, *thr_info, new_request_to_gui);

      thr_info->sync_with_main ();
      thr_info->sync_with_main ();
    }
}
