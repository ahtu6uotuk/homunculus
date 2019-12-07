#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "engine/logger.h"

class engine_t
{
  sf::RenderWindow m_window;
  logger_t m_logger;
private:
  int init ();
public:
  engine_t () = delete;
  engine_t (int argc, char *argv[]);
  engine_t (const engine_t &) = delete;
  engine_t (engine_t &&) = delete;
  int exec ();
  ~engine_t ();
};
