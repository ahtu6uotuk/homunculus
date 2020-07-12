#pragma once

#include "common/common.h"
#include "object/object.h"
#include "world/policies/camera_policy.h"
#include "world/policies/get_text_for_gui_policy.h"
#include "world/policies/name_policy.h"
#include "world/policies/player_choose_action_policy.h"
#include "world/policies/plot_tags_policy.h"
#include "world/policies/position_policy.h"
#include "world/policies/get_focus_policy.h"

class player_t : public object<
                     player_t,
                     simple_name_policy,
                     simple_get_text_for_gui_policy,
                     simple_camera_policy,
                     position_policy_t,
                     player_choose_action_policy,
                     simple_get_focus_policy
                     >
{
public:
  static std::string objtype_name () { return "player"; }
};
