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

# Directories

HEADERS += \
    engine/engine.h \
    common/common.h \
