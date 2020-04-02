cmake_minimum_required(VERSION 2.8.0)

project(homunculus)

# Main libraries
find_library(SFML_GRAPHICS_LIBRARY NAMES sfml-graphics)
find_library(SFML_WINDOW_LIBRARY NAMES sfml-window)
find_library(SFML_SYSTEM_LIBRARY NAMES sfml-system)
find_library(MATH_LIBRARY NAMES m)

# Compiler tuning
set(CMAKE_CXX_FLAGS="-W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wsuggest-override -Wmissing-declarations -Wnon-virtual-dtor -Wmissing-format-attribute -Wvla -Wformat=1 -Wno-maybe-uninitialized -Wuninitialized -Wlogical-op -Wno-unused-local-typedefs -Wshadow -Wextra  -Wformat-security -Wformat-nonliteral")
set (CMAKE_CXX_STANDARD 20)

add_subdirectory(common)
add_subdirectory(engine)
add_subdirectory(control_flow)
add_subdirectory(world)
add_subdirectory(datastructs)
add_subdirectory(resource)
add_subdirectory(object)
#add_subdirectory(tests)

add_executable(homunculus main.cpp)

target_link_libraries(homunculus
 ${SFML_GRAPHICS_LIBRARY}
 ${SFML_WINDOW_LIBRARY}
 ${SFML_SYSTEM_LIBRARY}
 ${MATH_LIBRARY}
 ${PLATFORM_SPECIFIC_LIBRARIES}
 common
 control_flow)

#set(INCLUDE_DIR "./")
