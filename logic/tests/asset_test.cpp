#include "logic_tests.h"

#include <string>
#include <vector>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/saveload_tree.h"

void asset_test ()
{
  vector<string> replics = {"kek", "чебурек", "лол"};

  string res;
  assert_error (save (replics, res));
  assert_error (to_asset_file (res, "test"));

  vector<string> another;
  string another_str;
  assert_error (from_asset_file (another_str, "test"));
  assert_error (load (another, another_str));

  assert_check (replics == another, "They should be equal");
}
