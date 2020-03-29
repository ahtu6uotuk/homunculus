#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "datastructs/mesh.h"
#include "object/object.h"
#include "resource/asset.h"
class world_t;

class mesh_policy : virtual public object_base
{
public:
  virtual mesh_t *get_mesh () = 0;

  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }
};

template<const char *file_name>
class simple_mesh_policy : public mesh_policy
{
public:
  mesh_t *get_mesh () override { return m_mesh.get (); }

  std::string policy_describe () const override
  {
    return string_printf ("mesh from %s", file_name);
  }

  void policy_build_saveload_tree (saveload::node_t &) override {}

  bool operator== (const simple_mesh_policy<file_name> &) const
  {
    return true;
  }

private:
  asset_ptr<mesh_t, file_name> m_mesh;
};
