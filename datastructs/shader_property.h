#pragma once
#ifndef SHADER_PROPERTY_H
#define SHADER_PROPERTY_H

/// @brief
/// Virtual base class for all shader properties
class shader_property_t
{
  unsigned int m_id; ///< unique GL uniform ID
public:
  shader_property_t () = delete;
  shader_property_t (const unsigned int id);
  unsigned int get_id () const;
  virtual void use () = 0;
  virtual ~shader_property_t () = 0;
};

// TODO: use C++20 concepts here
// GCC >= 10
// MSVC ?
template<typename T>
class shader_basic_property_t : public shader_property_t
{
  T m_value;
public:
  shader_basic_property_t () = delete;
  shader_basic_property_t (const T &value): m_value (value) {}
  void use () final;
};

#endif // SHADER_PROPERTY_H
