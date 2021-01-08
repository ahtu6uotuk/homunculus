project (model_compiler)

add_executable (${PROJECT_NAME} model_compiler.cpp)
target_link_libraries (${PROJECT_NAME} common datastructs)
