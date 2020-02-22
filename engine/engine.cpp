#include "engine.h"

#include <SFML/Window.hpp>

#include "engine/event.h"
#include "gui/gui_context.h"

engine_t::engine_t (int argc, char *argv[]):
  m_window (sf::VideoMode (800, 600, 32), "Homunculus", sf::Style::Default,
            sf::ContextSettings (0, 0, 0, 3, 3, sf::ContextSettings::Attribute::Core)),
  m_logger ("engine.log"),
  m_gui (800, 600),
  m_renderer (*this)
{
  do_nothing (argc, argv);
  m_window.setFramerateLimit (60);
  m_logger.print (log_section_t::ENGINE, log_priority_t::INFO, "initialization complete!");
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

  if (!m_gui.is_ok ())
    return err_t ("GUI initialization error: no contexts exist!");

  return ERR_OK;
}

void engine_t::render_and_display (unique_ptr<gui_context_t> extra_content)
{
  m_renderer.render (move (extra_content));
  m_window.display ();
}

optional<vector<event_t>> engine_t::handle_events ()
{
  optional<vector<event_t>> result = vector<event_t>();

  sf::Event event;
  while (m_window.pollEvent (event))
    {
      switch (event.type)
        {
        case sf::Event::EventType::Closed:
          {
            result = nullopt;
            break;
          }
        case sf::Event::EventType::Resized:
          {
            m_gui.resize (event.size.width, event.size.height);
            break;
          }
        case sf::Event::EventType::MouseMoved:
          {
            m_gui.handle_mouse_move_event (event.mouseMove.x, event.mouseMove.y);
            break;
          }
        case sf::Event::EventType::MouseButtonPressed:
          {
            if (event.mouseButton.button == sf::Mouse::Left)
              m_gui.handle_mouse_press_event (event.mouseButton.x, event.mouseButton.y);
            break;
          }
        case sf::Event::EventType::MouseButtonReleased:
          {
            break;
          }
        case sf::Event::EventType::KeyPressed:
          {
            do_nothing ();
            break;
          }
        case sf::Event::EventType::KeyReleased:
          {
            do_nothing ();
            break;
          }
        default:
          {
            do_nothing ();
          }
        }
    }
  return result;
}

engine_t::~engine_t ()
{}
