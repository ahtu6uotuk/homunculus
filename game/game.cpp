#include "game.h"

#include "engine/engine.h"

game_t::game_t (engine_t &engine):
  m_engine (engine)
{

}

err_t game_t::run ()
{
  RETURN_IF_FAIL (m_engine.init ());

  RETURN_IF_FAIL (m_engine.run ());

  return ERR_OK;
}

game_t::~game_t () = default;
