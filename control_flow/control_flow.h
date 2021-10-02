#pragma once

#include <atomic>
#include <vector>
#include <thread>
#include <optional>
#include "common/common.h"
#include "common/err_t.h"
class engine_t;
class world_t;
class err_t;
class thread_sync_t;
class thread_info_t;
class gui_context_t;
class request_to_calc_base;
class request_to_gui_base;
class frame_manager;

class control_flow
{
public:
  ~control_flow ();
  control_flow ();
  err_t run ();

private:
  err_t init ();
  err_t create_threads ();
  static std::unique_ptr<gui_context_t> make_gui_content (engine_t &engine, world_t &world);

private:
  std::unique_ptr<engine_t> m_engine;
  std::unique_ptr<world_t> m_world;

  std::unique_ptr<frame_manager> m_frame_manager;

  std::vector<std::unique_ptr<request_to_calc_base>> m_old_request_to_calc;
  std::vector<std::unique_ptr<request_to_gui_base>> m_old_request_to_gui;
  std::vector<std::unique_ptr<request_to_calc_base>> m_new_request_to_calc;
  std::vector<std::unique_ptr<request_to_gui_base>> m_new_request_to_gui;

  std::vector<std::jthread> m_threads;
  std::unique_ptr<thread_sync_t> m_sync;
  std::unique_ptr<thread_sync_t> m_sync_w_main;

  err_t m_next_frame_error = ERR_OK;

  friend void run_calc_thread (std::unique_ptr<thread_info_t> , control_flow &);
};
