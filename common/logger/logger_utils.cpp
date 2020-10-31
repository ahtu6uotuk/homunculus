#include "logger_utils.h"

#include <map>
#include <vector>

#include "common/type_traits_ext.h"
#include "common/logger/logger.h"
#include "datastructs/vertex_data.h"

using std::to_string;

inline std::string make_string (const glm::vec3 vec3)
{
  std::string buffer ("");
  buffer.append (to_string (vec3.x)).append (" ");
  buffer.append (to_string (vec3.y)).append (" ");
  buffer.append (to_string (vec3.z));
  return buffer;
}

inline std::string make_string (const glm::vec2 &vec2)
{
  std::string buffer ("");
  buffer.append (to_string (vec2.x)).append (" ");
  buffer.append (to_string (vec2.y));
  return buffer;
}

inline std::string make_string (const vertex_data_t &vertex_data)
{
  std::string buffer ("m_vertex: ");
  buffer.append (make_string (vertex_data.m_vertex));
  buffer.append (", m_normal: ");
  buffer.append (make_string (vertex_data.m_normal));
  buffer.append (", uv: ");
  buffer.append (make_string (vertex_data.m_uv));
  return buffer;
}

inline std::string make_string (const vertex_data_view_t &vertex_data)
{
  std::string buffer ("m_vertex: ");
  buffer.append (make_string (*vertex_data.m_vertex));
  buffer.append (", m_normal: ");
  buffer.append (make_string (*vertex_data.m_normal));
  buffer.append (", uv: ");
  buffer.append (make_string (*vertex_data.m_uv));
  return buffer;
}

inline std::string make_string (const std::pair<vertex_data_view_t, unsigned int> pair)
{
  return make_string (pair.first).append (" : ").append (to_string (pair.second));
}

template<typename T>
inline std::string to_stl_string (const T &data)
{
  if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, char *>)
    {
      return data;
    }
  else if constexpr (std::is_fundamental_v<T> || std::is_fundamental_v<std::remove_reference_t<T>>)
    {
      return to_string (data);
    }
  else if constexpr (is_iterable_v<T>)
    {
      std::string buffer;
      buffer.append (": \n");
      size_t i = 0;
      for (const auto &value : data)
        {
          buffer.append (to_string (i)).append (": ");
          buffer.append (to_stl_string<std::remove_reference_t<decltype (value)>> (value)).append ("\n");
          i++;
        }
      return buffer;
    }
  else
    {
      return make_string (data);
    }
  return "internal logger error";
}

template<typename T>
void logger_utils::print_var_info (const char *var_name, const T &var_value)
{
  logger_t::instance ().print_plain (var_name, to_stl_string (var_value));
}

template void logger_utils::print_var_info (const char *, const bool &);
template void logger_utils::print_var_info (const char *, const unsigned int &);
#if _WIN64 || !_WIN32
template void logger_utils::print_var_info (const char *, const std::size_t &);
#endif
template void logger_utils::print_var_info (const char *, const std::string &);
template void logger_utils::print_var_info (const char *, const std::vector<vertex_data_t> &);
template void logger_utils::print_var_info (const char *, const std::vector<unsigned int> &);
template void logger_utils::print_var_info (const char *, const std::vector<glm::vec3> &);
template void logger_utils::print_var_info (const char *, const std::vector<glm::vec2> &);
template void logger_utils::print_var_info (const char *, const vertex_data_view_t &);
template void logger_utils::print_var_info (const char *, const std::map<vertex_data_view_t, unsigned int> &);
