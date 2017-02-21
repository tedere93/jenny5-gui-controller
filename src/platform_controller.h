#pragma once


#define CANNOT_CONNECT_TO_JENNY5_PLATFORM_STR "CANNOT_CONNECT_TO_JENNY5_PLATFORM\n" 
#define CANNOT_CONNECT_TO_JENNY5_PLATFORM 1

#define Connected_to_platform_STR "Connected to platform\n"

#include "roboclaw_controller.h"

class t_platform_controller {
public:
	t_roboclaw_controller roboclaw_controller;

	t_platform_controller();
	~t_platform_controller();

	int connect(int PLATFORM_COM_PORT);
	bool is_connected(void);
	void disconnect(void);
	bool setup(char* error_string);

	void send_get_roboclaw_firmware_version(void);

	// positive if move forward
	void move_left_motor(int16_t speed, uint32_t acceleration);
	// positive if move forward
	void move_right_motor(int16_t speed, uint32_t acceleration);

	void rotate_left(uint16_t speed, uint32_t acceleration);
	void rotate_right(uint16_t speed, uint32_t acceleration);

	void stop_motors(void);
};

extern t_platform_controller platform_controller;