#pragma once
#include "common/common.h"
class engine_t;
class request_to_calc_base;

unique_ptr<request_to_calc_base> handle_gui_events (engine_t &engine);
