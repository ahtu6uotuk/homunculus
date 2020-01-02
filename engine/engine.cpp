#include "engine.h"
#include "common/common.h"
#include "common/thread_info.h"
#include <SFML/Window.hpp>

engine_t::engine_t (int argc, char *argv[]):
  m_window (sf::VideoMode::getDesktopMode (), "Homunculus"),
  m_logger ("engine.log"),
  m_thread (),
  m_thread_sync (get_computation_threads_number ()),
  m_run (true)
{
  do_nothing (argc, argv);
  m_window.setFramerateLimit (60);
  m_logger.print (log_section_t::ENGINE, log_priority_t::INFO, "initialization complete!");
}

err_t engine_t::init ()
{
  if (!m_logger.is_ok ())
    return err_t ("Internal logger error");

  const auto n_threads = get_computation_threads_number ();
  m_thread.resize (n_threads);
  for (size_t comp_thread_id = 0; comp_thread_id < n_threads; comp_thread_id++)
    {
      m_thread[comp_thread_id] = thread (run_computation_thread,
                                         make_unique<thread_info_t> (m_thread_sync, comp_thread_id, n_threads),
                                         std::ref (*this));
    }

  return ERR_OK;
}

void engine_t::handle_events ()
{
  sf::Event event;
  while (m_window.pollEvent (event) && !m_thread_sync.is_iteration_done ())
    {
      switch (event.type)
        {
        case sf::Event::Closed:
          {
            m_run = false;
            break;
          }
        default:
          {
            do_nothing ();
          }
        }
    }
}

size_t engine_t::get_computation_threads_number () const
{
  const auto hwc_threads = thread::hardware_concurrency () - 1;
  size_t n_threads = 1;
  if (hwc_threads > 1)
    n_threads = hwc_threads;

  return n_threads;
}

err_t engine_t::run_gui_thread ()
{
  while (m_run)
    {
      handle_events ();
      // ...do_something here
      m_window.display ();
    }
  m_window.close ();
  return ERR_OK;
}

int engine_t::exec ()
{
  if (!init ().ok ())
    {
      return -1;
    }

  if (!run_gui_thread ().ok ())
    {
      m_logger.print (log_section_t::ENGINE, log_priority_t::ERROR, "fatal error!");
      return -2;
    }

  for (auto &thr : m_thread)
    {
      thr.join ();
    }

  return 0;
}

engine_t::~engine_t ()
{}

int run_computation_thread (unique_ptr<thread_info_t> thr_info, engine_t &engine)
{
//  auto &logger = engine.get_logger ();
  int i = 0;
  while (engine.is_running ())
    {
//      logger.print (log_section_t::ENGINE, log_priority_t::INFO, "Ready thread:", std::this_thread::get_id ());
      thr_info->synchronize ();
//      logger.print (log_section_t::ENGINE, log_priority_t::INFO, "Finish thread:", std::this_thread::get_id ());
      i++;
      if (i > 3) {break;}
    }

  return 0;
}
