#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <mutex>

#include "common/common.h"

enum class log_section_t
{
  ENGINE = 0,
  RENDERER,
  GAME,
  RESOURCE_MANAGER,
  COUNT
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
private:
  std::stringstream m_buffer;
  std::fstream m_fstream;
  std::mutex m_mutex;
  bool m_is_print_to_stdout;
  bool m_is_print_to_file;
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
  explicit logger_t (const char *fname_log, const bool is_print_to_stdout, const bool is_print_to_file);
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
    if (m_is_print_to_file)
      {
        m_fstream << m_buffer.rdbuf ();
        m_buffer.seekg (m_buffer.beg);
        m_fstream.flush ();
      }
    if (m_is_print_to_stdout)
      {
        std::cout << m_buffer.rdbuf ();
        std::cout.flush ();
      }
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

  static logger_t &instance ();

  ~logger_t ();
};
