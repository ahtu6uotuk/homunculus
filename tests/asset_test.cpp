#include "logic_tests.h"

#include <string>
#include <vector>

#include "common/common.h"
#include "resource/asset.h"

void asset_test ()
{
  std::vector<std::string> replics = {"kek", "чебурек", "лол", "mea culpa", ""};

  std::string savestring;
  assert_error (saveload::save (replics, savestring));
  assert_error (to_asset_file (savestring, "test"));

  asset_ptr<std::vector<std::string>, LITERAL ("test")> test_asset;
  assert_check (*test_asset.get () == replics, "These should be equal");
}