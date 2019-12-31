#include "logic_tests.h"

#include <string>
#include <vector>

#include "common/common.h"
#include "logic/asset.h"

static const char teststr[] = "test";

void asset_test ()
{
  vector<string> replics = {"kek", "чебурек", "лол"};


  asset_ptr<vector<string>, teststr> test_asset;
  assert_check (*test_asset.get () == replics, "These should be equal");
}
