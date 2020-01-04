#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
#include "logic/saveload.h"

class health_policy : virtual public object_base
{
public:
  /// Every policy should have these two functions.
  virtual string describe_policy () const = 0;
  virtual void build_saveload_tree_policy (saveload_node &node) = 0;

  /// These two are unique for the policy.
  /// Names of unique functions should not collide.
  virtual void take_damage (int damage) = 0;
  virtual bool is_alive () = 0;
};



class hp_health_policy : public health_policy
{
public:
  /// This operator is here for testing purposes mostly (to compare two heaps).
  /// It is rather annoying, but for now it should stay.
  bool operator== (const hp_health_policy &other) const { return m_hp == other.m_hp; }
  string describe_policy () const override { return string_printf ("Has %d hp\n", m_hp); }
  virtual void build_saveload_tree_policy (saveload_node &node) override
  {
    node.add (m_hp, "hp");
  }

  void take_damage (int damage) override { m_hp -= damage; }
  bool is_alive() override { return m_hp > 0; }
  void set_hp (int hp) { m_hp = hp; }
  int get_hp () { return m_hp; }

private:
  /// Yes, policies can store data.
  int m_hp = 0;
};

class immortal_bragging_health_policy : public health_policy
{
public:
  bool operator== (const immortal_bragging_health_policy &) const { return true; }
  string describe_policy () const override { return "Is immortal\n"; }
  virtual void build_saveload_tree_policy (saveload_node &) override {}

  void take_damage (int) override
  {
    cout << "TRY AS YOU MIGHT, MORTAL, YOU CANNOT HURT ME" << endl;
  }
  bool is_alive() override { return true; }
};

class hit_count_health_policy : public health_policy
{
public:
  bool operator== (const hit_count_health_policy &other) const { return m_hits_remaining == other.m_hits_remaining; }
  string describe_policy () const override { return string_printf ("Can take %d more hits\n", m_hits_remaining); }
  virtual void build_saveload_tree_policy (saveload_node &node) override
  {
    node.add (m_hits_remaining, "hits_remaining");
  }

  void take_damage (int) override { m_hits_remaining -= 1; }
  bool is_alive() override { return m_hits_remaining > 0; }
  void set_hits_remaining (int hits_remaining) { m_hits_remaining = hits_remaining; }
  int get_hits_remaining () { return m_hits_remaining; }

private:
  int m_hits_remaining = 0;
};
