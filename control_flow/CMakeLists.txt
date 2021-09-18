project(control_flow)

add_library(${PROJECT_NAME} STATIC
            control_flow.cpp
            frame_manager.cpp
            handle_gui_events.cpp
            make_gui_content.cpp
            request_to_calc.cpp
            request_to_gui.cpp
            run_calc_thread.cpp)

include(FindThreads)
if (NOT THREADS_FOUND)
  message (FATAL_ERROR "Can't find threads library!")
endif ()

target_link_libraries(${PROJECT_NAME} engine world ${CMAKE_THREAD_LIBS_INIT})
