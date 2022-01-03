project(common)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    common.cpp
    err_t.cpp
    file_utils.cpp
    string/string_converters.cpp
    string/string_utils.cpp
    thread_info.cpp
    thread_sync.cpp
    logger/logger.cpp
    logger/logger_utils.cpp)
