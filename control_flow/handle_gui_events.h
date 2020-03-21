#pragma once
#include <memory>
#include <vector>
class engine_t;
class request_to_calc_base;

std::vector<std::unique_ptr<request_to_calc_base> > handle_gui_events(engine_t &engine);
