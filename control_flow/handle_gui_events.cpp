#include "handle_gui_events.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "control_flow/request_to_calc.h"
#include "engine/engine.h"

unique_ptr<request_to_calc_base> handle_gui_events (engine_t &engine)
{
  unique_ptr<request_to_calc_base> result (new request_to_calc_empty ());

  sf::Event event;
  while (engine.get_sfml_window ().pollEvent (event))
    {
      switch (event.type)
        {
        case sf::Event::EventType::Closed:
          {
            result.reset (new request_to_calc_exit ());
            break;
          }
        case sf::Event::EventType::Resized:
          {
            engine.get_gui_system ().resize (event.size.width, event.size.height);
            break;
          }
        case sf::Event::EventType::MouseMoved:
          {
            engine.get_gui_system ().handle_mouse_move_event (event.mouseMove.x, event.mouseMove.y);
            break;
          }
        case sf::Event::EventType::MouseButtonPressed:
          {
            if (event.mouseButton.button == sf::Mouse::Left)
              engine.get_gui_system ().handle_mouse_press_event (event.mouseButton.x, event.mouseButton.y);
            break;
          }
        case sf::Event::EventType::MouseButtonReleased:
          {
            break;
          }
        case sf::Event::EventType::KeyPressed:
          {
            do_nothing ();
            break;
          }
        case sf::Event::EventType::KeyReleased:
          {
            do_nothing ();
            break;
          }
        default:
          {
            do_nothing ();
          }
        }
    }
  return result;
}
