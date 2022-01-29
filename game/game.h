#pragma once
#include <memory>

class engine_t;
class err_t;
class game_settings_t;

class game_t
{
  std::unique_ptr<engine_t> m_engine;
  std::unique_ptr<game_settings_t> m_settings;
private:
public:
  game_t ();
  err_t run ();
  ~game_t ();
};

