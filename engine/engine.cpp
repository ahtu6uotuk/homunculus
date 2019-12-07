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

int engine_t::init ()
{
  if (!m_logger.is_ok ())
    return -1;

  return 0;
}

int engine_t::exec ()
{
  if (auto ret = init ())
    return ret;

  return 0;
}

engine_t::~engine_t ()
{

}
