#pragma once
#include <memory>

class engine_t;
class game_t;
class err_t;

class game_t
{
  engine_t &m_engine;
public:
  game_t (engine_t &engine);
  err_t run ();
  ~game_t ();
};

