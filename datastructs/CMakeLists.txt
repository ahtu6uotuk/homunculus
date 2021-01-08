cmake_minimum_required(VERSION 2.8.0)

project(datastructs)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
	camera_data_t.cpp
    dialog.cpp
    plot_tag.cpp
    texture.cpp
    io/model_obj.cpp
    io/tga_image.cpp
    mesh.cpp
    shader.cpp
    vertex_data.cpp
    shader_property.cpp
    material.cpp
    model.cpp
    animation.cpp)

target_link_libraries(${PROJECT_NAME} GLEW::GLEW ${OPENGL_LIBRARIES} common resource)


