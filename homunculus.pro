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

SOURCES += \
    common/file_utils.cpp \
    common/string/string_utils.cpp \
    control_flow/control_flow.cpp \
    control_flow/frame_manager.cpp \
    control_flow/handle_gui_events.cpp \
    control_flow/make_gui_content.cpp \
    control_flow/request_to_calc.cpp \
    control_flow/request_to_gui.cpp \
    control_flow/run_calc_thread.cpp \
    engine/event.cpp \
    logic/asset.cpp \
    logic/dialog.cpp \
    logic/object/interaction.cpp \
    logic/object/object_heap.cpp \
    objects/object_classes/enemy.cpp \
    objects/object_classes/friend.cpp \
    objects/object_classes/player.cpp \
    logic/plot_tag.cpp \
    objects/policies/choose_action_policy.cpp \
    objects/policies/coordinates_policy.cpp \
    objects/policies/get_text_for_gui_policy.cpp \
    objects/policies/player_choose_action_policy.cpp \
    objects/policies/plot_tags_policy.cpp \
    objects/policies/talk_policy.cpp \
    logic/action.cpp \
    logic/simulation/simulation.cpp \
    logic/simulation/simulation_helpers.cpp \
    logic/tests/asset_test.cpp \
    logic/tests/object_heap_test.cpp \
    logic/tests/plot_tag_set_test.cpp \
    logic/world.cpp \
    main.cpp \
    engine/engine.cpp \
    common/common.cpp \
    common/err_t.cpp \
    common/string/string_converters.cpp \
    logic/saveload/saveload_tree.cpp \
    logic/tests/saveload_tree_test.cpp \
    engine/logger.cpp \
    common/thread_info.cpp \
    common/thread_sync.cpp \
    engine/renderer/renderer.cpp \
    engine/gui/gui_context.cpp \
    engine/gui/gui_element.cpp \
    engine/gui/gui_interactive_element.cpp \
    engine/gui/gui_system.cpp \
    engine/renderer/font.cpp \
    engine/gui/gui_textline.cpp \
    engine/renderer/shader.cpp \
    engine/renderer/mesh.cpp \
    engine/io/model_obj.cpp \
    engine/renderer/vertex_data.cpp \
    engine/io/tga_image.cpp \
    engine/logger_utils.cpp \
    engine/renderer/camera.cpp \
    engine/io/resource_manager.cpp \
    engine/renderer/gl/gl_ext.cpp
# Directories

HEADERS += \
    common/file_utils.h \
    common/template_tricks/auto_register.h \
    common/template_tricks/comparator.h \
    common/template_tricks/static_for.h \
    common/template_tricks/string_literal.h \
    control_flow/control_flow.h \
    control_flow/event.h \
    control_flow/frame_manager.h \
    control_flow/handle_gui_events.h \
    control_flow/make_gui_content.h \
    control_flow/request_to_calc.h \
    control_flow/request_to_gui.h \
    control_flow/run_calc_thread.h \
    engine/engine.h \
    engine/event.h \
    common/common.h \
    common/err_t.h \
    external/rapidxml/rapidxml.hpp \
    external/rapidxml/rapidxml_iterators.hpp \
    external/rapidxml/rapidxml_print.hpp \
    external/rapidxml/rapidxml_utils.hpp \
    common/string/string_converters.h \
    logic/asset.h \
    logic/dialog.h \
    logic/object/interaction.h \
    objects/object_classes/enemy.h \
    objects/object_classes/example_classes.h \
    objects/object_classes/friend.h \
    objects/object_classes/player.h \
    logic/plot_tag.h \
    objects/policies/choose_action_policy.h \
    objects/policies/coordinates_policy.h \
    objects/policies/get_text_for_gui_policy.h \
    objects/policies/player_choose_action_policy.h \
    objects/policies/plot_tags_policy.h \
    objects/policies/talk_policy.h \
    logic/action.h \
    logic/saveload/saveload.h \
    logic/saveload/saveload_tree_fwd.h \
    logic/simulation/simulation.h \
    logic/simulation/simulation_helpers.h \
    logic/tests/logic_tests.h \
    logic/object/object.h \
    logic/object/object_base.h \
    logic/object/object_heap.h \
    objects/policies/health_policy.h \
    objects/policies/name_policy.h \
    logic/saveload/saveload_tree.h \
    common/string/string_utils.h \
    engine/logger.h \
    common/thread_info.h \
    common/thread_sync.h \
    engine/renderer/renderer.h \
    engine/gui/gui_context.h \
    engine/gui/gui_element.h \
    engine/gui/gui_interactive_element.h \
    engine/gui/gui_system.h \
    engine/renderer/font.h \
    logic/world.h \
    engine/gui/gui_textline.h \
    engine/renderer/shader.h \
    engine/renderer/mesh.h \
    engine/renderer/texture.h \
    engine/io/model_obj.h \
    engine/renderer/vertex_data.h \
    engine/io/tga_image.h \
    engine/logger_utils.h \
    engine/renderer/camera.h \
    common/type_traits_ext.h \
    engine/io/resource_manager.h \
    engine/renderer/shader_fwd.h \
    engine/renderer/gl/gl_ext.h

DISTFILES += \
    gamedata/shaders/text.vert \
    gamedata/shaders/text.frag \
    gamedata/shaders/default.vert \
    gamedata/shaders/test_simple.frag
