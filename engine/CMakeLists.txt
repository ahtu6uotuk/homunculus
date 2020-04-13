cmake_minimum_required(VERSION 2.8.0)

project(engine)

# Try to find Freetype2 library
include(FindFreetype)
if (NOT FREETYPE_FOUND)
  message (FATAL_ERROR "Freetype library not found!")
endif()

find_library (SFML_GRAPHICS_LIBRARY NAMES sfml-graphics)
find_library (SFML_WINDOW_LIBRARY NAMES sfml-window)
find_library (SFML_SYSTEM_LIBRARY NAMES sfml-system)

if (NOT SFML_GRAPHICS_LIBRARY)
    message (FATAL_ERROR "SFML Graphics library not found!")
endif ()
if (NOT SFML_WINDOW_LIBRARY)
    message (FATAL_ERROR "SFML Window library not found!")
endif ()
if (NOT SFML_SYSTEM_LIBRARY)
    message (FATAL_ERROR "SFML System library not found!")
endif ()

add_library (${PROJECT_NAME} STATIC)

target_sources (${PROJECT_NAME} PRIVATE
                engine.cpp
                gui/gui_context.cpp
                gui/gui_element.cpp
                gui/gui_interactive_element.cpp
                gui/gui_system.cpp
                gui/gui_textline.cpp
                renderer/gl/gl_ext.cpp
                renderer/camera.cpp
                renderer/font.cpp
                renderer/renderer.cpp)

set (RENDERER_LIBRARIES
     GLEW::GLEW
    ${OPENGL_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    datastructs)

target_include_directories (${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${RENDERER_LIBRARIES})
