// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "utils.h"
#include "head_controller.h"
#include "lidar_controller.h"
#include "platform_controller.h"


int follow_person(t_head_controller &jenny5_head_controller, int head_com_port, t_lidar_controller &lidar_controller, int lidar_com_port, t_platform_controller & tracks_controller, int platform_com_port, f_log_callback to_log);
