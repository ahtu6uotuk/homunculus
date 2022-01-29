#include "game.h"
#include "game_settings.h"
#include "common/err_t.h"
#include "engine/engine.h"

game_t::game_t () : m_engine (std::make_unique<engine_t> ()) {}

err_t game_t::run ()
{
  RETURN_IF_FAIL (m_engine->init ());
  return m_engine->run ();
}

game_t::~game_t () = default;
