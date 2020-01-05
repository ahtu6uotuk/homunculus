#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>
#include "common/err_t.h"
#include "engine/logger.h"
#include "common/thread_sync.h"
#include "engine/gui/gui_system.h"
#include "engine/renderer/renderer.h"

class thread_info_t;


class engine_t
{
  sf::RenderWindow m_window;
  logger_t m_logger;
  std::vector<thread> m_thread;
  thread_sync_t m_thread_sync;
  bool m_run;
  gui_system_t m_gui;
  renderer_t m_renderer;
private:
  err_t init ();
  err_t create_threads ();
  err_t run_gui_thread ();
  void handle_events ();
  size_t get_computation_threads_number () const;
public:
  engine_t () = delete;
  engine_t (int argc, char *argv[]);
  engine_t (const engine_t &) = delete;
  engine_t (engine_t &&) = delete;
  int exec ();
  bool is_running () const {return m_run;}
  auto &get_logger () {return m_logger;}
  ~engine_t ();
};

int run_computation_thread (unique_ptr<thread_info_t> thr_info, engine_t &engine);
