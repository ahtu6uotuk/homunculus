#ifndef THREAD_SYNC_H
#define THREAD_SYNC_H
#include <mutex>
#include <condition_variable>


using namespace std;

class thread_sync_t
{
  mutex m_mutex;
  condition_variable m_condvar;
  unsigned int m_thread_number;
  bool m_is_iteration_done = false;
public:
  thread_sync_t () = delete;
  thread_sync_t (const thread_sync_t &) = delete;
  thread_sync_t (thread_sync_t &&) = delete;
  thread_sync_t (const unsigned int thread_number);
  void synchronize ();
  bool is_iteration_done () const {return m_is_iteration_done;}
  void set_iteration_state (const bool is_done) {m_is_iteration_done = is_done;}
  ~thread_sync_t ();
};

#endif // THREAD_SYNC_H
