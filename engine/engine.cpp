#include "engine.h"

#include "common/logger/logger.h"
#include "datastructs/shader.h"
#include "gui/gui_context.h"
#include "gui/gui_system.h"
#include "renderer/renderer.h"
#include "resource/resource_manager.h"

engine_t::engine_t ():
  m_gui (std::make_unique<gui_system_t> (800, 600)),
  m_renderer (std::make_unique<renderer_t> (*this))
{
//  m_window.setMouseCursorGrabbed (true);
}

err_t engine_t::load_engine_resources ()
{
  // its okay to explicitly call resource manager here, since this shader does not belong to any object
  shader_t *tmp_shader = resource_manager::instance ().get_resource<shader_t> ("shaders/text.shader");

  auto &font = m_renderer->get_font ();
  font.set_text_shader (tmp_shader);

  return ERR_OK;
}

err_t engine_t::init ()
{
  RETURN_IF_FAIL (m_renderer->init ());

  m_gui->make_context ();

  if (!m_gui->is_ok ())
    return err_t ("GUI initialization error: no contexts exist!");

  RETURN_IF_FAIL (load_engine_resources ());

  logger_t::instance ().print (log_section_t::ENGINE, log_priority_t::INFO, "initialization complete!");

  return ERR_OK;
}

err_t engine_t::run ()
{
  return ERR_OK;
}

engine_t::~engine_t () = default;
