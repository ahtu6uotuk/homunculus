#include "application.h"

#include "common/common.h"
#include "common/err_t.h"
#include "common/logger/logger.h"
#include "engine/engine.h"
#include "game/game.h"

application_t::application_t (int argc, char **argv):
  m_game (std::make_unique<game_t> ())
{
  do_nothing (argc, argv);
}

int application_t::exec ()
{
  auto &logger = logger_t::instance ();
  if (!logger.is_ok ())
    {
      std::cout << "Internal engine error: logger init failed." << std::endl;
      return 1;
    }

  auto err = m_game->run ();
  if (err)
    logger.print_plain (err.descr ());

  return 0;
}

application_t::~application_t () = default;
