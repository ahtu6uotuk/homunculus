#pragma once
#include <vector>

#include "common/common.h"
#include "logic/saveload.h"

struct named_tag
{
  void build_saveload_tree (saveload_node &node)
  {
    node.add (m_name, "name");
    node.add (m_value, "value");
  }
  bool operator== (const named_tag &other) const
  {
    return m_name == other.m_name && m_value == other.m_value;
  }
  string m_name;
  string m_value;
};

struct cond_goto
{
  void build_saveload_tree (saveload_node &node)
  {
    node.add (m_pc_conditions, "pc_conditions");
    node.add (m_npc_conditions, "npc_conditions");
  }
  bool operator== (const cond_goto &other) const
  {
    return m_pc_conditions == other.m_pc_conditions && m_npc_conditions == other.m_npc_conditions;
  }
  vector<pair<named_tag, string>> m_pc_conditions;
  vector<pair<named_tag, string>> m_npc_conditions;
};

class dialog_line
{
public:
  virtual ~dialog_line () {}
  bool m_final = false;
  string m_goto_tag;
  cond_goto m_conditional_goto;
  vector<named_tag> m_pc_tags_to_set;
  vector<named_tag> m_npc_tags_to_set;

protected:
  void add_to_tree (saveload_node &node)
  {
    node.add (m_goto_tag, "goto");
    node.add (m_final, "final");
    node.add (m_conditional_goto, "goto_conditional");
    node.add (m_pc_tags_to_set, "pc_tags_to_set");
    node.add (m_npc_tags_to_set, "npc_tags_to_set");
  }
  bool operator== (const dialog_line &other) const
  {
    return m_final == other.m_final && m_pc_tags_to_set == other.m_pc_tags_to_set
           && m_npc_tags_to_set == other.m_npc_tags_to_set;
  }
};

class pc_dialog_line : public dialog_line
{
public:
  virtual ~pc_dialog_line () {}
  void build_saveload_tree (saveload_node &node)
  {
    node.add (m_text, "text");
    node.add (m_tags_required, "tags_required");
    dialog_line::add_to_tree (node);
  }
  bool operator== (const pc_dialog_line &other) const
  {
    return dialog_line::operator== (other) && m_text == other.m_text;
  }

  string m_text;
  vector<named_tag> m_tags_required;
};

class npc_dialog_line : public dialog_line
{
public:
  virtual ~npc_dialog_line () {}
  void build_saveload_tree (saveload_node &node)
  {
    node.add (m_text_beats, "beats");
    node.add (m_answers, "answers");
    dialog_line::add_to_tree (node);
  }
  bool operator== (const npc_dialog_line &other) const
  {
    return dialog_line::operator== (other) && m_text_beats == other.m_text_beats
           && m_answers == other.m_answers;
  }

  vector<string> m_text_beats;
  vector<pc_dialog_line> m_answers;
};

class dialog_tree
{
public:
  void build_saveload_tree (saveload_node &node) { node.add (m_lines, "lines"); }
  unordered_map<string, npc_dialog_line> m_lines;
};
