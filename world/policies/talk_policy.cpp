#include "talk_policy.h"

#include "datastructs/dialog.h"
#include "object/object.h"
#include "tests/simulation/simulation_helpers.h"
#include "world/policies/plot_tags_policy.h"

static void print_text_beats (const std::vector<std::string> &beats)
{
  for (const std::string &beat : beats)
    {
      printf ("%s\n", beat.c_str ());
      std::string dummy;
      getline (std::cin, dummy);
    }
}

static std::string get_goto (const object_base &pc, const object_base &npc, const dialog_line &line)
{
  const plot_tags_policy *pc_policy = pc.get_policy<plot_tags_policy> ();
  const plot_tags_policy *npc_policy = npc.get_policy<plot_tags_policy> ();

  std::string curr_goto = "";

  for (const std::pair<named_tag, std::string> &cond_goto : line.m_conditional_goto.m_pc_conditions)
    {
      if (pc_policy->has_tag (cond_goto.first.m_name, cond_goto.first.m_value))
        {
          assert_check (curr_goto.empty (), "Conditional gotos should be mutually exclusive");
          curr_goto = cond_goto.second;
        }
    }

  for (const std::pair<named_tag, std::string> &cond_goto : line.m_conditional_goto.m_npc_conditions)
    {
      if (npc_policy->has_tag (cond_goto.first.m_name, cond_goto.first.m_value))
        {
          assert_check (curr_goto.empty (), "Conditional gotos should be mutually exclusive");
          curr_goto = cond_goto.second;
        }
    }

  if (!curr_goto.empty ())
    return curr_goto;

  bool is_npc_line = dynamic_cast<const npc_dialog_line *> (&line);
  assert_check (is_npc_line || !line.m_goto_tag.empty (), "If none of conditional gotos work, default one should");
  return line.m_goto_tag;
}

static void exec_dialog_line (const dialog_line &line, object_base &pc, object_base &npc)
{
  plot_tags_policy *pc_policy = pc.get_policy<plot_tags_policy> ();
  plot_tags_policy *npc_policy = npc.get_policy<plot_tags_policy> ();

  for (const named_tag &pc_tag_to_set : line.m_pc_tags_to_set)
    pc_policy->set_tag (pc_tag_to_set.m_name, pc_tag_to_set.m_value);

  for (const named_tag &npc_tag_to_set :line.m_npc_tags_to_set)
    npc_policy->set_tag (npc_tag_to_set.m_name, npc_tag_to_set.m_value);
}

void talk_policy::get_talked_by (object_base &player_character)
{
  std::unordered_map<std::string, npc_dialog_line> &lines = get_dialog_tree ().m_lines;

  while (true)
    {
      assert_check (lines.count (get_current_tag ()), "Dialog doesnt have this tag");
      npc_dialog_line &curr_line = lines[get_current_tag ()];

      exec_dialog_line (curr_line, player_character, *this);
      print_text_beats (curr_line.m_text_beats);

      if (curr_line.m_final)
        return;

      std::string goto_str = get_goto (player_character, *this, curr_line);
      if (!goto_str.empty ())
        {
          get_current_tag () = goto_str;
          continue;
        }

      std::function<std::string (const pc_dialog_line &)> print_func
          = [] (const pc_dialog_line &line) { return line.print (); };
      int answer_number = print_choices_and_get_answer (curr_line.m_answers, print_func);

      pc_dialog_line &given_answer = curr_line.m_answers[answer_number];
      exec_dialog_line (given_answer, player_character, *this);
      get_current_tag () = get_goto (player_character, *this, given_answer);
    }
}
