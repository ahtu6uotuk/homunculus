#pragma once
#include <memory>
#include <unordered_map>

#include "common/err_t.h"
#include "common/file_utils.h"
#include "common/template_tricks/has_member.h"
#include "resource/saveload/saveload.h"

class resource_manager
{
  struct resource
  {
    resource (void *data) : m_data (data) {}
    int m_refcount = 0;
    void *m_data;
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
    return static_cast<T *> (it->second.m_data);
  }

  template<typename T>
  void pop_resource (const std::string &asset_name)
  {
    auto it = m_loaded_resources.find (asset_name);
    assert_check (it != m_loaded_resources.end (), "Reference count went wrong");

    if (--it->second.m_refcount == 0)
      {
        delete static_cast<T *> (it->second.m_data);
        m_loaded_resources.erase (it);
      }
  }

private:
  std::unordered_map<std::string, resource> m_loaded_resources;

  GENERATE_HAS_MEMBER (load_custom)
  template<typename DataT, std::enable_if_t<has_member_load_custom<DataT>::value, int> = 0>
  static err_t load_data_private (const std::string &asset_name, DataT &result)
  {
    return result.load_custom (asset_name);
  }
  template<typename DataT, std::enable_if_t<!has_member_load_custom<DataT>::value, int> = 0>
  static err_t load_data_private (const std::string &asset_name, DataT &result)
  {
    std::string file_contents;
    assert_error (from_gamedata_file (file_contents, asset_name));

    return saveload::load (result, file_contents);
  }

  template<typename DataT>
  static resource load_new_resource (const std::string &asset_name)
  {
    DataT *result = new DataT;
    assert_error (load_data_private (asset_name, *result));
    return resource (result);
  }
};
