﻿#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <thread>
#include <atomic>
#include "common/err_t.h"
#include "engine/logger.h"
#include "common/thread_sync.h"
#include "engine/gui/gui_system.h"
#include "engine/renderer/renderer.h"

class thread_info_t;
class event_t;
class gui_context_t;

class engine_t
{
  sf::RenderWindow m_window;
  logger_t m_logger;
  gui_system_t m_gui;
  renderer_t m_renderer;
private:
  err_t create_threads ();
  err_t run_gui_thread ();
  size_t get_computation_threads_number () const;
public:
  engine_t () = delete;
  engine_t (int argc, char *argv[]);
  engine_t (const engine_t &) = delete;
  engine_t (engine_t &&) = delete;
  err_t init ();
  auto &get_renderer () {return m_renderer;}
  auto &get_logger () {return m_logger;}
  auto &get_gui_system () {return m_gui;}
  auto &get_sfml_window () {return m_window;}
  void render_and_display (unique_ptr<gui_context_t> extra_content);
  optional<vector<event_t>> handle_events ();
  ~engine_t ();
};
