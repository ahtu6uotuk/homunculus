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
public:
  thread_sync_t () = delete;
  thread_sync_t (const thread_sync_t &) = delete;
  thread_sync_t (thread_sync_t &&) = delete;
  thread_sync_t (const unsigned int thread_number);
  void synchronize ();
  ~thread_sync_t ();
};

#endif // THREAD_SYNC_H
