#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <unordered_map>
#include <vector>
#include "common/err_t.h"
#include "engine/renderer/shader_fwd.h"

class logger_t;
class mesh_t;

enum class resource_type_t
{
  VERTEX_SHADER,
  FRAGMENT_SHADER,
  SHADER_PROGRAM,
  MESH
};

struct resource_id_t
{
  resource_type_t m_type;
  unsigned int m_id;
  resource_id_t (resource_type_t res_type, unsigned int id): m_type (res_type), m_id (id) {}
};

class resource_manager_t
{
  logger_t &m_logger; ///< reference to engine logger for info messages
  unordered_map<string, resource_id_t> m_resource_id_storage;
  vector<unique_ptr<vertex_shader_t>> m_vertex_shaders;
  vector<unique_ptr<fragment_shader_t>> m_fragment_shaders;
  vector<unique_ptr<shader_t>> m_shaders;
  vector<unique_ptr<mesh_t>> m_meshes;
private:
  template<typename T>
  bool is_resource_in_storage (const string &filename, T **resource) const;
public:
  resource_manager_t (logger_t &logger);
  resource_manager_t (const resource_manager_t &) = delete;
  resource_manager_t (resource_manager_t &&) = delete;

  fragment_shader_t *get_fragment_shader (const resource_id_t &res_id) const;
  vertex_shader_t *get_vertex_shader (const resource_id_t &res_id) const;
  shader_t *get_shader (const resource_id_t &res_id) const;
  mesh_t *get_mesh (const resource_id_t &res_id) const;

  err_t load_vertex_shader (const string &filename, vertex_shader_t **vertex_shader);
  err_t load_fragment_shader (const string &filename, fragment_shader_t **fragment_shader);
  err_t load_shader (const string &filename, shader_t **shader);
  err_t load_mesh (const string &filename, mesh_t **mesh);

  ~resource_manager_t ();
};

#endif // RESOURCE_MANAGER_H
