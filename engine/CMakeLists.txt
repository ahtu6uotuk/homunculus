project(engine)

add_subdirectory (gui)
add_subdirectory (renderer)

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
                engine.cpp)

set (RENDERER_LIBRARIES
     GLEW::GLEW
    ${OPENGL_LIBRARIES}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    datastructs)

target_link_libraries (${PROJECT_NAME} ${RENDERER_LIBRARIES} gui renderer)
