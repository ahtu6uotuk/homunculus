cmake_minimum_required(VERSION 2.8.0)

project(homunculus)

set (OpenGL_GL_PREFERENCE LEGACY)
include (FindOpenGL)
if (NOT OpenGL_OpenGL_FOUND)
  message (FATAL_ERROR "OpenGL libraries not found!")
endif ()
if (NOT OPENGL_GLU_FOUND)
  message (FATAL_ERROR "GLU libraries not found!")
endif ()
find_package(GLEW REQUIRED)

# Compiler tuning
set(CMAKE_CXX_FLAGS "-W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -Wnon-virtual-dtor -Wmissing-format-attribute -Wvla -Wuninitialized -Wno-unused-local-typedefs -Wshadow -Wextra  -Wformat-security -Wformat-nonliteral")
if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
  set(CMAKE_CXX_FLAGS "-Wsuggest-override -Wno-maybe-uninitialized -Wformat=1 -Wlogical-op ${CMAKE_CXX_FLAGS}")
endif ()

# gcc-only -Wsuggest-override -Wno-maybe-uninitialized -Wformat=1 -Wlogical-op
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories (./)

add_subdirectory(common)
add_subdirectory(engine)
add_subdirectory(control_flow)
add_subdirectory(world)
add_subdirectory(datastructs)
add_subdirectory(resource)
add_subdirectory(object)
add_subdirectory(tests)

add_executable(homunculus main.cpp)

target_link_libraries(homunculus
 common
 control_flow)
