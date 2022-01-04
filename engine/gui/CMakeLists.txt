project (gui)

add_library (${PROJECT_NAME} STATIC)

target_sources (${PROJECT_NAME} PRIVATE
                gui_context.cpp
                widgets/gui_element.cpp
                widgets/gui_interactive_element.cpp
                gui_system.cpp
                widgets/gui_textline.cpp)
