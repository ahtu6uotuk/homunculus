#pragma once
#include <iostream>

#include "common/common.h"
#include "common/string/string_utils.h"
#include "logic/object/object.h"
#include "logic/saveload/saveload.h"

class health_policy : virtual public object_base
{
public:
  virtual string policy_describe () const = 0;
  virtual void policy_build_saveload_tree (saveload_node &node) = 0;
  vector<interaction> policy_get_interactions ()
  {
    return {interaction ("Hit", [this] (object_base &pc) { get_hit_by (pc); })};
  }

  virtual void get_hit_by (object_base &character) = 0;
  virtual bool is_alive () = 0;
};

class hp_health_policy : public health_policy
{
public:
  bool operator== (const hp_health_policy &other) const { return m_hp == other.m_hp; }
  string policy_describe () const override { return string_printf ("Has %d hp", m_hp); }
  void policy_build_saveload_tree (saveload_node &node) override { node.add (m_hp, "hp"); }

  void get_hit_by (object_base &) override { m_hp -= 10; }
  bool is_alive() override { return m_hp > 0; }
  void set_hp (int hp) { m_hp = hp; }
  int get_hp () { return m_hp; }

private:
  int m_hp = 0;
};

class hit_count_health_policy : public health_policy
{
public:
  bool operator== (const hit_count_health_policy &other) const { return m_hits_remaining == other.m_hits_remaining; }
  string policy_describe () const override { return string_printf ("Can take %d more hits\n", m_hits_remaining); }
  virtual void policy_build_saveload_tree (saveload_node &node) override
  {
    node.add (m_hits_remaining, "hits_remaining");
  }

  void get_hit_by (object_base &) override { m_hits_remaining -= 1; }
  bool is_alive() override { return m_hits_remaining > 0; }
  void set_hits_remaining (int hits_remaining) { m_hits_remaining = hits_remaining; }
  int get_hits_remaining () { return m_hits_remaining; }

private:
  int m_hits_remaining = 0;
};
