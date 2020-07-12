#pragma once

#include <vector>

#include "common/common.h"
class interaction;

class object_base
{
public:
  virtual ~object_base () {}
  template<typename PolicyType>
  PolicyType *get_policy ()
  {
    return dynamic_cast<PolicyType *> (&get_policy_private ());
  }

  template<typename PolicyType>
  const PolicyType *get_policy () const
  {
    return dynamic_cast<const PolicyType *> (&get_policy_private ());
  }

  virtual std::string describe () const = 0;
  virtual std::vector<interaction> get_interactions () = 0;
  int get_id () const { return m_id; }
private:
  virtual object_base &get_policy_private () = 0;
  virtual const object_base &get_policy_private () const = 0;
  template<typename Self, typename... Args> friend class object;

protected:
  // TODO: make ids totally unique, not just unique for each level
  int m_id = -1;
  friend class object_heap;
  friend class world_t;
};
