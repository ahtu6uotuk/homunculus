#include "control_flow.h"

#include "control_flow/run_calc_thread.h"
#include "control_flow/frame_manager.h"
#include "engine/engine.h"
#include "world/world.h"
#include "engine/gui/gui_context.h"
#include "common/thread_info.h"
#include "engine/gui/gui_textline.h"
#include "common/thread_sync.h"
#include "control_flow/handle_gui_events.h"
#include "control_flow/request_to_gui.h"
#include "control_flow/request_to_calc.h"

control_flow::~control_flow () {}

control_flow::control_flow (int argc, char **argv) : m_argc (argc), m_argv (argv) {}

err_t control_flow::init ()
{
  m_engine = std::make_unique<engine_t> (m_argc, m_argv);
  RETURN_IF_FAIL (m_engine->init ());

  m_world = std::make_unique<world_t> ("test_story");
  RETURN_IF_FAIL (m_world->load ("initial_state"));

  m_sync = std::make_unique<thread_sync_t> (get_calc_threads_number ());
  m_sync_w_main = std::make_unique<thread_sync_t> (get_calc_threads_number () + 1);
  RETURN_IF_FAIL (create_threads ());

  m_frame_manager = std::make_unique<frame_manager> (*m_engine->get_performance_indicator ());

  return ERR_OK;
}

err_t control_flow::run ()
{
  RETURN_IF_FAIL (init ());

  bool first_frame = true;
  m_sync_w_main->sync ();
  while (m_old_request_to_calc.empty () || !m_old_request_to_calc.back ()->is_exit ())
    {
      m_frame_manager->start_frame ();

      if (first_frame)
        {
          first_frame = false;
        }
      else
        {
          m_new_request_to_calc = handle_gui_events (*m_engine);
          m_engine->render_and_display ();
        }

      m_sync_w_main->sync ();
      m_old_request_to_calc = move (m_new_request_to_calc);
      m_old_request_to_gui = move (m_new_request_to_gui);
      for (auto &req : m_old_request_to_gui)
        req->exec_assert (*m_engine);
      m_sync_w_main->sync ();

      m_frame_manager->end_frame ();
    }

  join_threads ();
  m_world->save ("initial_state");
  return ERR_OK;
}

size_t control_flow::get_calc_threads_number () const
{
  return std::max<size_t> (1, std::thread::hardware_concurrency () - 1);
}

err_t control_flow::create_threads ()
{
  const auto n_thr = get_calc_threads_number ();
  m_threads.resize (n_thr);
  for (size_t id = 0; id < n_thr; id++)
    {
      std::unique_ptr<thread_info_t> inf = std::make_unique<thread_info_t> (*m_sync, *m_sync_w_main, id, n_thr);
      m_threads[id] = std::thread (run_calc_thread, move (inf), std::ref (*this));
    }
  return ERR_OK;
}

void control_flow::join_threads ()
{
  for (std::thread &thr : m_threads)
    thr.join ();
}
