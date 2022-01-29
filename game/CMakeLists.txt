project (game)

add_library (${PROJECT_NAME} STATIC)

target_sources (${PROJECT_NAME} PRIVATE game.cpp game.h game_settings.cpp game_settings.h)

target_link_libraries (${PROJECT_NAME} engine jsoncpp)
