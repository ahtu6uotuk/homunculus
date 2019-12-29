#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "common/common.h"
#include "logic/object/object.h"
#include "logic/policies/health_policy.h"
#include "common/string/string_utils.h"

class talk_policy : virtual public object_base
{
public:
  virtual string describe_policy () const = 0;
  virtual void build_saveload_tree_policy (saveload_node &node) = 0;

  virtual bool has_something_to_say () = 0;
  virtual std::string speak () = 0;
};

class about_health_talk_policy : public talk_policy
{
public:
  bool operator== (const about_health_talk_policy &) const { return true; }
  string describe_policy () const override { return "Likes to talk about his health\n"; }
  void build_saveload_tree_policy (saveload_node &) override {}

  bool has_something_to_say () override
  {
    /// This policy references another policy!
    /// So you can define different intractions between them.
    /// If class does not have such policy, it will just return nullptr.
    return get_policy<health_policy> ()->is_alive ();
  }
  std::string speak () override
  {
    /// Example below is a bit much, but it shows that you
    /// can use another policy as specifically as you want.
    /// You probably shouldn't though.
    health_policy *health_p = get_policy<health_policy> ();

    if (!health_p)
      return "I guess I dont care much about my health, huh\n";

    if (dynamic_cast<hp_health_policy *> (health_p))
      return string_printf (
          "I have %d hp left, dont hit me too hard!\n",
          dynamic_cast<hp_health_policy *> (health_p)->get_hp ());

    if (dynamic_cast<hit_count_health_policy *> (health_p))
      return string_printf (
          "I can take %d more hits. I dont care how hard you hit me.\n",
          dynamic_cast<hit_count_health_policy *> (health_p)->get_hits_remaining ());

    if (dynamic_cast<immortal_bragging_health_policy *> (health_p))
      return "I AM IMMORTAL, HUMAN! BOW BEFORE ME\n";

    return "Huh, this developer sucks and missed a policy";
  }
};

class weather_talk_policy : public talk_policy
{
public:
  bool operator== (const weather_talk_policy &other) const { return m_curr_replic_number == other.m_curr_replic_number; }
  string describe_policy () const override { return "Likes to talk about weather\n"; }
  void build_saveload_tree_policy (saveload_node &node) override
  {
    node.add (m_curr_replic_number, "replic_num");
  }

  bool has_something_to_say () override
  {
    return m_curr_replic_number < isize (m_replics);
  }
  std::string speak () override
  {
    assert_check (m_curr_replic_number < isize (m_replics), "No more replics");

    string postfix;
    if (get_policy<health_policy> () && !get_policy<health_policy> ()->is_alive ())
      postfix = "Im dead, by the way. That hurt!\n";

    return m_replics[m_curr_replic_number++] + postfix;
  }

private:
  vector<string> m_replics =
  {
    "Hey, nice to meet you.\n",
    "The weather is nice today, isn't it?\n",
    "I guess I don't have much to say, huh?\n"
      };
  int m_curr_replic_number = 0;
};

