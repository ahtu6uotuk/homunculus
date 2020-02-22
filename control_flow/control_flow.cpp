#include "control_flow.h"

#include "control_flow/run_calc_thread.h"
#include "control_flow/frame_manager.h"
#include "engine/engine.h"
#include "logic/world.h"
#include "engine/event.h"
#include "engine/gui/gui_context.h"
#include "common/thread_info.h"
#include "engine/gui/gui_textline.h"
#include "common/thread_sync.h"

control_flow::~control_flow () {}

control_flow::control_flow (int argc, char **argv) : m_argc (argc), m_argv (argv) {}

err_t control_flow::init ()
{
  m_engine = make_unique<engine_t> (m_argc, m_argv);
  RETURN_IF_FAIL (m_engine->init ());

  m_world = make_unique<world_t> ("test_story");
  RETURN_IF_FAIL (m_world->load ("initial_state"));

  m_sync = make_unique<thread_sync_t> (get_calc_threads_number ());
  m_sync_w_main = make_unique<thread_sync_t> (get_calc_threads_number () + 1);
  RETURN_IF_FAIL (create_threads ());

  m_old_events = vector<event_t> ();
  m_old_gui_content = make_unique<gui_context_t> (m_engine->get_gui_system ());

  return ERR_OK;
}

err_t control_flow::run ()
{
  RETURN_IF_FAIL (init ());
  frame_manager frame_mgr;

  while (m_old_events)
    {
      frame_mgr.start_frame ();
      m_sync_w_main->sync ();

      /// get new events
      m_new_events = m_engine->handle_events ();

      /// get new content
      do_nothing ("done by calc threads");

      /// handle old content
      m_engine->render_and_display (move (m_old_gui_content));

      /// handle old events
      do_nothing ("done by calc threads");

      m_sync_w_main->sync ();
      string frame_stats = frame_mgr.end_frame ();
      m_new_gui_content->add_element (make_unique<gui_textline_t> (
          m_engine->get_renderer (), 10, 0, gui_horizontal_alignment_t::LEFT,
          gui_vertical_alignment_t::UP, frame_stats, glm::vec3 (.7f, .15f, .15f), 24));

      m_old_events = move (m_new_events);
      m_old_gui_content = move (m_new_gui_content);
    }

  join_threads ();
  return ERR_OK;
}

size_t control_flow::get_calc_threads_number () const
{
  return max<size_t> (1, thread::hardware_concurrency () - 1);
}

err_t control_flow::create_threads ()
{
  const auto n_thr = get_calc_threads_number ();
  m_threads.resize (n_thr);
  for (size_t id = 0; id < n_thr; id++)
    {
      unique_ptr<thread_info_t> inf = make_unique<thread_info_t> (*m_sync, *m_sync_w_main, id, n_thr);
      m_threads[id] = thread (run_calc_thread, move (inf), std::ref (*this));
    }
  return ERR_OK;
}

void control_flow::join_threads ()
{
  m_sync_w_main->sync ();
  for (thread &thr : m_threads)
    thr.join ();
}
