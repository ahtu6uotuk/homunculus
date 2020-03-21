#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "common/err_t.h"
#include "engine/logger.h"
#include "engine/io/resource_manager.h"
#include "engine/gui/gui_system.h"
#include "engine/renderer/renderer.h"

class thread_info_t;
class gui_context_t;
class gui_textline_t;

class engine_t
{
  sf::RenderWindow m_window;
  logger_t m_logger;
  resource_manager_t m_resource_manager;
  gui_system_t m_gui;
  renderer_t m_renderer;
  gui_textline_t *m_performance_indicator;
private:
  err_t load_engine_resources ();
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
  auto &get_performance_indicator () {return m_performance_indicator;}
  void render_and_display ();
  ~engine_t ();
};
