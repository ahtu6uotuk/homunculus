cmake_minimum_required(VERSION 2.8.0)

project(engine)

# Try to find Freetype2 library
include(FindFreetype)

if(!FREETYPE_FOUND)
	message("Freetype library not found!")
	exit()
endif()

# Platform-specific libraries
if (UNIX)
	find_library(GLEW_LIBRARY NAMES GLEW)
	find_library(GL_LIBRARY NAMES GL)
	find_library(GLU_LIBRARY NAMES GLU)
	set(PLATFORM_SPECIFIC_LIBRARIES ${GL_LIBRARY} ${GLU_LIBRARY} ${GLEW_LIBRARY})
elseif (WIN32)
	find_library(GLEW_LIBRARY, glew32)
	find_library(GL_LIBRARY, gl32)
	find_library(GLU_LIBRARY, glu32)
	find_library(LSSP_LIBRARY, lssp)
	set(PLATFORM_SPECIFIC_LIBRARIES ${GL_LIBRARY} ${GLU_LIBRARY} ${GLEW_LIBRARY} ${LSSP_LIBRARY})
endif()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
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

target_link_libraries(${PROJECT_NAME}
                      ${FREETYPE_LIBRARIES}
                      ${SFML_GRAPHICS_LIBRARY}
                      ${SFML_WINDOW_LIBRARY}
                      ${SFML_SYSTEM_LIBRARY}
                      ${PLATFORM_SPECIFIC_LIBRARIES}
                      datastructs)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR} ${FREETYPE_INCLUDE_DIRS})
