#pragma once
#include <memory>

class game_t;
class err_t;

class application_t
{
  std::unique_ptr<game_t> m_game;
public:
  application_t (int argc, char **argv);
  int exec ();
  ~application_t ();
};

