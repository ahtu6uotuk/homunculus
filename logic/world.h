#pragma once

#include "common/common.h"
#include "logic/object/object_heap.h"
#include "logic/object_classes/player.h"

class world_t
{
public:
  world_t (const std::string &story_name);

  err_t switch_level (const std::string &level_to_load);
  err_t load (const std::string &save_name);
  err_t save (const std::string &save_name);

  player_t &get_player ();
  object_heap &get_level ();
  std::vector<object_base *> get_all ();

private:
  struct meta_info;
  bool loaded ();
  err_t load_player (const std::string &save_name);
  err_t load_meta_info (const std::string &save_name);
  err_t load_level (const std::string &save_name);

  const std::string m_story_name;
  std::string m_last_save_name;
  std::unique_ptr<meta_info> m_meta_info;
  std::unique_ptr<player_t> m_player;
  std::unique_ptr<object_heap> m_level;

private:
  struct meta_info
  {
    void build_saveload_tree (saveload_node &node);
    bool loaded ();
    const std::string &get_level ();
    void set_level (const std::string &name);
    std::string m_curr_level;
  };
};
