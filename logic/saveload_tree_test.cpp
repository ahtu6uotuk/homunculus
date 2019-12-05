#include <iostream>
#include "common/string_utils.h"
#include "logic/saveload_tree_test.h"
#include "common/common.h"
#include "logic/saveload_tree.h"

class A
{
public:
  bool operator == (const A &other)
  {
    return
        !fuzzycmp (x, other.x, 0)
        && !fuzzycmp (y, other.y, 0)
        && z1 == other.z1
        && z2 == other.z2;
  }
  void build_saveload_tree (saveload_node &node)
  {
    node.add (x, "x");
    node.add (y, "y");
    node.add (z1, "z1");
    node.add (z2, "z2");
  }
  double x = 0;
  double y = 0;
  int z1 = 0;
  int z2 = 0;
};

class B
{
public:
  bool operator == (const B &other) { return k == other.k && !fuzzycmp (m, other.m, 0); }
  void build_saveload_tree (saveload_node &node)
  {
    node.add (k, "some_args");
    node.add (m, "m");
    node.add (l, "dlist");
  }
  A k;
  double m = 0;
  vector<double> l;
};

void saveload_tree_test ()
{
  B data_to_save;
  data_to_save.k.x = 1.1;
  data_to_save.k.y = 1234234.125e+30;
  data_to_save.k.z1 = -1735;
  data_to_save.k.z2 = 97353;
  data_to_save.m = 1.0 / 7.0;
  data_to_save.l = {1, 2, 3};

  string dump;
  assert_test (save (data_to_save, dump));

  B data_to_load;
  assert_test (load (data_to_load, dump), string_printf ("\nDump:\n%s", dump.c_str ()));

  err_t err = (data_to_save == data_to_load ? ERR_OK : err_t ("Loaded data is different from saved data!"));
  assert_test (err, string_printf ("\nDump:\n%s", dump.c_str ()));
}

