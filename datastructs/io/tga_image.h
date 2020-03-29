#pragma once

#include <memory>

#include "common/err_t.h"

enum class tga_image_type_t : uint8_t
{
  NO_IMAGE_DATA = 0,
  UNCOMPRESSED_COLOR_MAPPED = 1,
  UNCOMPRESSED_TRUE_COLOR = 2,
  UNCOMPRESSED_BLACK_AND_WHITE = 3,
  RLE_COLOR_MAPPED = 9,
  RLE_TRUE_COLOR = 10,
  RLE_BLACK_AND_WHITE = 11
};

///@brief Base class for TGA color map
/// @details Not implemented yet
class tga_color_map_data_t
{};

///@brief TGA file header
///@details This struct stores all info about TGA image file
struct tga_header_t
{
  unsigned char m_id_length; ///< length of image ID in bytes
  unsigned char m_color_map_type; ///< type of color map (0 for True-color, 1 for pallete)
  tga_image_type_t m_image_type; ///< type of image data
  unsigned short m_first_entry_index; ///< index of the first color map entry
  unsigned short m_color_map_length; ///< number of entries in color map
  unsigned char m_color_map_entry_size; ///< size of entry in color map
  unsigned short m_x_origin; ///< X-origin of image
  unsigned short m_y_origin; ///< Y-origin of image
  unsigned short m_image_width; ///< image width
  unsigned short m_image_height; ///< image height
  unsigned char m_pixel_depth; ///< image pixel color depth
  union
  {
    struct // please make this less weird, clang code model doesnt get this and highlighting is fucked up
    {
      unsigned char m_bpp : 2;
      bool m_from_left : 1;
      bool m_from_top : 1;
      unsigned char m_zero : 2;
    } m_desciptor_bits;
    unsigned char m_descriptor;
  };
  void print_debug_info () const;
  size_t get_image_size () const;
};

///@brief TGA image class
class tga_image_t
{
  tga_header_t m_header;
  std::unique_ptr<char[]> m_image_id = nullptr;
  std::unique_ptr<tga_color_map_data_t> m_color_map_data = nullptr;
  std::unique_ptr<unsigned char[]> m_image_data = nullptr;
public:
  tga_image_t ();
  err_t load (const std::string &file_contents);
  std::unique_ptr<unsigned char[]> move_as_texture_data ();
  std::unique_ptr<unsigned char[]> copy_as_texture_data () const;
  unsigned int to_gl () const;
  ~tga_image_t ();
};
