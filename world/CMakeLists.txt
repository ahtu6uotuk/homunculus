project(world)

add_library(${PROJECT_NAME} STATIC
            classes/enemy.cpp
            classes/friend.cpp
            classes/dialog_partner.cpp
            classes/player.cpp
            classes/example_classes.cpp
            policies/camera_policy.cpp
            policies/choose_action_policy.cpp
            policies/get_text_for_gui_policy.cpp
            policies/player_choose_action_policy.cpp
            policies/plot_tags_policy.cpp
            policies/talk_policy.cpp
            action.cpp
            policies/mesh_policy.cpp
            policies/shader_policy.cpp
            policies/texture_policy.cpp
            policies/position_policy.cpp
            policies/get_focus_policy.cpp
            world.cpp)

target_link_libraries (${PROJECT_NAME} object)
