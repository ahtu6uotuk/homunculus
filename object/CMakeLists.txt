cmake_minimum_required(VERSION 2.8.0)

project(object)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    interaction.cpp
    object_heap.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "../")
