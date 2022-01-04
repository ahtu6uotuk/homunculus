#pragma once
#include "engine/gui/gui_system.h"
#include "engine/renderer/renderer.h"

class err_t;

class engine_t
{
  gui_system_t m_gui;
  renderer_t m_renderer;
private:
  err_t load_engine_resources ();
public:
  engine_t ();
  engine_t (const engine_t &) = delete;
  engine_t (engine_t &&) = delete;
  err_t init ();
  auto &get_renderer () {return m_renderer;}
  auto &get_gui_system () {return m_gui;}
  auto &get_sfml_window () {return m_renderer.get_window ();}
  void render_and_display ();
  ~engine_t ();
};
