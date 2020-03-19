#pragma once

#include <SFML/Window.hpp>
#include "common/common.h"

class event_t
{
public:
  event_t ();

  event_t (const event_t &other) : m_event (other.m_event)
  {
    assert_check (false, "I thought i moved them");
  }
  event_t (event_t &&other) : m_event (std::move (other.m_event)) {}

private:
  sf::Event m_event;
};
