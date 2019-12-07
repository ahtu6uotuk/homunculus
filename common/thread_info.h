#pragma once

class thread_info_t
{
  unsigned int m_thread_id;
  unsigned int m_thread_number;
public:
  thread_info_t () = delete;
  thread_info_t (thread_info_t &) = delete;
  thread_info_t (thread_info_t &&) = delete;
  thread_info_t (unsigned int thread_id, unsigned int thread_number);
  unsigned int get_thread_id () const {return m_thread_id;}
  unsigned int get_thread_number () const {return m_thread_number;}
};
