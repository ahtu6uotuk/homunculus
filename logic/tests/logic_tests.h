#pragma once
#include "common/common.h"
#include "common/err_t.h"
#include "common/string/string_utils.h"

void complex_structure_saveload_test ();
void object_heap_test ();
void asset_test ();

void run_logic_tests ()
{
  complex_structure_saveload_test ();
  object_heap_test ();
  asset_test ();
}

template <typename T>
T save_and_load_test (T &data_to_save)
{
  string dump;
  assert_error (save (data_to_save, dump));

  T data_to_load;
  assert_error (load (data_to_load, dump), string_printf ("\nDump:\n%s", dump.c_str ()));

  err_t err = (data_to_save == data_to_load ? ERR_OK : err_t ("Loaded data is different from saved data!"));
  assert_error (err, string_printf ("\nDump:\n%s", dump.c_str ()));

  string another_dump;
  assert_error (save (data_to_load, another_dump));

  err = (dump == another_dump ? ERR_OK : err_t ("Loaded data dump differs from saved data dump!"));
  assert_error (err, string_printf ("\nDump1:\n%s\nDump2:\n%s", dump.c_str (), another_dump.c_str ()));

  return data_to_load;
}
