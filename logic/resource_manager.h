#pragma once
#include <any>
#include <memory>
#include <unordered_map>

#include "common/err_t.h"
#include "common/file_utils.h"
#include "common/template_tricks/has_member.h"
#include "logic/saveload/saveload.h"

class resource_manager
{
  struct resource
  {
    resource (std::unique_ptr<std::any> data) : m_data (std::move (data)) {}
    int m_refcount = 0;
    std::unique_ptr<std::any> m_data;
  };

public:
  static resource_manager &instance ();

  template<typename T>
  T *get_resource (const std::string &asset_name)
  {
    auto it = m_loaded_resources.find (asset_name);
    if (it == m_loaded_resources.end ())
      it = m_loaded_resources.emplace (asset_name, load_new_resource<T> (asset_name)).first;

    it->second.m_refcount++;
    return std::any_cast<T> (it->second.m_data.get ());
  }

  void pop_resource (const std::string &asset_name);

private:
  std::unordered_map<std::string, resource> m_loaded_resources;

  GENERATE_HAS_MEMBER (load_custom)
  template<typename DataT, std::enable_if_t<has_member_load_custom<DataT>::value, int> = 0>
  static err_t load_data_private (const std::string &file_contents, DataT &result)
  {
    return result.load_custom (file_contents);
  }
  template<typename DataT, std::enable_if_t<!has_member_load_custom<DataT>::value, int> = 0>
  static err_t load_data_private (const std::string &file_contents, DataT &result)
  {
    return saveload::load (result, file_contents);
  }

  template<typename DataT>
  static resource load_new_resource (const std::string &asset_name)
  {
    std::unique_ptr<std::any> result = std::make_unique<std::any> (DataT ());
    DataT *typed_data = std::any_cast<DataT> (result.get ());

    std::string file_contents;
    assert_error (from_asset_file (file_contents, asset_name));

    assert_error (load_data_private (file_contents, *typed_data));

    return resource (std::move (result));
  }
};
