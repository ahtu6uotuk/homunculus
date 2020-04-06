#include "handle_gui_events.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "control_flow/request_to_calc.h"
#include "engine/engine.h"
#include "world/world.h"
#include "world/policies/player_choose_action_policy.h"

static std::unique_ptr<request_to_calc_base> request_player_action (std::unique_ptr<action> action)
{
  return std::unique_ptr<request_to_calc_base> (
      new request_to_calc_t ([actcopy = std::move (action)] (world_t &world, thread_info_t &) mutable {
        player_choose_action_policy *pl = world.get_player ().get_policy<player_choose_action_policy> ();
        pl->add_buffered_action (std::move (actcopy));
        return ERR_OK;
      }));
}

std::vector<std::unique_ptr<request_to_calc_base>> handle_gui_events (engine_t &engine)
{
  std::vector<std::unique_ptr<request_to_calc_base>> result;
//  auto &camera = engine.get_renderer ().get_camera ();

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
          //            if (event.key.code == sf::Keyboard::Key::Right)
          //              camera.rotate (5.f, 0.f);
          //            if (event.key.code == sf::Keyboard::Key::Left)
          //              camera.rotate (-5.f, 0.f);
          //            if (event.key.code == sf::Keyboard::Key::Up)
          //              camera.rotate (0.f, 5.f);
          //            if (event.key.code == sf::Keyboard::Key::Down)
          //              camera.rotate (0.f, -5.f);
          if (event.key.code == sf::Keyboard::Key::Right)
            result.push_back (request_player_action (std::make_unique<rotate_action> (5.f, 0.f)));
          if (event.key.code == sf::Keyboard::Key::Left)
            result.push_back (request_player_action (std::make_unique<rotate_action> (-5.f, 0.f)));
          if (event.key.code == sf::Keyboard::Key::Up)
            result.push_back (request_player_action (std::make_unique<rotate_action> (0.f, 5.f)));
          if (event.key.code == sf::Keyboard::Key::Down)
            result.push_back (request_player_action (std::make_unique<rotate_action> (0.f, -5.f)));

          if (event.key.code == sf::Keyboard::Key::D)
            result.push_back (request_player_action (std::make_unique<move_action> (movement_direction_t::RIGHT, 1.f, 0.1f)));
          if (event.key.code == sf::Keyboard::Key::A)
            result.push_back (request_player_action (std::make_unique<move_action> (movement_direction_t::LEFT, 1.f, 0.1f)));
          if (event.key.code == sf::Keyboard::Key::W)
            result.push_back (request_player_action (std::make_unique<move_action> (movement_direction_t::FORWARD, 1.f, 0.1f)));
          if (event.key.code == sf::Keyboard::Key::S)
            result.push_back (request_player_action (std::make_unique<move_action> (movement_direction_t::BACKWARD, 1.f, 0.1f)));
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
