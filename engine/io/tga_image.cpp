#include <fstream>
#include <GL/glew.h>
#include "tga_image.h"

void tga_header_t::print_debug_info () const
{
  auto print_debug_var = [] (const char *name, auto value)
    {
      printf ("%s = %u\n", name, static_cast<unsigned int> (value));
    };
  print_debug_var ("m_id_length", m_id_length);
  print_debug_var ("m_color_map_type", m_color_map_type);
  print_debug_var ("m_image_type", m_image_type);
  print_debug_var ("m_first_entry_index", m_first_entry_index);
  print_debug_var ("m_color_map_length", m_color_map_length);
  print_debug_var ("m_color_map_entry_size", m_color_map_entry_size);
  print_debug_var ("m_x_origin", m_x_origin);
  print_debug_var ("m_y_origin", m_y_origin);
  print_debug_var ("m_image_width", m_image_width);
  print_debug_var ("m_image_height", m_image_height);
  print_debug_var ("m_pixel_depth", m_pixel_depth);
  print_debug_var ("m_descriptor", m_descriptor);
  print_debug_var ("m_descriptor_colors", m_desciptor_bits.m_bpp);
  print_debug_var ("m_descriptor_from_left", m_desciptor_bits.m_from_left);
  print_debug_var ("m_descriptor_from_top", m_desciptor_bits.m_from_top);
  print_debug_var ("m_descriptor_zero", m_desciptor_bits.m_zero);
  fflush (stdout);
}

size_t tga_header_t::get_image_size () const
{
  return m_image_width * m_image_height * (m_pixel_depth + m_desciptor_bits.m_bpp) / 8;
}

tga_image_t::tga_image_t ()
{

}

err_t tga_image_t::load (const std::string &file_name)
{
  std::ifstream tga_file;
  tga_file.open (file_name, std::ios::in | std::ios::binary);
  if (!tga_file.is_open ())
    {return std::string ("can't open ").append (file_name);}

  tga_file.read (reinterpret_cast<char *> (&m_header.m_id_length), sizeof (m_header.m_id_length));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_color_map_type), sizeof (m_header.m_color_map_type));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_image_type), sizeof (m_header.m_image_type));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_first_entry_index), sizeof (m_header.m_first_entry_index));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_color_map_length), sizeof (m_header.m_color_map_length));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_color_map_entry_size), sizeof (m_header.m_color_map_entry_size));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_x_origin), sizeof (m_header.m_x_origin));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_y_origin), sizeof (m_header.m_y_origin));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_image_width), sizeof (m_header.m_image_width));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_image_height), sizeof (m_header.m_image_height));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_pixel_depth), sizeof (m_header.m_pixel_depth));
  tga_file.read (reinterpret_cast<char *> (&m_header.m_descriptor), sizeof (m_header.m_descriptor));

  if (tga_file.fail ())
    {return std::string ("wrong TGA header format ").append (file_name);}

  if (m_header.m_id_length > 0)
    {
      m_image_id = std::make_unique<char[]> (m_header.m_id_length);
      tga_file.read (m_image_id.get (), m_header.m_id_length);
    }

  if (m_header.m_color_map_type)
    {return std::string ("wrong color type in TGA file ").append (file_name);}

//  m_header.print_debug_info ();

  const auto image_data_size = m_header.get_image_size ();
  m_image_data = std::make_unique<unsigned char[]> (image_data_size);
  tga_file.read (reinterpret_cast<char *> (m_image_data.get ()), image_data_size);

  if (m_header.m_image_type != tga_image_type_t::UNCOMPRESSED_TRUE_COLOR)
    return std::string ("unsupported TGA image type ").append (file_name);

  return ERR_OK;
}

std::unique_ptr<unsigned char[]> tga_image_t::move_as_texture_data ()
{
  if (m_header.m_image_type == tga_image_type_t::UNCOMPRESSED_TRUE_COLOR)
    {
      return std::move (m_image_data);
    }
  return nullptr;
}

std::unique_ptr<unsigned char[]> tga_image_t::copy_as_texture_data () const
{
  if (m_header.m_image_type == tga_image_type_t::UNCOMPRESSED_TRUE_COLOR)
    {
      const auto img_size = m_header.get_image_size ();
      auto img = std::make_unique<unsigned char[]> (img_size);
      std::copy_n (m_image_data.get (), img_size, img.get ());
      return std::unique_ptr<unsigned char[]> (img.release ());
    }
  return nullptr;
}

unsigned int tga_image_t::to_gl () const
{
  unsigned int texture = 0;
  glGenTextures (1, &texture);
  glBindTexture (GL_TEXTURE_2D, texture);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, m_header.m_image_width, m_header.m_image_height, 0,
                GL_BGRA, GL_UNSIGNED_BYTE, m_image_data.get ());
  // ... nice trilinear filtering ...
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  // ... which requires mipmaps. Generate them automatically.
  glGenerateMipmap (GL_TEXTURE_2D);
  return texture;
}

tga_image_t::~tga_image_t ()
{}
