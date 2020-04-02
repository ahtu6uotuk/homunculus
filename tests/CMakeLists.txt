cmake_minimum_required(VERSION 2.8.0)

project(homunculus_tests)

add_executable(${PROJECT_NAME}
               homunculus_tests.cpp
               asset_test.cpp
               object_heap_test.cpp
               plot_tag_set_test.cpp
               saveload_tree_test.cpp
               simulation/simulation.cpp
               simulation/simulation_helpers.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
