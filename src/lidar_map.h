// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include "jenny5_arduino_controller.h"
#include "jenny5_defs.h"

struct t_lidar_user_data
{
	Mat *lidar_image;
	int image_width;
	int lidar_distances[LIDAR_NUM_STEPS];
	double lidar_map_scale_factor;
};

void create_and_init_lidar_map(Mat &lidar_image, int image_width, t_lidar_user_data&);
int lidar_map(t_jenny5_arduino_controller &LIDAR_controller, int lidar_com_port, f_log_callback to_log);
void on_lidar_mouse_event(int event, int x, int y, int flags, void *userdata);
bool update_lidar_data(t_jenny5_arduino_controller &LIDAR_controller, Mat &lidar_image, int image_width, t_lidar_user_data&, f_log_callback to_log);