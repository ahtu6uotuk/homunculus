#pragma once

class logger_t;

/// @brief Get string representation of GL error code
const char *gl_error_to_string (unsigned int err_code);

/// @brief Print GL error code string to logger or stdout
void gl_get_error_description (const char *filename, unsigned int line);

#define GL_DEBUG_INFO() gl_get_error_description(__FILE__, __LINE__)
