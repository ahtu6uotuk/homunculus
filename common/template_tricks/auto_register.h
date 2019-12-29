#pragma once

template<typename D>
struct automatic_register
{
private:
  struct exec_register
  {
    exec_register () { D::register_type_for_heap (); }
  };

  template<exec_register &>
  struct ref_it {};

  static exec_register register_object;
  static ref_it<register_object> referrer;
};

template<typename D>
typename automatic_register<D>::exec_register automatic_register<D>::register_object;
