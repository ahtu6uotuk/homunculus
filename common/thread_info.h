#pragma once
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;
class thread_sync_t;

class thread_info_t
{
  thread_sync_t &m_thread_sync;
  thread_sync_t &m_thread_sync_w_main;
  mutex m_mutex;
  mutex m_condvar_mutex;
  condition_variable m_condvar;
  unsigned int m_thread_id;
  unsigned int m_thread_number;
  unsigned int m_activations;
public:
  thread_info_t () = delete;
  thread_info_t (thread_info_t &) = delete;
  thread_info_t (thread_info_t &&);
  thread_info_t (thread_sync_t &thread_sync,
                 thread_sync_t &thread_sync_w_main,
                 unsigned int thread_id,
                 unsigned int thread_number);
  bool is_main_thread () const { return m_thread_id == 0; }
  unsigned int get_thread_id () const {return m_thread_id;}
  unsigned int get_thread_number () const {return m_thread_number;}

  void sync ();
  void sync_with_main ();
};
