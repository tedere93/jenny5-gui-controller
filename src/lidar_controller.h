#pragma once

#include "jenny5_arduino_controller.h"

#define LIDAR_NUM_STEPS 200

struct t_lidar_controller {
	t_jenny5_arduino_controller arduino_controller;
	int lidar_distances[LIDAR_NUM_STEPS];

	t_lidar_controller(void);
	void disconnect(void);
	bool is_connected(void);

	bool connect(int lidar_com_port, char* error_string);
	bool setup(char* error_string);
	bool update_data(void);
};

extern t_lidar_controller LIDAR_controller;