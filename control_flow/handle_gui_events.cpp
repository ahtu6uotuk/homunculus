#include "handle_gui_events.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "control_flow/request_to_calc.h"
#include "engine/engine.h"

std::vector<std::unique_ptr<request_to_calc_base>> handle_gui_events (engine_t &engine)
{
  std::vector<std::unique_ptr<request_to_calc_base>> result;
  auto &camera = engine.get_renderer ().get_camera ();

  sf::Event event;
  while (engine.get_sfml_window ().pollEvent (event))
    {
      switch (event.type)
        {
        case sf::Event::EventType::Closed:
          {
            result.push_back (std::make_unique<request_to_calc_exit> ());
            return result;
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
            if (event.key.code == sf::Keyboard::Key::Right)
              camera.rotate (5.f, 0.f);
            if (event.key.code == sf::Keyboard::Key::Left)
              camera.rotate (-5.f, 0.f);
            if (event.key.code == sf::Keyboard::Key::Up)
              camera.rotate (0.f, 5.f);
            if (event.key.code == sf::Keyboard::Key::Down)
              camera.rotate (0.f, -5.f);
            if (event.key.code == sf::Keyboard::Key::D)
              camera.move (movement_direction_t::RIGHT, 1.f);
            if (event.key.code == sf::Keyboard::Key::A)
              camera.move (movement_direction_t::LEFT, 1.f);
            if (event.key.code == sf::Keyboard::Key::W)
              camera.move (movement_direction_t::FORWARD, 1.f);
            if (event.key.code == sf::Keyboard::Key::S)
              camera.move (movement_direction_t::BACKWARD, 1.f);
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
