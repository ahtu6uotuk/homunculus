#include "talk_policy.h"

#include "logic/dialog.h"
#include "logic/object/object.h"
#include "logic/policies/plot_tags_policy.h"

static void print_text_beats (const vector<string> &beats)
{
  for (const string &beat : beats)
    {
      printf ("%s", beat.c_str ());
      string dummy;
      getline (cin, dummy);
    }
}

static void print_answers (const vector<pc_dialog_line> &answers)
{
  for (int i = 0; i < isize (answers); i++)
    {
      const pc_dialog_line &answer = answers[i];
      printf ("%d: %s\n", i + 1, answer.m_text.c_str ());
    }
}

static bool get_answer_number_or_print_error (const vector<pc_dialog_line> &answers, int &res)
{
  string player_input;
  getline (cin, player_input);

  int answer_number = 0;
  err_t err = string_to_data (player_input, answer_number);
  answer_number--;

  if (!err.ok ())
    {
      printf ("%s\n", err.descr_c_str ());
      return true;
    }

  if (answer_number >= isize (answers) || answer_number < 0)
    {
      printf ("There is no answer with such number\n");
      return true;
    }

  res = answer_number;
  return false;
}

static string get_goto (const object_base &pc, const object_base &npc, const dialog_line &line)
{
  const plot_tags_policy *pc_policy = pc.get_policy<plot_tags_policy> ();
  const plot_tags_policy *npc_policy = npc.get_policy<plot_tags_policy> ();

  string curr_goto = "";

  for (const pair<named_tag, string> &cond_goto : line.m_conditional_goto.m_pc_conditions)
    {
      if (pc_policy->has_tag (cond_goto.first.m_name, cond_goto.first.m_value))
        {
          assert_check (curr_goto.empty (), "Conditional gotos should be mutually exclusive");
          curr_goto = cond_goto.second;
        }
    }

  for (const pair<named_tag, string> &cond_goto : line.m_conditional_goto.m_npc_conditions)
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

void talk_policy::talk (object_base &player_character)
{
  unordered_map<string, npc_dialog_line> &lines = get_dialog_tree ().m_lines;

  while (true)
    {
      assert_check (lines.count (get_current_tag ()), "Dialog doesnt have this tag");
      npc_dialog_line &curr_line = lines[get_current_tag ()];

      exec_dialog_line (curr_line, player_character, *this);
      print_text_beats (curr_line.m_text_beats);

      if (curr_line.m_final)
        return;

      string goto_str = get_goto (player_character, *this, curr_line);
      if (!goto_str.empty ())
        {
          get_current_tag () = goto_str;
          continue;
        }

      print_answers (curr_line.m_answers);

      int answer_number = 0;
      if (get_answer_number_or_print_error (curr_line.m_answers, answer_number))
        continue;

      pc_dialog_line &given_answer = curr_line.m_answers[answer_number];
      exec_dialog_line (given_answer, player_character, *this);
      get_current_tag () = get_goto (player_character, *this, given_answer);
    }
}
