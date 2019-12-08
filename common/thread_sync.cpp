#include "thread_sync.h"
#include "common/common.h"


thread_sync_t::thread_sync_t (const unsigned int thread_number):
  m_mutex (),
  m_condvar (),
  m_thread_number (thread_number)
{}

void thread_sync_t::synchronize ()
{
  /// dummy
}

thread_sync_t::~thread_sync_t () {}
