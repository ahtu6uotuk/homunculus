CONFIG -= qt
CONFIG += link_pkgconfig
CONFIG += console
PKGCONFIG += freetype2
LIBS += -lsfml-graphics -lsfml-window -lsfml-system  -lpthread -lfreetype

unix:LIBS += -lGLEW -lGL -lGLU
win32:LIBS += -lglew32 -lglu32 -lopengl32 -lssp

QMAKE_CXXFLAGS += -std=c++2a
QMAKE_CXXFLAGS += -g -lm -W -Wall -Wunused -Wcast-align -Werror \
                  -pedantic -pedantic-errors -fstack-protector-all \
                  -Wfloat-equal -Wpointer-arith -Wwrite-strings \
                  -Wcast-align -Wno-long-long -Wsuggest-override\
                  -Wmissing-declarations -Wnon-virtual-dtor \
                  -Wmissing-format-attribute -Wvla -Wformat=1 \
                  -Wno-maybe-uninitialized -Wuninitialized \
                  -Wlogical-op -Wno-unused-local-typedefs -Wshadow \
                  -Wextra  -Wformat-security -Wformat-nonliteral \

INCLUDEPATH += ./

HEADERS += common/common.h \
           common/err_t.h \
           common/file_utils.h \
           common/thread_info.h \
           common/thread_sync.h \
           common/type_traits_ext.h \
           control_flow/control_flow.h \
           control_flow/frame_manager.h \
           control_flow/handle_gui_events.h \
           control_flow/make_gui_content.h \
           control_flow/request_to_calc.h \
           control_flow/request_to_gui.h \
           control_flow/run_calc_thread.h \
           datastructs/camera_data_t.h \
           datastructs/dialog.h \
           datastructs/plot_tag.h \
           engine/engine.h \
           common/logger/logger.h \
           common/logger/logger_utils.h \
           object/interaction.h \
           object/object.h \
           object/object_base.h \
           object/object_heap.h \
           resource/asset.h \
           resource/resource_manager.h \
           tests/logic_tests.h \
           world/action.h \
           world/world.h \
           common/string/string_converters.h \
           common/string/string_utils.h \
           common/template_tricks/auto_register.h \
           common/template_tricks/comparator.h \
           common/template_tricks/has_member.h \
           common/template_tricks/static_for.h \
           common/template_tricks/string_literal.h \
           engine/gui/gui_context.h \
           engine/gui/gui_element.h \
           engine/gui/gui_interactive_element.h \
           engine/gui/gui_system.h \
           engine/gui/gui_textline.h \
           datastructs/io/model_obj.h \
           datastructs/io/tga_image.h \
           engine/renderer/camera.h \
           engine/renderer/font.h \
           datastructs/mesh.h \
           engine/renderer/renderer.h \
           datastructs/shader.h \
           datastructs/shader_fwd.h \
           datastructs/texture.h \
           datastructs/vertex_data.h \
           external/rapidxml/rapidxml.hpp \
           external/rapidxml/rapidxml_iterators.hpp \
           external/rapidxml/rapidxml_print.hpp \
           external/rapidxml/rapidxml_utils.hpp \
           resource/saveload/saveload.h \
           resource/saveload/saveload_fwd.h \
           resource/saveload/saveload_rules.h \
           resource/saveload/saveload_tree.h \
           tests/simulation/simulation.h \
           tests/simulation/simulation_helpers.h \
           world/classes/enemy.h \
           world/classes/example_classes.h \
           world/classes/friend.h \
           world/classes/player.h \
           datastructs/helpers/saveload_rules_extensions.h \
           world/policies/camera_policy.h \
           world/policies/choose_action_policy.h \
           world/policies/get_text_for_gui_policy.h \
           world/policies/health_policy.h \
           world/policies/name_policy.h \
           world/policies/player_choose_action_policy.h \
           world/policies/plot_tags_policy.h \
           world/policies/talk_policy.h \
           engine/renderer/gl/gl_ext.h
SOURCES += main.cpp \
           common/common.cpp \
           common/err_t.cpp \
           common/file_utils.cpp \
           common/thread_info.cpp \
           common/thread_sync.cpp \
           control_flow/control_flow.cpp \
           control_flow/frame_manager.cpp \
           control_flow/handle_gui_events.cpp \
           control_flow/make_gui_content.cpp \
           control_flow/request_to_calc.cpp \
           control_flow/request_to_gui.cpp \
           control_flow/run_calc_thread.cpp \
           datastructs/camera_data_t.cpp \
           datastructs/dialog.cpp \
           datastructs/plot_tag.cpp \
           engine/engine.cpp \
           common/logger/logger.cpp \
           common/logger/logger_utils.cpp \
           datastructs/texture.cpp \
           object/interaction.cpp \
           object/object_heap.cpp \
           resource/asset.cpp \
           resource/resource_manager.cpp \
           tests/asset_test.cpp \
           tests/object_heap_test.cpp \
           tests/plot_tag_set_test.cpp \
           tests/saveload_tree_test.cpp \
           world/action.cpp \
           world/world.cpp \
           common/string/string_converters.cpp \
           common/string/string_utils.cpp \
           engine/gui/gui_context.cpp \
           engine/gui/gui_element.cpp \
           engine/gui/gui_interactive_element.cpp \
           engine/gui/gui_system.cpp \
           engine/gui/gui_textline.cpp \
           datastructs/io/model_obj.cpp \
           datastructs/io/tga_image.cpp \
           engine/renderer/camera.cpp \
           engine/renderer/font.cpp \
           datastructs/mesh.cpp \
           engine/renderer/renderer.cpp \
           datastructs/shader.cpp \
           datastructs/vertex_data.cpp \
           resource/saveload/saveload_tree.cpp \
           tests/simulation/simulation.cpp \
           tests/simulation/simulation_helpers.cpp \
           world/classes/enemy.cpp \
           world/classes/friend.cpp \
           world/classes/player.cpp \
           world/policies/camera_policy.cpp \
           world/policies/choose_action_policy.cpp \
           world/policies/get_text_for_gui_policy.cpp \
           world/policies/player_choose_action_policy.cpp \
           world/policies/plot_tags_policy.cpp \
           world/policies/talk_policy.cpp \
           engine/renderer/gl/gl_ext.cpp


DISTFILES += \
    gamedata/shaders/text.vert \
    gamedata/shaders/text.frag \
    gamedata/shaders/default.vert \
    gamedata/shaders/test_simple.frag
