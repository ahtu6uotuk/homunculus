#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/plot_tag.h"
#include "logic/object/object.h"

class plot_tags_policy : virtual public object_base
{
public:
  virtual string describe_policy () const = 0;
  virtual void build_saveload_tree_policy (saveload_node &node) = 0;

  virtual void set_tag (const string &tag_name, const string &tag_value) = 0;
  virtual bool has_tag (const string &tag_name, const string &tag_value) const = 0;
};

template <typename ... NamedEnums>
class simple_plot_tags_policy : public plot_tags_policy
{
public:
  virtual string describe_policy () const override { return m_set.print (); }
  virtual void build_saveload_tree_policy (saveload_node &node) override { node.add (m_set, "tag_set"); }
  bool operator== (const simple_plot_tags_policy<NamedEnums...> &other) const
  {
    return m_set == other.m_set;
  }

  void set_tag (const string &tag_name, const string &tag_value) override
  {
    m_set.set (tag_name, tag_value);
  }

  bool has_tag (const string &tag_name, const string &tag_value) const override
  {
    return m_set.has (tag_name, tag_value);
  }

private:
  plot_tag_set<NamedEnums ...> m_set;
};
