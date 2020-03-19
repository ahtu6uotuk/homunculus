#pragma once
#include <memory>
class engine_t;
class request_to_calc_base;

std::unique_ptr<request_to_calc_base> handle_gui_events (engine_t &engine);
