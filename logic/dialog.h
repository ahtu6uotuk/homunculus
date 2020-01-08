#pragma once
#include <vector>
#include <unordered_map>

#include "common/common.h"
class saveload_node;

struct named_tag
{
  void build_saveload_tree (saveload_node &node);
  bool operator== (const named_tag &other) const;
  string m_name;
  string m_value;
};

struct cond_goto
{
  void build_saveload_tree (saveload_node &node);
  bool operator== (const cond_goto &other) const;
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
  void add_to_tree (saveload_node &node);
  bool operator== (const dialog_line &other) const;
};

class pc_dialog_line : public dialog_line
{
public:
  virtual ~pc_dialog_line () {}
  void build_saveload_tree (saveload_node &node);
  bool operator== (const pc_dialog_line &other) const;
  const string &print () const;

  string m_text;
  vector<named_tag> m_tags_required;
};

class npc_dialog_line : public dialog_line
{
public:
  virtual ~npc_dialog_line () {}
  void build_saveload_tree (saveload_node &node);
  bool operator== (const npc_dialog_line &other) const;

  vector<string> m_text_beats;
  vector<pc_dialog_line> m_answers;
};

class dialog_tree
{
public:
  void build_saveload_tree (saveload_node &node);
  unordered_map<string, npc_dialog_line> m_lines;
};
