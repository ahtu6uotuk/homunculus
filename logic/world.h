#pragma once

#include "common/common.h"
#include "logic/object/object_heap.h"
#include "logic/object_classes/player.h"

class world_t
{
public:
  world_t (const string &story_name);

  err_t switch_level (const string &level_to_load);
  err_t load (const string &save_name);
  err_t save (const string &save_name);

  player_t &get_player ();
  object_heap &get_level ();

private:
  struct meta_info;
  bool loaded ();
  err_t load_player (const string &save_name);
  err_t load_meta_info (const string &save_name);
  err_t load_level (const string &save_name);

  const string m_story_name;
  string m_last_save_name;
  unique_ptr<meta_info> m_meta_info;
  unique_ptr<player_t> m_player;
  unique_ptr<object_heap> m_level;

private:
  struct meta_info
  {
    void build_saveload_tree (saveload_node &node);
    bool loaded ();
    const string &get_level ();
    void set_level (const string &name);
    string m_curr_level;
  };
};
