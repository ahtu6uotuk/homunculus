#include "logic_tests.h"

#include <string>
#include <vector>

#include "common/common.h"
#include "logic/asset.h"

void asset_test ()
{
  vector<string> replics = {"kek", "чебурек", "лол", "mea culpa"};

  string savestring;
  assert_error (save (replics, savestring));
  assert_error (to_asset_file (savestring, "test"));

  asset_ptr<vector<string>, STRING_LITERAL ("test")> test_asset;
  assert_check (*test_asset.get () == replics, "These should be equal");
}
