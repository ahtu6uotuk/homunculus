CONFIG -= qt
CONFIG += link_pkgconfig
PKGCONFIG += freetype2
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -lGL -lpthread -lfreetype -lGLU

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
    logic/asset.cpp \
    logic/dialog.cpp \
    logic/object/interaction.cpp \
    logic/object/object_heap.cpp \
    logic/object_classes/enemy.cpp \
    logic/object_classes/friend.cpp \
    logic/object_classes/player.cpp \
    logic/plot_tag.cpp \
    logic/policies/plot_tags_policy.cpp \
    logic/policies/talk_policy.cpp \
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
    engine/gui/gui_text.cpp \
    engine/renderer/shader.cpp

# Directories

HEADERS += \
    common/file_utils.h \
    common/template_tricks/auto_register.h \
    common/template_tricks/comparator.h \
    common/template_tricks/static_for.h \
    common/template_tricks/string_literal.h \
    engine/engine.h \
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
    logic/object_classes/enemy.h \
    logic/object_classes/example_classes.h \
    logic/object_classes/friend.h \
    logic/object_classes/player.h \
    logic/plot_tag.h \
    logic/policies/plot_tags_policy.h \
    logic/policies/talk_policy.h \
    logic/saveload/saveload.h \
    logic/saveload/saveload_tree_fwd.h \
    logic/simulation/simulation.h \
    logic/simulation/simulation_helpers.h \
    logic/tests/logic_tests.h \
    logic/object/object.h \
    logic/object/object_base.h \
    logic/object/object_heap.h \
    logic/policies/health_policy.h \
    logic/policies/name_policy.h \
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
    engine/gui/gui_text.h \
    engine/renderer/shader.h

DISTFILES += \
    gamedata/shaders/text.vert \
    gamedata/shaders/text.frag
