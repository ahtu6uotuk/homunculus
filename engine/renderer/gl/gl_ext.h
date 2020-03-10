#pragma once
#ifndef GL_EXT_H
#define GL_EXT_H

class logger_t;

/// @brief Get string representation of GL error code
const char *gl_error_to_string (unsigned int err_code);

/// @brief Print GL error code string to logger or stdout
void gl_get_error_description (logger_t *logger, const char *filename, unsigned int line);

#define GL_DEBUG_INFO(LOGGER) gl_get_error_description((LOGGER), __FILE__, __LINE__)

#endif // GL_EXT_H
