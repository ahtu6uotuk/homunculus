#pragma once
#include <memory>

class engine_t;
class game_t;
class err_t;

class application_t
{
  std::unique_ptr<engine_t> m_engine;
  std::unique_ptr<game_t> m_game;
public:
  application_t (int argc, char **argv);
  int exec ();
  ~application_t ();
};

