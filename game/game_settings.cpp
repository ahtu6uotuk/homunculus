#include "game_settings.h"
#include <json/json.h>
#include <fstream>

game_settings_t::game_settings_t () : game_settings_t ("settings.json") {}

game_settings_t::game_settings_t (const std::string &filename)
{
  Json::CharReaderBuilder reader_builder;
  Json::Value value;
  std::ifstream ifstream (filename);
  Json::parseFromStream (reader_builder, ifstream, &value, nullptr);
}

game_settings_t::~game_settings_t () = default;
