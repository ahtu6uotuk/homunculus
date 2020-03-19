#pragma once

#include "common/common.h"
class err_t;

err_t to_file (const std::string &src_string, const std::string &dst_filename);
err_t from_file (std::string &dst_string, const std::string &src_filename);
err_t to_asset_file (const std::string &src_string, const std::string &asset_name);
err_t from_asset_file (std::string &dst_string, const std::string &asset_name);
err_t to_saved_game_file (const std::string &src, const std::string &story, const std::string &save, const std::string &asset);
err_t from_saved_game_file (std::string &dst, const std::string &story, const std::string &save, const std::string &asset);

err_t directory_exists (const std::string &path, bool &res);
err_t create_dir (const std::string &path);
err_t ensure_dir_exists (const std::string &path);
err_t rename (const std::string &old_path, const std::string &new_path);
err_t copy (const std::string &old_path, const std::string &new_path);
err_t remove_dir (const std::string &path);
