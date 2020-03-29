#include "engine.h"

#include <SFML/Window.hpp>

#include "engine/event.h"
#include "gui/gui_context.h"
#include "engine/gui/gui_element.h"
#include "engine/gui/gui_textline.h"

engine_t::engine_t (int argc, char *argv[]):
  m_window (sf::VideoMode (800, 600, 32), "Homunculus", sf::Style::Default,
            sf::ContextSettings (0, 0, 0, 3, 3, sf::ContextSettings::Attribute::Core)),
  m_logger ("engine.log"),
//  m_resource_manager (m_logger),
  m_gui (800, 600),
  m_renderer (*this)
{
  do_nothing (argc, argv);
  m_window.setFramerateLimit (60);
}

err_t engine_t::load_engine_resources ()
{
  shader_t *tmp_shader = nullptr;
//  RETURN_IF_FAIL (m_resource_manager.load_shader ("text.shader", &tmp_shader));

  auto &font = m_renderer.get_font ();
  font.set_text_shader (tmp_shader);

  mesh_t *msh = nullptr;
//  RETURN_IF_FAIL (m_resource_manager.load_mesh ("cube.obj", &msh));

//  RETURN_IF_FAIL (m_resource_manager.load_shader ("test.shader", &tmp_shader));

  unsigned int tex;
//  RETURN_IF_FAIL (m_resource_manager.load_tga_texture ("cube.tga", tex));
  tex = 0;

  m_renderer.set_mesh (m_logger, msh, tmp_shader, tex);

  return ERR_OK;
}

err_t engine_t::init ()
{
  if (!m_logger.is_ok ())
    return err_t ("Internal logger error");

  RETURN_IF_FAIL (m_renderer.init ());

  // TODO: remove this block
  m_gui.make_context ();
  gui_context_t *context = m_gui.get_active_context ();
  context->add_test_page (m_renderer);

  std::unique_ptr<gui_textline_t> performance_indicator = std::make_unique<gui_textline_t> (
      get_renderer (), 10, 0,
      gui_horizontal_alignment_t::LEFT, gui_vertical_alignment_t::UP,
      "", glm::vec3 (.7f, .15f, .15f), 24);
  m_performance_indicator = performance_indicator.get ();
  context->add_element (move (performance_indicator));

  if (!m_gui.is_ok ())
    return err_t ("GUI initialization error: no contexts exist!");

  RETURN_IF_FAIL (load_engine_resources ());

  m_logger.print (log_section_t::ENGINE, log_priority_t::INFO, "initialization complete!");

  return ERR_OK;
}

void engine_t::render_and_display ()
{
  m_renderer.render ();
  m_window.display ();
}

engine_t::~engine_t ()
{}
