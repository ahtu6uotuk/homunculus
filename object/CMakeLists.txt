project(object)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    interaction.cpp
    object_heap.cpp)
