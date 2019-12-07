CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -lGL
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -g -W -Wall -Wunused -Wcast-align -Werror \
                  -pedantic -pedantic-errors -fstack-protector-all \
                  -Wfloat-equal -Wpointer-arith -Wwrite-strings \
                  -Wcast-align -Wno-long-long \
                  -Wmissing-declarations -lm
INCLUDEPATH += ./

SOURCES += \
    main.cpp \
    engine/engine.cpp \
    common/common.cpp \
    common/err_t.cpp \
    external/rapidxml_helpers/rapidxml_wrapper.cpp \
    common/string_converters.cpp \
    logic/saveload_tree.cpp \
    logic/saveload_tree_test.cpp \
    common/string_utils.cpp \
    engine/logger.cpp

# Directories

HEADERS += \
    engine/engine.h \
    common/common.h \
    common/err_t.h \
    external/rapidxml/rapidxml.hpp \
    external/rapidxml/rapidxml_iterators.hpp \
    external/rapidxml/rapidxml_print.hpp \
    external/rapidxml/rapidxml_utils.hpp \
    external/rapidxml_helpers/rapidxml_wrapper.h \
    common/string_converters.h \
    logic/saveload_tree.h \
    logic/saveload_tree_test.h \
    common/string_utils.h \
    engine/logger.h
