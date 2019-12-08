#pragma once
#include <mutex>
#include <condition_variable>


using namespace std;
class thread_sync_t;

class thread_info_t
{
  thread_sync_t &m_thread_sync;
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
                 unsigned int thread_id,
                 unsigned int thread_number);
  unsigned int get_thread_id () const {return m_thread_id;}
  unsigned int get_thread_number () const {return m_thread_number;}
  void synchronize ();
};
