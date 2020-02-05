﻿#pragma once

#include <atomic>
#include <vector>
#include <thread>
#include <optional>
#include "common/common.h"
#include "common/err_t.h"
class engine_t;
class world_t;
class err_t;
class event_t;
class thread_sync_t;
class thread_info_t;
class gui_context_t;

class control_flow
{
public:
  ~control_flow ();
  control_flow (int argc, char **argv);
  err_t run ();

private:
  err_t init ();
  err_t create_threads ();
  void join_threads ();
  size_t get_calc_threads_number () const;
  static unique_ptr<gui_context_t> make_gui_content (engine_t &engine, world_t &world);

private:
  unique_ptr<engine_t> m_engine;
  unique_ptr<world_t> m_world;

  optional<vector<event_t>> m_old_events;
  unique_ptr<gui_context_t> m_old_gui_content;
  optional<vector<event_t>> m_new_events;
  unique_ptr<gui_context_t> m_new_gui_content;

  std::vector<thread> m_threads;
  unique_ptr<thread_sync_t> m_sync;
  unique_ptr<thread_sync_t> m_sync_w_main;

  err_t m_next_frame_error = ERR_OK;

  int m_argc;
  char ** m_argv;

  friend void run_calc_thread (unique_ptr<thread_info_t> , control_flow &);
};