#ifndef THREAD_SYNC_H
#define THREAD_SYNC_H
#include <mutex>
#include <condition_variable>
#include <functional>

class thread_sync_t
{
  std::mutex m_mutex;
  std::condition_variable m_condvar_in;
  std::condition_variable m_condvar_out;
  unsigned int m_times_in = 0;
  unsigned int m_times_out = 0;
  unsigned int m_thread_number;

public:
  void sync ();

  thread_sync_t () = delete;
  thread_sync_t (const thread_sync_t &) = delete;
  thread_sync_t (thread_sync_t &&) = delete;
  thread_sync_t (const unsigned int thread_number);
  ~thread_sync_t ();
};

#endif // THREAD_SYNC_H
