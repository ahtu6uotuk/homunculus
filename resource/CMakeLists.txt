cmake_minimum_required(VERSION 2.8.0)

project(resource)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    asset.cpp
    resource_manager.cpp
    saveload/saveload_tree.cpp
    saveload/saveload_default_helpers.cpp
    )
