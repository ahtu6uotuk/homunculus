#include "resource_manager.h"
#include <fstream>
#include "engine/logger.h"
#include "engine/io/io_utils.h"
#include "engine/io/model_obj.h"
#include "engine/io/tga_image.h"
#include "engine/renderer/shader.h"
#include "engine/renderer/mesh.h"

bool resource_manager_t::is_resource_in_storage (const std::string &filename, unsigned int &resource) const
{
  const auto &it = m_resource_id_storage.find (filename);
  if (it != m_resource_id_storage.cend ())
    {
      resource = m_textures[it->second.m_id];
      return true;
    }
  return false;
}

resource_manager_t::resource_manager_t (logger_t &logger):
  m_logger (logger)
{}

vertex_shader_t *resource_manager_t::get_vertex_shader (const resource_id_t &res_id) const
{
  return m_vertex_shaders[res_id.m_id].get ();
}

fragment_shader_t *resource_manager_t::get_fragment_shader (const resource_id_t &res_id) const
{
  return m_fragment_shaders[res_id.m_id].get ();
}

shader_t *resource_manager_t::get_shader (const resource_id_t &res_id) const
{
  return m_shaders[res_id.m_id].get ();
}

mesh_t *resource_manager_t::get_mesh (const resource_id_t &res_id) const
{
  return m_meshes[res_id.m_id].get ();
}

template<typename T>
bool resource_manager_t::is_resource_in_storage (const std::string &filename, T **resource) const
{
  const auto &it = m_resource_id_storage.find (filename);
  if (it != m_resource_id_storage.cend ())
    {
      if constexpr (std::is_same_v<T, vertex_shader_t>)
        {
          *resource = get_vertex_shader (it->second);
        }
      else if constexpr (std::is_same_v<T, fragment_shader_t>)
        {
          *resource = get_fragment_shader (it->second);
        }
      else if constexpr (std::is_same_v<T, shader_t>)
        {
          *resource = get_shader (it->second);
        }
      else if constexpr (std::is_same_v<T, mesh_t>)
        {
          *resource = get_mesh (it->second);
        }
      return true;
    }

  return false;
}

err_t resource_manager_t::load_vertex_shader (const std::string &filename, vertex_shader_t **vertex_shader)
{
  auto path = std::string ("gamedata/shaders/").append (filename);

  std::string src;
  RETURN_IF_FAIL (read_file_data (path, src));
  auto &vs = m_vertex_shaders.emplace_back (std::make_unique<vertex_shader_t> (src.c_str ()));
  RETURN_IF_FAIL (vs->check ());

  m_logger.print (log_section_t::RESOURCE_MANAGER, log_priority_t::INFO, "load vertex subshader", path);

  m_resource_id_storage.emplace (
        make_pair (path, resource_id_t (resource_type_t::VERTEX_SHADER, m_vertex_shaders.size () -1))
        );

  *vertex_shader = vs.get ();

  return ERR_OK;
}

err_t resource_manager_t::load_fragment_shader (const std::string &filename, fragment_shader_t **fragment_shader)
{
  auto path = std::string ("gamedata/shaders/").append (filename);

  std::string src;
  RETURN_IF_FAIL (read_file_data (path, src));
  auto &fs = m_fragment_shaders.emplace_back (std::make_unique<fragment_shader_t> (src.c_str ()));
  RETURN_IF_FAIL (fs->check ());

  m_logger.print (log_section_t::RESOURCE_MANAGER, log_priority_t::INFO, "load fragment subshader", path);

  m_resource_id_storage.emplace (
        make_pair (path, resource_id_t (resource_type_t::FRAGMENT_SHADER, m_fragment_shaders.size () - 1))
        );

  *fragment_shader = fs.get ();

  return ERR_OK;
}

err_t resource_manager_t::load_shader (const std::string &filename, shader_t **shader)
{
  auto path = std::string ("gamedata/shaders/").append (filename);
  if (is_resource_in_storage (path, shader))
    return ERR_OK;

  m_logger.print (log_section_t::RESOURCE_MANAGER, log_priority_t::INFO, "load shader", path);

  std::ifstream fdata (path);

  if (!fdata.is_open ())
    return std::string ("can't open ").append (path);

  std::string vs_path, fs_path;

  if (!getline (fdata, vs_path))
    return std::string ("can't read ").append (path);

  if (!getline (fdata, fs_path))
    return std::string ("can't read ").append (path);

  vertex_shader_t *vs = nullptr;
  fragment_shader_t *fs = nullptr;

  RETURN_IF_FAIL (load_vertex_shader (vs_path, &vs));
  RETURN_IF_FAIL (load_fragment_shader (fs_path, &fs));

  auto &res = m_shaders.emplace_back (std::make_unique<shader_t> (vs->get_id (), fs->get_id ()));
  RETURN_IF_FAIL (res->check ());

  m_resource_id_storage.emplace (
        make_pair (path, resource_id_t (resource_type_t::SHADER_PROGRAM, m_shaders.size () - 1)
                   ));

  *shader = res.get ();

  return ERR_OK;
}

err_t resource_manager_t::load_mesh (const std::string &filename, mesh_t **mesh)
{
  auto path = std::string ("gamedata/models/").append (filename);

  if (is_resource_in_storage (path, mesh))
    return ERR_OK;

  m_logger.print (log_section_t::RESOURCE_MANAGER, log_priority_t::INFO, "loading mesh", path);

  model_obj_t obj_importer;
  RETURN_IF_FAIL (obj_importer.load (path));
  obj_importer.print_debug_info (m_logger);

  m_meshes.emplace_back (std::make_unique<mesh_t> (obj_importer.to_mesh (m_logger)));
  m_resource_id_storage.emplace (
        make_pair (path, resource_id_t (resource_type_t::MESH, m_meshes.size () - 1))
        );

  *mesh = m_meshes.back ().get ();

  return ERR_OK;
}

err_t resource_manager_t::load_tga_texture (const std::string &filename, unsigned int &texture)
{
  auto path = std::string ("gamedata/textures/").append (filename);

  if (is_resource_in_storage (path, texture))
    {
      return ERR_OK;
    }

  tga_image_t tga;
  RETURN_IF_FAIL (tga.load (path));
  texture = tga.to_gl ();
  m_textures.push_back (texture);
  m_resource_id_storage.emplace (
        make_pair (path, resource_id_t (resource_type_t::TEXTURE, m_textures.size () - 1))
        );

  return ERR_OK;
}

resource_manager_t::~resource_manager_t ()
{}
