#pragma once
#ifndef BITVIEW_T_H
#define BITVIEW_T_H
#include <cstddef>

class bitview_t
{
  class iterator
  {
    std::byte &m_byte;
    unsigned int m_pos;
  public:
    iterator () = delete;
    iterator (std::byte &byte, std::size_t pos): m_byte (byte), m_pos (pos) {}
    bool operator* () { return (std::to_integer<int> (m_byte) & (1 << m_pos)); }
    bool operator== (const bitview_t::iterator &b) const { return m_byte == b.m_byte && m_pos == b.m_pos; }
    bool operator!= (const bitview_t::iterator &b) const { return !((*this)==b); }
    iterator &operator++ ()
    {
      m_pos--;
      return *this;
    }
  };

  std::byte &m_byte;
public:
  bitview_t (std::byte &byte): m_byte (byte) {}
  bitview_t::iterator begin ()
  {
    return cbegin ();
  }
  bitview_t::iterator end ()
  {
    return cend ();
  }
  bitview_t::iterator cbegin () const
  {
    return bitview_t::iterator (m_byte, 7);
  }
  bitview_t::iterator cend () const
  {
    return bitview_t::iterator (m_byte, 0);
  }
  bool at (int index) const { return std::to_integer<int> (m_byte) & (1 << index);}
};

#endif // BITVIEW_T_H
