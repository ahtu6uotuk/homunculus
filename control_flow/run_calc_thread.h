#pragma once

#include "common/common.h"

class thread_info_t;
class control_flow;

void run_calc_thread (unique_ptr<thread_info_t> thr_info, control_flow &flow);
