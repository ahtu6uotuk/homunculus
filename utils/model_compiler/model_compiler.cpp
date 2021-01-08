#include <iostream>
#include <vector>
#include "common/common.h"
#include "datastructs/model.h"
#include "datastructs/mesh.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#if defined(__GNUC__) or defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#include "external/tiny_gltf.h"
#pragma GCC diagnostic pop
#endif

void print_usage (const char *exe);
bool check_model_support (const tinygltf::Model &model);
void print_model_info (const tinygltf::Model &model);
auto prepare_model (tinygltf::Model &model);
bool export_model (auto &model);


void print_usage (const char *exe)
{
  std::cout << "Usage: " << exe << " <.gltf file>" << std::endl;
}

bool check_model_support (const tinygltf::Model &model)
{
  do_nothing (model);
  return true;
}

void print_model_info (const tinygltf::Model &model)
{
  std::cout << "Model statistics:" << std::endl;
  std::cout << "Scenes: " << std::to_string (model.scenes.size ()) << std::endl;
  std::cout << "Nodes: " << std::to_string (model.nodes.size ()) << std::endl;
  std::cout << "Animations: " << std::to_string (model.animations.size ()) << std::endl;
  std::cout << "Meshes: " << std::to_string (model.meshes.size ()) << std::endl;
}

auto prepare_model (tinygltf::Model &model)
{
  auto &main_scene = model.scenes.front ();

  for (auto &node_index : main_scene.nodes)
    {
      auto &node = model.nodes[node_index];
      if (node.mesh >= 0)
        {
          do_nothing ();
        }
    }

  for (auto &animation : model.animations)
    {
      do_nothing (animation);
    }


  for (auto &material : model.materials)
    {
      do_nothing (material);
    }

  return 0;
}

bool export_model (auto &model)
{
  do_nothing (model);
  return true;
}

int
main (int argc, char **argv)
{
  if (argc != 2)
    {
      print_usage (argv[0]);
      return 0;
    }

  tinygltf::Model import_model;
  std::string stl_warn = "";
  std::string stl_err = "";

  tinygltf::TinyGLTF loader;
  if (!loader.LoadASCIIFromFile (&import_model, &stl_err, &stl_warn, argv[1]))
    {
      std::cout << "TinyGLTF: failed to parse %s" << std::endl;

      if (!stl_warn.empty ())
        std::cout << "TinyGLTF: warning: " << stl_warn << std::endl;

      if (!stl_err.empty ())
        std::cout << "TinyGLTF: error: " << stl_err << std::endl;
    }

  if (!check_model_support (import_model))
    {
      std::cout << "model_compiler: model has unsupported GLTF features" << std::endl;
      return 0;
    }

  print_model_info (import_model);

  if (import_model.scenes.empty ())
    { std::cout << "No scenes in model!" << std::endl; return 0;}

  auto model_for_export = prepare_model (import_model);

  export_model (model_for_export);

  return 0;
}
