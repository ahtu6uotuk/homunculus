#include "file_utils.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "common/string/string_utils.h"
#include "common/err_t.h"

using namespace std::filesystem;

err_t directory_exists (const std::string &path, bool &res)
{
  std::error_code err;

  bool r = exists (path, err);
  if (err)
    return string_printf (
        "Couldn't check if directory \"%s\" exists: %s", path.c_str (), err.message ().c_str ());

  if (!r)
    {
      res = false;
      return ERR_OK;
    }

  r = is_directory (path, err);
  if (err)
    return string_printf (
        "Couldn't check if directory \"%s\" exists: %s", path.c_str (), err.message ().c_str ());

  res = r;
  return ERR_OK;
}
err_t create_dir (const std::string &path)
{
  std::error_code err;

  bool r = create_directories (path, err);
  if (err)
    return string_printf (
        "Couldn't create directory \"%s\": %s", path.c_str (), err.message ().c_str ());

  assert_check (r, "Huh, I thought this would always be true here");
  return ERR_OK;
}
err_t ensure_dir_exists (const std::string &path)
{
  bool r;
  std::string dir_path = std::filesystem::path (path).remove_filename ().string();

  RETURN_IF_FAIL (directory_exists (dir_path, r));
  if (!r)
    RETURN_IF_FAIL (create_dir (dir_path));

  return ERR_OK;
}

err_t copy (const std::string &old_path, const std::string &new_path)
{
  std::error_code err;

  if (is_directory (new_path))
    RETURN_IF_FAIL (remove_dir (new_path));

  copy_options options
      = copy_options::recursive | copy_options::overwrite_existing;
  copy (old_path, new_path, options, err);
  if (err)
    return string_printf (
        "Couldn't copy \"%s\" to \"%s\": %s", old_path.c_str (), new_path.c_str (),
        err.message ().c_str ());

  return ERR_OK;
}
err_t rename (const std::string &old_path, const std::string &new_path)
{
  std::error_code err;

  rename (old_path, new_path, err);
  if (err)
    return string_printf (
        "Couldn't rename \"%s\" to \"%s\": %s", old_path.c_str (), new_path.c_str (),
        err.message ().c_str ());

  return ERR_OK;
}
err_t remove_dir (const std::string &path)
{
  std::error_code err;

  remove_all (path, err);
  if (err)
    return string_printf (
        "Couldn't remove directory \"%s\": %s", path.c_str (), err.message ().c_str ());

  return ERR_OK;
}

err_t to_asset_file (const std::string &src_string, const std::string &asset_name)
{
  return to_file (src_string, get_assets_path_prefix () + asset_name + ".xml");
}
err_t from_asset_file (std::string &dst_string, const std::string &asset_name)
{
  return from_file (dst_string, get_assets_path_prefix () + asset_name + ".xml");
}
err_t to_saved_game_file (const std::string &src, const std::string &story, const std::string &save, const std::string &asset)
{
  return to_file (src, get_saved_game_path_prefix () + story + "/" + save + "/" + asset + ".xml");
}
err_t from_saved_game_file (std::string &dst, const std::string &story, const std::string &save, const std::string &asset)
{
  return from_file (dst, get_saved_game_path_prefix () + story + "/" + save + "/" + asset + ".xml");
}

err_t to_file (const std::string &src_string, const std::string &dst_filename)
{
  RETURN_IF_FAIL (ensure_dir_exists (path (dst_filename).remove_filename ().string()));

  std::fstream file_stream;
  file_stream.open (dst_filename, std::ios::out);
  if (!file_stream.is_open ())
    return string_printf ("Couldn't open file for writing %s", dst_filename.c_str ());

  file_stream << src_string;
  file_stream.flush ();
  file_stream.close ();

  return ERR_OK;
}

err_t from_file (std::string &dst_string, const std::string &src_filename)
{
  std::fstream file_stream;

  file_stream.open (src_filename, std::ios_base::in);
  if (!file_stream.is_open ())
    return string_printf ("Couldn't open file for reading %s", src_filename.c_str ());

  std::stringstream buffer;
  buffer << file_stream.rdbuf();

  dst_string = buffer.str ();
  file_stream.close ();

  return ERR_OK;
}
