#pragma once

#include <unordered_map>
#include <any>
#include <string>

class game_settings_private_t;

enum class game_settings_type_t
{
  renderer,
  resolution,
  count
};

class game_settings_t
{
  std::unordered_map<game_settings_type_t, std::any> m_settings;
  bool m_is_ok = false;
private:
  bool open (const std::string &filename);
public:
  game_settings_t ();
  game_settings_t (const std::string &filename);
  template<typename type_t>
  type_t get (game_settings_type_t setting) const;
  template<typename type_t>
  void set (game_settings_type_t setting);
  bool is_ok () const;
  ~game_settings_t ();
};

