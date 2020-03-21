#pragma once
#include <functional>
#include "common/common.h"
#include "common/err_t.h"
class engine_t;

class request_to_gui_base
{
public:
  virtual ~request_to_gui_base () {}
  virtual err_t exec (engine_t &engine) = 0;
  void exec_assert (engine_t &engine) { assert_error (exec (engine)); }
};

template<typename FuncT>
class request_to_gui_t : public request_to_gui_base
{
public:
  ~request_to_gui_t () {}
  request_to_gui_t (FuncT func) : m_func (std::move (func)) {}
  err_t exec (engine_t &engine) override { return m_func (engine); }

private:
  FuncT m_func;
};

