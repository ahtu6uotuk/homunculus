#include "common/thread_sync.h"
#include "thread_info.h"


thread_info_t::thread_info_t (thread_info_t &&thr_info):
  m_thread_sync (thr_info.m_thread_sync),
  m_thread_sync_w_main (thr_info.m_thread_sync_w_main),
  m_mutex (),
  m_condvar_mutex (),
  m_condvar (),
  m_thread_id (thr_info.m_thread_id),
  m_thread_number (thr_info.m_thread_number),
  m_activations (thr_info.m_activations)
{}

thread_info_t::thread_info_t (thread_sync_t &thread_sync,
                              thread_sync_t &thread_sync_w_main,
                              unsigned int thread_id,
                              unsigned int thread_number):
  m_thread_sync (thread_sync),
  m_thread_sync_w_main (thread_sync_w_main),
  m_thread_id (thread_id),
  m_thread_number (thread_number),
  m_activations (0)
{}

void thread_info_t::sync () { m_thread_sync.sync (); }

void thread_info_t::sync_with_main () { m_thread_sync_w_main.sync (); }
