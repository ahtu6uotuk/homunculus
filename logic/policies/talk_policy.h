#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/asset.h"
#include "logic/object/object.h"
class dialog_tree;

class talk_policy : virtual public object_base
{
public:
  virtual string describe_policy () const = 0;
  virtual void build_saveload_tree_policy (saveload_node &node) = 0;

  virtual dialog_tree &get_dialog_tree () = 0;
  virtual string &get_current_tag () = 0;
  void talk (object_base &player_character);
};

template <const char *dialog_name>
class simple_talk_policy : public talk_policy
{
public:
  string describe_policy () const override
  {
    return string_printf (
        "I talk using dialog tree from asset \"%s\". My current tag is \"%s\"", dialog_name,
        m_current_tag.c_str ());
  }
  void build_saveload_tree_policy (saveload_node &node) override
  {
    node.add (m_current_tag, "current_tag");
  }
  bool operator== (const simple_talk_policy<dialog_name> &other) const
  {
    return m_current_tag == other.m_current_tag;
  }

  dialog_tree &get_dialog_tree () override { return *m_dialog; }
  string &get_current_tag () override { return m_current_tag; }

private:
  asset_ptr<dialog_tree, dialog_name> m_dialog;
  string m_current_tag = "start";
};














