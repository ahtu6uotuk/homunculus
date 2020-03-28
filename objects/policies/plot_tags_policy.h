#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/plot_tag.h"
#include "logic/object/object.h"

class plot_tags_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  std::vector<interaction> policy_get_interactions () { return {}; }

  virtual void set_tag (const std::string &tag_name, const std::string &tag_value) = 0;
  virtual bool has_tag (const std::string &tag_name, const std::string &tag_value) const = 0;
};

template <typename ... NamedEnums>
class simple_plot_tags_policy : public plot_tags_policy
{
public:
  virtual std::string policy_describe () const override { return m_set.print (); }
  virtual void policy_build_saveload_tree (saveload::node_t &node) override { saveload::add (node, m_set, "tag_set"); }
  bool operator== (const simple_plot_tags_policy<NamedEnums...> &other) const
  {
    return m_set == other.m_set;
  }

  void set_tag (const std::string &tag_name, const std::string &tag_value) override
  {
    m_set.set (tag_name, tag_value);
  }

  bool has_tag (const std::string &tag_name, const std::string &tag_value) const override
  {
    return m_set.has (tag_name, tag_value);
  }

private:
  plot_tag_set<NamedEnums ...> m_set;
};
