#pragma once

#include "common/common.h"
class saveload_node;

class object_base
{
public:
  virtual ~object_base () {}
  template<typename PolicyType>
  PolicyType *get_policy ()
  {
    return dynamic_cast<PolicyType *> (&get_policy_private ());
  }

  virtual string describe () const = 0;
private:
  virtual object_base &get_policy_private () = 0;
  template<typename Self, typename... Args> friend class object;
};
