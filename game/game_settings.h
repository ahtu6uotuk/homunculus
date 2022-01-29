#pragma once
#include <string>

enum class game_setting_t
{
  renderer,
  resolution,
  count
};

class game_settings_t
{
public:
  game_settings_t ();
  game_settings_t (const std::string &filename);
  template<typename type_t>
  type_t get (game_setting_t setting) const;
  template<typename type_t>
  void set (game_setting_t setting);
  ~game_settings_t ();
};

