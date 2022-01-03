project (gui)

add_library (${PROJECT_NAME} STATIC)

target_sources (${PROJECT_NAME} PRIVATE
                gui_context.cpp
                gui_element.cpp
                gui_interactive_element.cpp
                gui_system.cpp
                gui_textline.cpp)
