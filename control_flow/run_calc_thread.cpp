#include "run_calc_thread.h"

#include "control_flow/control_flow.h"
#include "control_flow/make_gui_content.h"
#include "logic/world.h"
#include "engine/event.h"
#include "common/thread_info.h"

void run_calc_thread (unique_ptr<thread_info_t> thr_info, control_flow &flow)
{
  optional<vector<event_t>> &events = flow.m_old_events;

  while (true)
    {
      thr_info->sync_with_main ();
      if (!events)
        break;
      else
        do_nothing ();

      // pretending to do something
      int j = 0;
      for (int i = 0; i < 10000; i++)
        j = j + i;
      for (int i = 0; i < 3; i++)
        thr_info->sync ();
      //

      make_gui_content (*flow.m_engine, *flow.m_world, *thr_info, flow.m_new_gui_content);

      thr_info->sync_with_main ();
    }
}
