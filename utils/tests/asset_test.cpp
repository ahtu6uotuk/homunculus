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
  assert_error (to_gamedata_file (savestring, "assets/test.xml"));

  asset_ptr<std::vector<std::string>, LITERAL ("assets/test.xml")> test_asset;
  assert_check (*test_asset.get () == replics, "These should be equal");
}
