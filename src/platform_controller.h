#pragma once


#include "roboclaw_controller.h"

class t_platform_controller {
public:
	t_roboclaw_controller roboclaw_controller;

	t_platform_controller();
	~t_platform_controller();

	bool connect(int PLATFORM_COM_PORT, char* error_string);
	bool is_connected(void);
	void disconnect(void);
	bool setup(char* error_string);

	void send_get_roboclaw_firmware_version(void);

	void move_left_motor(uint32_t speed, uint32_t acceleration);
	void move_right_motor(uint32_t speed, uint32_t acceleration);

	void stop_motors(void);
};

extern t_platform_controller platform_controller;