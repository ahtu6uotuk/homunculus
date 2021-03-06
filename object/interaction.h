#pragma once

#include <functional>

#include "common/common.h"
class object_base;

/// It is highly likely that this class will not be used in the final version of the game.
/// However, for now I will use it to test the world with no graphics.

class interaction
{
public:
  interaction (const std::string &name, std::function<void (object_base &player_character)> interact_func)
    : m_name (name), m_interact_func (interact_func)
  {
  }
  void interact (object_base &player_character) { m_interact_func (player_character); }
  const std::string &get_name () const { return m_name; }

private:
  std::string m_name;
  std::function<void (object_base &player_character)> m_interact_func;
};
