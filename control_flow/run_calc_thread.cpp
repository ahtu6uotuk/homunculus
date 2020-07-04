#include "run_calc_thread.h"

#include <math.h>

#include "control_flow/control_flow.h"
#include "control_flow/make_gui_content.h"
#include "world/world.h"
#include "world/action.h"
#include "world/policies/choose_action_policy.h"
#include "common/thread_info.h"
#include "control_flow/request_to_gui.h"
#include "control_flow/request_to_calc.h"

static bool handle_requests (std::vector<std::unique_ptr<request_to_calc_base>> &requests, world_t &world, thread_info_t &thr_info)
{
  for (auto &req : requests)
    {
      if (req->is_exit ())
        return false;
      if (thr_info.is_main_thread ())
        req->exec_assert (world, thr_info);
    }
  return true;
}

void run_calc_thread (std::unique_ptr<thread_info_t> thr_info, control_flow &flow)
{
  std::vector<std::unique_ptr<request_to_calc_base>> &old_request_to_calc = flow.m_old_request_to_calc;
  std::vector<std::unique_ptr<request_to_gui_base>> &new_request_to_gui = flow.m_new_request_to_gui;
  world_t &world = *flow.m_world;
  engine_t &engine = *flow.m_engine;

  thr_info->sync_with_main ();
  while (handle_requests (old_request_to_calc, world, *thr_info))
    {
      if (thr_info->is_main_thread ())
        {
          // choose actions
          std::vector<std::pair<int, std::unique_ptr<action>>> actors_and_actions;
          for (object_base *obj : world.get_level ().get_all ())
            {
              choose_action_policy *pl = obj->get_policy<choose_action_policy> ();
              if (pl)
                actors_and_actions.push_back (std::make_pair (obj->get_id (), pl->get_action (world)));
            }

          // execute actions
          for (auto &actor_and_action : actors_and_actions)
            actor_and_action.second->exec (actor_and_action.first, world);
        }

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
