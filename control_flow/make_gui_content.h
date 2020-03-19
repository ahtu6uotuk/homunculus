#pragma once

#include <memory>
class gui_context_t;
class engine_t;
class world_t;
class thread_info_t;
class request_to_gui_base;

void make_gui_content (engine_t &engine, world_t &world, thread_info_t &thr_info, std::unique_ptr<request_to_gui_base> &res);
