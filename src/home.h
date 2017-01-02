// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include "jenny5_arduino_controller.h"

bool home_head_motors(t_jenny5_arduino_controller &head_controller, char* error_string);
bool home_left_arm_motors(t_jenny5_arduino_controller &left_arm_controller, char* error_string);