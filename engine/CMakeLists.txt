cmake_minimum_required(VERSION 2.8.0)

project(engine)

# Try to find Freetype2 library
include(FindFreetype)
if (NOT FREETYPE_FOUND)
  message (FATAL_ERROR "Freetype library not found!")
endif()

set (OpenGL_GL_PREFERENCE LEGACY)
include (FindOpenGL)
if (NOT OpenGL_OpenGL_FOUND)
  message (FATAL_ERROR "OpenGL libraries not found!")
endif ()
if (NOT OPENGL_GLU_FOUND)
  message (FATAL_ERROR "GLU libraries not found!")
endif ()
include (FindGLEW)
if (NOT GLEW_FOUND)
  message (FATAL_ERROR "GLEW library not found!")
endif ()

find_library (SFML_GRAPHICS_LIBRARY NAMES sfml-graphics)
find_library (SFML_WINDOW_LIBRARY NAMES sfml-window)
find_library (SFML_SYSTEM_LIBRARY NAMES sfml-system)

# Platform-specific libraries
if (WIN32)
  find_library (LSSP_LIBRARY, lssp)
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
    ${FREETYPE_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    datastructs)

if (LSSP_LIBRARY)
  set (RENDERER_LIBRARIES ${RENDERER_LIBRARIES} ${LSSP_LIBRARY})
endif ()

target_link_libraries (${PROJECT_NAME} ${RENDERER_LIBRARIES})
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR} ${FREETYPE_INCLUDE_DIRS})
