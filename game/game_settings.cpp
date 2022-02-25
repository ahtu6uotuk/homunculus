#include "game_settings.h"

#include <json/json.h>

#include <fstream>

game_settings_t::game_settings_t () : game_settings_t ("settings.json") {}

game_settings_t::game_settings_t (const std::string &filename)
{
  m_is_ok = open (filename);
}

bool game_settings_t::open (const std::string &filename)
{
  std::ifstream ifs (filename);
  if (!ifs.is_open ())
    return (m_is_ok = false);

  Json::CharReaderBuilder reader_builder;
  Json::Value value;
  if (!Json::parseFromStream (reader_builder, ifs, &value, nullptr))
    return (m_is_ok = false);

  return (m_is_ok = true);
}

bool game_settings_t::is_ok () const
{
  return m_is_ok;
}

game_settings_t::~game_settings_t () = default;
