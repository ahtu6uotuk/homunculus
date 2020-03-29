#pragma once

#include "common/err_t.h"
#include "engine/renderer/camera.h"
#include "engine/renderer/font.h"
#include "datastructs/texture.h"

class engine_t;
class gui_system_t;
class mesh_t;

namespace sf
{
  class RenderWindow;
}

class renderer_t
{
  engine_t &m_engine;
  sf::RenderWindow &m_window;
  gui_system_t &m_gui;
  font_t m_font;
  camera_t m_camera;

  shader_t *m_test_shader = nullptr;
  mesh_t *m_test_mesh = nullptr;
  texture_t *m_tex = nullptr;
public:
  renderer_t (engine_t &engine);
  err_t init ();
  void render ();
  font_t &get_font () {return m_font;}
  gui_system_t &get_gui () {return m_gui;}
  camera_t &get_camera () {return m_camera;}
  void set_mesh (mesh_t *test, shader_t *shader, texture_t *tex);
  ~renderer_t ();
};
