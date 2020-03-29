#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "datastructs/shader.h"
#include "object/object.h"
#include "resource/asset.h"
class world_t;

class shader_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }
};

template<const char *file_name>
class simple_shader_policy : public shader_policy
{
public:
  shader_t &get_shader () { return *m_shader; }

  std::string policy_describe () const override
  {
    return string_printf ("shader from %s", file_name);
  }

  void policy_build_saveload_tree (saveload::node_t &) override {}

  bool operator== (const simple_shader_policy<file_name> &) const
  {
    return true;
  }

private:
  asset_ptr<shader_t, file_name> m_shader;
};





