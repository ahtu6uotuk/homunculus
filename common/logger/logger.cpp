#include "logger.h"

logger_t &logger_t::instance ()
{
  static logger_t inst ("engine.log", true, true);
  return inst;
}

logger_t::logger_t (const char *fname_log, const bool is_print_to_stdout, const bool is_print_to_file):
  m_is_print_to_stdout (is_print_to_stdout), m_is_print_to_file (is_print_to_file)
{
  m_fstream.open (fname_log, std::ios_base::out);
}

bool logger_t::is_ok () const
{
  return m_fstream.is_open ();
}

logger_t::~logger_t ()
{
  m_fstream.flush ();
  m_fstream.close ();
}

const char *enum_to_string (log_section_t section)
{
  switch (section)
    {
    case log_section_t::ENGINE:
      return "ENGINE";
    case log_section_t::RENDERER:
      return "RENDERER";
    case log_section_t::GAME:
      return "GAME";
    case log_section_t::RESOURCE_MANAGER:
      return "RESOURCE MANAGER";
    case log_section_t::LOG_ERROR:
      return "Internal logger error";
    }
  return "Internal logger error";
}

const char *enum_to_string (log_priority_t priority)
{
  switch (priority)
    {
    case log_priority_t::INFO:
      return "info";
    case log_priority_t::WARNING:
      return "warning";
    case log_priority_t::LOG_ERROR:
      return "error";
    case log_priority_t::DEBUG:
      return "debug";
    case log_priority_t::COUNT:
      return "Internal logger error";
    }
  return "Internal logger error";
}

