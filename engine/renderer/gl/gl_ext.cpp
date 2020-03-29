#include "gl_ext.h"

#include <GL/glew.h>
#include <iostream>

#include "engine/logger.h"

const char *gl_error_to_string (unsigned int err_code)
{
  switch (err_code)
    {
    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";
    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW:
      return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:
      return "GL_STACK_UNDERFLOW";
    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";
    case GL_NO_ERROR:
      return nullptr;
    default:
      return "unknown GL error";
    }
  return "unknown GL error";
}

void gl_get_error_description (logger_t *logger, const char *filename, unsigned int line)
{
  auto err_code = glGetError ();
  auto descr = gl_error_to_string (err_code);
  if (descr)
    {
      if (logger)
        logger->print (log_section_t::RENDERER, log_priority_t::DEBUG, filename, ":", line, ":", descr);
      else
        std::cout << filename << ": line " << std::to_string (line) << ": " << descr << std::endl;
    }
}
