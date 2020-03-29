#pragma once

#include <queue>

#include "logic/action.h"
#include "objects/policies/choose_action_policy.h"

class player_choose_action_policy : public choose_action_policy
{
public:
  std::string policy_describe () const override
  {
    return string_printf ("Choosing action according to keyboard input");
  }
  void policy_build_saveload_tree (saveload::node_t &) override {}
  bool operator== (const player_choose_action_policy &) const { return true; }

  std::unique_ptr<action> get_action (world_t &) override
  {
    if (m_buffered_actions.empty ())
      return std::make_unique<no_action> ();

    std::unique_ptr<action> res = std::move (m_buffered_actions.front ());
    m_buffered_actions.pop ();
    return res;
  }

  void add_buffered_action (std::unique_ptr<action> action)
  {
    m_buffered_actions.push (std::move (action));
  }

private:
  std::queue<std::unique_ptr<action>> m_buffered_actions;
};
