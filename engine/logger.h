#pragma once
#include <sstream>
#include <fstream>
#include <mutex>
#include "common/common.h"


enum class log_section_t
{
  ENGINE = 0,
  COUNT,
  ERROR = COUNT
};

enum class log_priority_t
{
  INFO = 0,
  WARNING,
  ERROR,
  COUNT
};

const char *enum_to_string (log_section_t section);
const char *enum_to_string (log_priority_t priority);

class logger_t
{
  stringstream m_buffer;
  fstream m_fstream;
  mutex m_mutex;
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
  template<typename ...Types>
  void print (const log_section_t section, const log_priority_t priority, const Types & ... data)
  {
    m_mutex.lock ();
    m_buffer.clear ();
    m_buffer.str ("");
    m_buffer << enum_to_string (section) << ": " << enum_to_string (priority) << ":";
    print_internal (data...);
    m_buffer << std::endl;
    m_fstream << m_buffer.rdbuf ();
    m_fstream.flush ();
    m_mutex.unlock ();
  }
  bool is_ok () const;
  ~logger_t ();
};
