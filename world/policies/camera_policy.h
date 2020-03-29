#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "datastructs/camera_data_t.h"
#include "object/object.h"
class dialog_tree;
class world_t;

class camera_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions () { return {}; }
  };

class simple_camera_policy : public camera_policy
{
public:
  camera_data_t &get () { return m_camera_data; }

  std::string policy_describe () const override
  {
    return string_printf (
        "My coordinates are (%f; %f; %f)", m_camera_data.m_position.x, m_camera_data.m_position.y,
        m_camera_data.m_position.z);
  }
  void policy_build_saveload_tree (saveload::node_t &node) override
  {
    saveload::add (node, m_camera_data, "camera_data");
  }
  bool operator== (const simple_camera_policy &other) const
  {
    return m_camera_data == other.m_camera_data;
  }

private:
  camera_data_t m_camera_data;
};




