#include "resource_manager.h"

resource_manager &resource_manager::instance ()
{
  static resource_manager inst;
  return inst;
}
