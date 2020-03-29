#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "datastructs/texture.h"
#include "object/object.h"
#include "resource/asset.h"
class world_t;

class texture_policy : virtual public object_base
{
public:
  virtual texture_t *get_texture () = 0;

  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }
};

template<const char *file_name>
class simple_texture_policy : public texture_policy
{
public:
  texture_t *get_texture () override { return m_texture.get (); }

  std::string policy_describe () const override
  {
    return string_printf ("texture from %s", file_name);
  }

  void policy_build_saveload_tree (saveload::node_t &) override {}

  bool operator== (const simple_texture_policy<file_name> &) const
  {
    return true;
  }

private:
  asset_ptr<texture_t, file_name> m_texture;
};
