#include "engine.h"

#include <SFML/Window.hpp>

#include "common/logger/logger.h"
#include "engine/gui/gui_element.h"
#include "engine/gui/gui_textline.h"
#include "gui/gui_context.h"
#include "resource/resource_manager.h"
#include "datastructs/shader.h"

engine_t::engine_t (int argc, char *argv[]):
  m_window (sf::VideoMode (800, 600, 32), "Homunculus", sf::Style::Default,
            sf::ContextSettings (0, 0, 0, 3, 3, sf::ContextSettings::Attribute::Core)),
  m_gui (800, 600),
  m_renderer (*this)
{
  do_nothing (argc, argv);
  m_window.setFramerateLimit (60);
}

err_t engine_t::load_engine_resources ()
{
  // its okay to explicitly call resource manager here, since this shader does not belong to any object
  shader_t *tmp_shader = resource_manager::instance ().get_resource<shader_t> ("shaders/text.shader");

  auto &font = m_renderer.get_font ();
  font.set_text_shader (tmp_shader);

  return ERR_OK;
}

err_t engine_t::init ()
{
  RETURN_IF_FAIL (m_renderer.init ());

  m_gui.make_context ();
  gui_context_t *context = m_gui.get_active_context ();
  std::unique_ptr<gui_textline_t> performance_indicator =
      std::make_unique<gui_textline_t> (get_renderer (),
                                        10, 10, gui_horizontal_alignment_t::LEFT,
                                        gui_vertical_alignment_t::DOWN, "",
                                        glm::vec3 (.7f, .15f, .15f), 24);
  m_performance_indicator = performance_indicator.get ();
  context->add_element (move (performance_indicator));

  if (!m_gui.is_ok ())
    return err_t ("GUI initialization error: no contexts exist!");

  RETURN_IF_FAIL (load_engine_resources ());

  logger_t::instance ().print (log_section_t::ENGINE, log_priority_t::INFO, "initialization complete!");

  return ERR_OK;
}

void engine_t::render_and_display ()
{
  m_renderer.render ();
  m_window.display ();
}

engine_t::~engine_t ()
{}
