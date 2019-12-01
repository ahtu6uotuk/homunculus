#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics/RenderWindow.hpp>


class engine_t
{
  sf::RenderWindow m_window;
public:
  engine_t () = delete;
  engine_t (int argc, char *argv[]);
  engine_t (const engine_t &) = delete;
  engine_t (engine_t &&) = delete;
  int exec ();
  ~engine_t ();
};

#endif // ENGINE_H
