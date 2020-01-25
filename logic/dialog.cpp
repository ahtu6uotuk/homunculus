#include "dialog.h"

#include "logic/saveload/saveload.h"

void named_tag::build_saveload_tree (saveload_node &node)
{
  node.add (m_name, "name");
  node.add (m_value, "value");
}
bool named_tag::operator== (const named_tag &other) const
{
  return m_name == other.m_name && m_value == other.m_value;
}

void cond_goto::build_saveload_tree (saveload_node &node)
{
  node.add (m_pc_conditions, "pc_conditions");
  node.add (m_npc_conditions, "npc_conditions");
}
bool cond_goto::operator== (const cond_goto &other) const
{
  return m_pc_conditions == other.m_pc_conditions && m_npc_conditions == other.m_npc_conditions;
}

void dialog_line::add_to_tree (saveload_node &node)
{
  node.add (m_goto_tag, "goto");
  node.add (m_final, "final");
  node.add (m_conditional_goto, "goto_conditional");
  node.add (m_pc_tags_to_set, "pc_tags_to_set");
  node.add (m_npc_tags_to_set, "npc_tags_to_set");
}
bool dialog_line::operator== (const dialog_line &other) const
{
  return m_final == other.m_final && m_pc_tags_to_set == other.m_pc_tags_to_set
         && m_npc_tags_to_set == other.m_npc_tags_to_set;
}

void pc_dialog_line::build_saveload_tree (saveload_node &node)
{
  node.add (m_text, "text");
  node.add (m_tags_required, "tags_required");
  dialog_line::add_to_tree (node);
}
bool pc_dialog_line::operator== (const pc_dialog_line &other) const
{
  return dialog_line::operator== (other) && m_text == other.m_text;
}
const string &pc_dialog_line::print () const { return m_text; }

void npc_dialog_line::build_saveload_tree (saveload_node &node)
{
  node.add (m_text_beats, "beats");
  node.add (m_answers, "answers");
  dialog_line::add_to_tree (node);
}
bool npc_dialog_line::operator== (const npc_dialog_line &other) const
{
  return dialog_line::operator== (other) && m_text_beats == other.m_text_beats
         && m_answers == other.m_answers;
}


void dialog_tree::build_saveload_tree (saveload_node &node) { node.add (m_lines, "lines"); }
