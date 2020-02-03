#pragma once

#include "common/common.h"
class gui_context_t;
class engine_t;
class world_t;
class thread_info_t;

void make_gui_content (engine_t &engine, world_t &world, thread_info_t &thr_info, unique_ptr<gui_context_t> &result);
