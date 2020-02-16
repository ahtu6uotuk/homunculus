#include <fstream>
#include "tga_image.h"

tga_image_t::tga_image_t ()
{

}

void tga_image_t::read (const std::string &file_name)
{
  std::ifstream tga_file;
  tga_file.open (file_name, std::ios::in | std::ios::binary);
  if (!tga_file.is_open ())
    {return;}

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
    {return;}

//  m_header.print_debug_info ();

  if (m_header.m_id_length > 0)
    {
      m_image_id = std::make_unique<char[]> (m_header.m_id_length);
      tga_file.read (m_image_id.get (), m_header.m_id_length);
    }

  if (m_header.m_color_map_type)
    {return;}

  const auto image_data_size = m_header.m_image_width * m_header.m_image_height * 4;
  m_image_data = std::make_unique<tga_image_data_t> (image_data_size);
  tga_file.read (reinterpret_cast<char *> (img.get ()), image_data_size);
  return ;
}

tga_image_t::~tga_image_t()
{

}

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
  fflush (stdout);
}

tga_image_data_t::~tga_image_data_t ()
{

}