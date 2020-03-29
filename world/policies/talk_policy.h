#pragma once

#include "common/common.h"
#include "common/string/string_utils.h"
#include "resource/asset.h"
#include "object/object.h"
class dialog_tree;

class talk_policy : virtual public object_base
{
public:
  virtual std::string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload::node_t &node) = 0;
  virtual std::vector<interaction> policy_get_interactions ()
  {
    return {interaction ("Talk", [this] (object_base &pc) { get_talked_by (pc); })};
  }

  virtual dialog_tree &get_dialog_tree () = 0;
  virtual std::string &get_current_tag () = 0;
  void get_talked_by (object_base &player_character);
};

template <const char *dialog_name>
class simple_talk_policy : public talk_policy
{
public:
  std::string policy_describe () const override
  {
    return string_printf ("Talks using dialog \"%s\", tag: \"%s\"", dialog_name, m_current_tag.c_str ());
  }
  void policy_build_saveload_tree (saveload::node_t &node) override
  {
    saveload::add (node, m_current_tag, "current_tag");
  }
  bool operator== (const simple_talk_policy<dialog_name> &other) const
  {
    return m_current_tag == other.m_current_tag;
  }

  dialog_tree &get_dialog_tree () override { return *m_dialog; }
  std::string &get_current_tag () override { return m_current_tag; }

private:
  asset_ptr<dialog_tree, dialog_name> m_dialog;
  std::string m_current_tag = "start";
};














