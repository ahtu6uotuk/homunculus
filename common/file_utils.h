#pragma once

#include "common/common.h"
class err_t;

err_t to_file (const string &src_string, const string &dst_filename);
err_t from_file (string &dst_string, const string &src_filename);
err_t to_asset_file (const string &src_string, const string &asset_name);
err_t from_asset_file (string &dst_string, const string &asset_name);
err_t to_saved_game_file (const string &src, const string &story, const string &save, const string &asset);
err_t from_saved_game_file (string &dst, const string &story, const string &save, const string &asset);

err_t directory_exists (const string &path, bool &res);
err_t create_dir (const string &path);
err_t ensure_dir_exists (const string &path);
err_t rename (const string &old_path, const string &new_path);
err_t copy (const string &old_path, const string &new_path);
err_t remove_dir (const string &path);
