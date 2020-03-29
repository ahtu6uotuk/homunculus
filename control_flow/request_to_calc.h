#pragma once
#include <functional>
#include <vector>
#include "common/common.h"
#include "common/err_t.h"
class world_t;
class thread_info_t;

class request_to_calc_base
{
public:
  virtual ~request_to_calc_base () {}
  virtual err_t exec (world_t &world, thread_info_t &thr_info) = 0;
  virtual bool is_exit () { return false; }
  void exec_assert (world_t &world, thread_info_t &thr_info)
  {
    assert_error (exec (world, thr_info));
  }
};

class request_to_calc_exit : public request_to_calc_base
{
public:
  ~request_to_calc_exit () {}
  request_to_calc_exit () {}
  bool is_exit () override { return true; }
  err_t exec (world_t &, thread_info_t &) override
  {
    assert_check (false, "Sanity");
    return ERR_OK;
  }
};

template<typename FuncT>
class request_to_calc_t : public request_to_calc_base
{
public:
  ~request_to_calc_t () {}
  request_to_calc_t (FuncT func) : m_func (std::move (func)) {}
  err_t exec (world_t &world, thread_info_t &thr_info) override { return m_func (world, thr_info); }

private:
  FuncT m_func;
};
