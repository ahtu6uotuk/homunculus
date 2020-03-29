#pragma once

#include "common/common.h"
#include "logic/object/object.h"
#include "objects/policies/camera_policy.h"
#include "objects/policies/get_text_for_gui_policy.h"
#include "objects/policies/name_policy.h"
#include "objects/policies/player_choose_action_policy.h"
#include "objects/policies/plot_tags_policy.h"

class player_t : public object<
                     player_t,
                     simple_name_policy,
                     simple_get_text_for_gui_policy,
                     simple_camera_policy,
                     player_choose_action_policy
                     >
{
public:
  static std::string objtype_name () { return "player"; }
};
