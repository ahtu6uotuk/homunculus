#pragma once
#include <sstream>
#include <fstream>
#include <mutex>
#include "common/common.h"


enum class log_section_t
{
  ENGINE = 0,
  RENDERER,
  GAME,
  RESOURCE_MANAGER,
  COUNT,
  LOG_ERROR = COUNT
};

enum class log_priority_t
{
  INFO = 0,
  WARNING,
  LOG_ERROR,
  DEBUG,
  COUNT
};

const char *enum_to_string (log_section_t section);
const char *enum_to_string (log_priority_t priority);

class logger_t
{
  std::stringstream m_buffer;
  std::fstream m_fstream;
  std::mutex m_mutex;
private:
  void print_internal ()
  {}
  template<typename T, typename ... TYPES>
  void print_internal (const T &data, const TYPES & ... additional_data)
  {
    m_buffer << " " << data;
    return print_internal (additional_data...);
  }
public:
  logger_t () = delete;
  explicit logger_t (const char *fname_log);
  logger_t (const logger_t &) = delete;
  logger_t (logger_t &&) = delete;
  template<typename ...Types>
  void print_plain (const Types & ... data)
  {
    std::lock_guard lock (m_mutex);
    m_buffer.clear ();
    m_buffer.str ("");
    print_internal (data...);
    m_buffer << std::endl;
    m_fstream << m_buffer.rdbuf ();
    m_fstream.flush ();
  }
  template<typename ...Types>
  void print (const log_section_t section, const log_priority_t priority, const Types & ... data)
  {
    std::string prefix = enum_to_string (section);
    prefix.append (": ");
    prefix.append (enum_to_string (priority));
    prefix.append (":");
    return print_plain (prefix, data...);
  }

  bool is_ok () const;
  ~logger_t ();
};
