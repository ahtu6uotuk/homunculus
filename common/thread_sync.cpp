#include "thread_sync.h"
#include "common/common.h"


thread_sync_t::thread_sync_t (const unsigned int thread_number):
  m_mutex (),
  m_condvar_in (),
  m_condvar_out (),
  m_thread_number (thread_number)
{}

void thread_sync_t::sync ()
{
  if (m_thread_number <= 1)
    return;

  unique_lock lock (m_mutex);

  m_times_in++;

  if (m_times_in >= m_thread_number)
    {
      m_times_out = 0;
      m_condvar_in.notify_all ();
    }
  else
    m_condvar_in.wait (lock, [&] () { return m_times_in >= m_thread_number; });

  m_times_out++;

  if (m_times_out >= m_thread_number)
    {
      m_times_in = 0;
      m_condvar_out.notify_all ();
    }
  else
    m_condvar_out.wait (lock, [&] () { return m_times_out >= m_thread_number; });

  do_nothing ();
}

thread_sync_t::~thread_sync_t () {}
