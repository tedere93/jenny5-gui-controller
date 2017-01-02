// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include "jenny5_arduino_controller.h"

struct t_user_data
{
	Mat *lidar_image;
	int image_width;
};

int lidar_map(t_jenny5_arduino_controller &LIDAR_controller, int lidar_com_port, f_log_callback to_log);