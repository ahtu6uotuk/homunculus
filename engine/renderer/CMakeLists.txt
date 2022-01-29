project (renderer)

# Try to find Freetype2 library
include(FindFreetype)
if (NOT FREETYPE_FOUND)
  message (FATAL_ERROR "Freetype library not found!")
endif()

add_library (${PROJECT_NAME} STATIC)

target_include_directories (${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})

target_sources (${PROJECT_NAME} PRIVATE
                gl/gl_ext.cpp
                camera.cpp
                camera.h
                font.cpp
                font.h
                scene.cpp
                scene.h
                renderer.cpp
                renderer.h
                renderer_type.cpp
                renderer_type.h)

target_link_libraries (${PROJECT_NAME} ${FREETYPE_LIBRARIES} GLEW::GLEW ${OPENGL_LIBRARIES} datastructs)
