#pragma once
#include <memory>

class err_t;
class thread_manager_t;
class gui_system_t;
class renderer_t;

class engine_t
{
  std::unique_ptr<thread_manager_t> m_thread_manager;
  std::unique_ptr<gui_system_t> m_gui;
  std::unique_ptr<renderer_t> m_renderer;
private:
  err_t load_engine_resources ();
public:
  engine_t ();
  engine_t (const engine_t &) = delete;
  engine_t (engine_t &&) = delete;
  err_t init ();
  auto &get_gui_system () { return *m_gui; }
  err_t run ();
  ~engine_t ();
};
