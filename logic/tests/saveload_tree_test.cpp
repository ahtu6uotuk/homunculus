#include "logic_tests.h"

#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/saveload/saveload.h"

class inner_class
{
public:
  bool operator== (const inner_class &other) const
  {
    return    !fuzzycmp (m_double_val_1, other.m_double_val_1, 0)
           && !fuzzycmp (m_double_val_2, other.m_double_val_2, 0)
           && m_int_val_1 == other.m_int_val_1
           && m_int_val_2 == other.m_int_val_2
           && uptrs_are_equal (m_unique_int_1, other.m_unique_int_1)
           && uptrs_are_equal (m_unique_int_2, other.m_unique_int_2);
  }
  void build_saveload_tree (saveload::node_t &node)
  {
    saveload::add (node, m_double_val_1, "m_double_val_1");
    saveload::add (node, m_double_val_2, "m_double_val_2");
    saveload::add (node, m_int_val_1, "m_int_val_1");
    saveload::add (node, m_int_val_2, "m_int_val_2");
    saveload::add (node, m_unique_int_1, "m_unique_int_1");
    saveload::add (node, m_unique_int_2, "m_unique_int_2");
  }
  std::unique_ptr<int> m_unique_int_1;
  std::unique_ptr<int> m_unique_int_2;
  double m_double_val_1 = 0;
  double m_double_val_2 = 0;
  int m_int_val_1 = 0;
  int m_int_val_2 = 0;
};

class outer_class
{
public:
  bool operator== (const outer_class &other) const
  {
    return    m_member_inner == other.m_member_inner
           && !fuzzycmp (m_double_val, other.m_double_val, 0)
           && m_int_string_map == other.m_int_string_map
           && m_vect_of_inners == other.m_vect_of_inners
           && uptrs_are_equal (m_unique_inner_1, other.m_unique_inner_1)
           && uptrs_are_equal (m_unique_inner_1, other.m_unique_inner_1);
  }
  void build_saveload_tree (saveload::node_t &node)
  {
    saveload::add (node, m_member_inner, "member_inner");
    saveload::add (node, m_double_val, "double_val");
    saveload::add (node, m_int_string_map, "vect_of_ints");
    saveload::add (node, m_vect_of_inners, "vect_of_inners");
    saveload::add (node, m_unique_inner_1, "unique_inner_1");
    saveload::add (node, m_unique_inner_2, "unique_inner_2");
  }
  inner_class m_member_inner;
  std::unique_ptr<inner_class> m_unique_inner_1;
  std::unique_ptr<inner_class> m_unique_inner_2;
  double m_double_val = 0;
  std::unordered_map<int, std::string> m_int_string_map;
  std::vector<inner_class> m_vect_of_inners;
};

void complex_structure_saveload_test ()
{
  outer_class data_to_save;

  data_to_save.m_member_inner.m_double_val_1 = 1.1;
  data_to_save.m_member_inner.m_double_val_2 = 1234234.125e+30;
  data_to_save.m_member_inner.m_int_val_1 = -1735;
  data_to_save.m_member_inner.m_int_val_2 = 97353;
  data_to_save.m_member_inner.m_unique_int_1.reset (new int (11038));
  data_to_save.m_member_inner.m_unique_int_2.reset ();

  data_to_save.m_double_val = 1.0 / 7.0;

  data_to_save.m_int_string_map.insert ({1, "kek"});
  data_to_save.m_int_string_map.insert ({2, "lek"});
  data_to_save.m_int_string_map.insert ({3, "lel"});

  data_to_save.m_vect_of_inners.push_back ({});
  data_to_save.m_vect_of_inners[0].m_int_val_1 = 11037;

  data_to_save.m_unique_inner_1.reset (new inner_class ());
  data_to_save.m_unique_inner_1->m_int_val_2 = 11039;

  save_and_load_test (data_to_save);
}
