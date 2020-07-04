#include "world.h"

#include <filesystem>

#include "common/err_t.h"
#include "common/file_utils.h"

const int player_id = 0;

const std::string &world_t::meta_info::get_level ()
{
  assert_check (loaded (), "Sanity");
  return m_curr_level;
}

void world_t::meta_info::set_level (const std::string &name)
{
  assert_check (!name.empty (), "Level should have a valid name");
  m_curr_level = name;
}

int world_t::meta_info::gen_id ()
{
  assert_check (loaded (), "Sanity");
  return ++m_max_id;
}

bool world_t::meta_info::loaded () { return !m_curr_level.empty () && m_max_id != -1; }

void world_t::meta_info::build_saveload_tree (saveload::node_t &node)
{
  saveload::add (node, m_curr_level, "current_level_name");
  saveload::add (node, m_max_id, "max_id");
}

world_t::world_t (const std::string &story_name) : m_story_name (story_name)
{
  assert_check (!m_story_name.empty (), "Story should have a valid name");
}

player_t &world_t::get_player ()
{
  assert_check (loaded (), "Sanity");
  player_t *pl = get_by_id<player_t> (player_id);
  assert_check (pl, "Player should be on current level");
  return *pl;
}

object_heap &world_t::get_level ()
{
  assert_check (loaded (), "Sanity");
  return *m_level;
}

int world_t::gen_id ()
{
  assert_check (loaded (), "Sanity");
  return m_meta_info->gen_id ();
}

object_base *world_t::get_by_id (int id) { return m_level->get (id); }

bool world_t::loaded ()
{
  if (!m_last_save_name.empty () && m_level && m_meta_info && m_meta_info->loaded ())
    return true;

  if (m_last_save_name.empty () && !m_level && !m_meta_info)
    return false;

  assert_check (false, "Invalid state");
  return false;
}

err_t world_t::load (const std::string &save_name)
{
  assert_check (!loaded (), "These should be empty before loading");

  std::function<err_t (err_t)> clear_if_fail = [this] (err_t prev_err) {
    if (prev_err.ok ())
      return ERR_OK;
    m_last_save_name = "";
    m_meta_info.reset ();
    m_level.reset ();
    return prev_err;
  };

  m_last_save_name = save_name;
  RETURN_IF_FAIL (clear_if_fail (load_meta_info (save_name)));
  RETURN_IF_FAIL (clear_if_fail (load_level (save_name)));

  return ERR_OK;
}

err_t world_t::load_meta_info (const std::string &save_name)
{
  assert_check (!m_meta_info, "This should be empty");
  std::unique_ptr<meta_info> new_info (new meta_info);
  std::string buffer;

  RETURN_IF_FAIL (from_saved_game_file (buffer, m_story_name, save_name, "meta_info"));
  RETURN_IF_FAIL (saveload::load (*new_info, buffer));

  m_meta_info = move (new_info);

  return ERR_OK;
}

err_t world_t::load_level (const std::string &save_name)
{
  assert_check (!m_level, "This should be empty");
  std::unique_ptr<object_heap> new_level (new object_heap);
  std::string buffer;

  RETURN_IF_FAIL (from_saved_game_file (buffer, m_story_name, save_name, m_meta_info->get_level ()));
  RETURN_IF_FAIL (saveload::load (*new_level, buffer));

  m_level = move (new_level);
  m_level->set_id_generator ([this] () { return gen_id (); });

  return ERR_OK;
}

err_t world_t::save (const std::string &save_name)
{
  assert_check (loaded (), "Load a game first");

  std::string meta_info_buffer;
  std::string player_buffer;
  std::string level_buffer;

  RETURN_IF_FAIL (saveload::save (*m_meta_info, meta_info_buffer));
  RETURN_IF_FAIL (saveload::save (*m_level, level_buffer));

  if (m_last_save_name != save_name)
    {
      std::string old_save_path = get_saved_game_path_prefix () + m_story_name + "/" + m_last_save_name;
      std::string new_save_path = get_saved_game_path_prefix () + m_story_name + "/" + save_name;
      RETURN_IF_FAIL (copy (old_save_path, new_save_path));
      m_last_save_name = save_name;
    }

  RETURN_IF_FAIL (to_saved_game_file (meta_info_buffer, m_story_name, save_name, "meta_info"));
  RETURN_IF_FAIL (to_saved_game_file (level_buffer, m_story_name, save_name, m_meta_info->get_level ()));

  return ERR_OK;
}

err_t world_t::switch_level (const std::string &level_to_load)
{
  assert_check (loaded (), "Load a game first");
  RETURN_IF_FAIL (save ("_autosave"));

  std::string old_level_name = m_meta_info->get_level ();
  std::unique_ptr<object_heap> old_level = move (m_level);

  m_meta_info->set_level (level_to_load);
  err_t err = load_level (m_last_save_name);

  if (!err.ok ())
    {
      m_meta_info->set_level (old_level_name);
      m_level = move (old_level);
      m_level->set_id_generator ([this] () { return gen_id (); });
      return err;
    }

  return ERR_OK;
}
