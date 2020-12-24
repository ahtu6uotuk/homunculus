#pragma once
#include <vector>
#include <unordered_map>

#include "common/common.h"
#include "resource/saveload/saveload_fwd.h"

struct named_tag
{
  void build_saveload_tree (saveload::node_t &node);
  bool operator== (const named_tag &other) const;
  std::string m_name;
  std::string m_value;
};

struct cond_goto
{
  void build_saveload_tree (saveload::node_t &node);
  bool operator== (const cond_goto &other) const;
  std::vector<std::pair<named_tag, std::string>> m_pc_conditions;
  std::vector<std::pair<named_tag, std::string>> m_npc_conditions;
};

class dialog_line
{
public:
  virtual ~dialog_line () {}
  bool m_final = false;
  std::string m_goto_tag;
  cond_goto m_conditional_goto;
  std::vector<named_tag> m_pc_tags_to_set;
  std::vector<named_tag> m_npc_tags_to_set;

protected:
  void add_to_tree (saveload::node_t &node);
  bool operator== (const dialog_line &other) const;
};

class pc_dialog_line : public dialog_line
{
public:
  virtual ~pc_dialog_line () {}
  void build_saveload_tree (saveload::node_t &node);
  bool operator== (const pc_dialog_line &other) const;
  const std::string &print () const;

  std::string m_text;
  std::vector<named_tag> m_pc_tags_required;
  std::vector<named_tag> m_npc_tags_required;
};

class npc_dialog_line : public dialog_line
{
public:
  virtual ~npc_dialog_line () {}
  void build_saveload_tree (saveload::node_t &node);
  bool operator== (const npc_dialog_line &other) const;

  std::vector<std::string> m_text_beats;
  std::vector<pc_dialog_line> m_answers;
};

class dialog_tree
{
public:
  void build_saveload_tree (saveload::node_t &node);
  std::unordered_map<std::string, npc_dialog_line> m_lines;
};
