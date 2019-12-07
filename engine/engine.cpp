#include "engine.h"
#include "common/common.h"
#include <SFML/Window.hpp>

engine_t::engine_t (int argc, char *argv[]):
  m_window (sf::VideoMode::getDesktopMode (), "Homunculus"),
  m_logger ("engine.log")
{
  do_nothing (argc, argv);
  m_window.setFramerateLimit (60);
  m_logger.print (log_section_t::ENGINE, log_priority_t::INFO, "initialization complete!");
}

int engine_t::exec ()
{
  while (m_window.isOpen ())
    {
      sf::Event event;
      while (m_window.pollEvent (event))
        {
          if (event.type == sf::Event::Closed)
            m_window.close ();
        }
      uint8_t color = (time (nullptr) * 100) % 255;
      m_window.clear (sf::Color (color, color, color));
      m_window.display ();
    }
  return 0;
}

engine_t::~engine_t ()
{

}
