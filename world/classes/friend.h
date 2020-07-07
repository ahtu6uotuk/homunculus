#pragma once

#include "datastructs/dialog.h"
#include "object/object.h"
#include "world/policies/get_text_for_gui_policy.h"
#include "world/policies/health_policy.h"
#include "world/policies/name_policy.h"
#include "world/policies/plot_tags_policy.h"
#include "world/policies/talk_policy.h"

#include "world/policies/shader_policy.h"
#include "world/policies/mesh_policy.h"
#include "world/policies/texture_policy.h"
#include "world/policies/position_policy.h"

enum class mood { happy, sad, melancholic, COUNT };
const char *enum_to_string (mood m);
enum class bloodtype { o, a, b, ab, COUNT };
const char *enum_to_string (bloodtype m);

typedef plot_tag_set<
    named_enum<LITERAL ("mood"), mood>,
    named_enum<LITERAL ("blood_type"), bloodtype>>
    generic_propset;

class friend_t
  : public object<
        friend_t,
        simple_name_policy,
        simple_get_text_for_gui_policy,
        simple_plot_tags_policy<named_enum<LITERAL ("mood"), mood>, named_enum<LITERAL ("blood_type"), bloodtype>>,
        simple_talk_policy<LITERAL ("assets/some_dialog.xml")>,
        // perhaps these three should be merged into one policy, its not even hard
        simple_shader_policy<LITERAL("shaders/test.shader")>,
        simple_mesh_policy<LITERAL("models/cube.obj")>,
        simple_texture_policy<LITERAL("textures/cube_friend.tga")>,
        position_policy_t
        >
{
public:
  static std::string objtype_name () { return "friend"; }
};
