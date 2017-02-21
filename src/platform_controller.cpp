#include "platform_controller.h"
#include "jenny5_defs.h"

t_platform_controller platform_controller;

//------------------------------------------------------------------------
t_platform_controller::t_platform_controller()
{

}
//------------------------------------------------------------------------
t_platform_controller::~t_platform_controller()
{
	stop_motors();
	roboclaw_controller.close_connection();
}
//------------------------------------------------------------------------
int t_platform_controller::connect(int PLATFORM_COM_PORT)
{
	if (!roboclaw_controller.connect(PLATFORM_COM_PORT - 1, 38400)) {
		return CANNOT_CONNECT_TO_JENNY5_PLATFORM;
	}
	return E_OK;
}
//------------------------------------------------------------------------
bool t_platform_controller::is_connected(void)
{
	return roboclaw_controller.is_open();
}
//------------------------------------------------------------------------
void t_platform_controller::disconnect(void)
{
	roboclaw_controller.close_connection();
}
//------------------------------------------------------------------------
bool t_platform_controller::setup(char* error_string)
{
	return true;
}
//------------------------------------------------------------------------
void t_platform_controller::send_get_roboclaw_firmware_version(void)
{

}
//------------------------------------------------------------------------
void t_platform_controller::move_left_motor(int16_t speed, uint32_t acceleration)
{
	roboclaw_controller.drive_M1_with_signed_duty_and_acceleration(-speed, acceleration);
}
//------------------------------------------------------------------------
void t_platform_controller::move_right_motor(int16_t speed, uint32_t acceleration)
{
	roboclaw_controller.drive_M2_with_signed_duty_and_acceleration(speed, acceleration);
}
//------------------------------------------------------------------------
void t_platform_controller::stop_motors(void)
{
	roboclaw_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	roboclaw_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
}
//------------------------------------------------------------------------
void t_platform_controller::rotate_left(uint16_t speed, uint32_t acceleration)
{
	move_right_motor(speed, 1);
	move_left_motor(-speed, 1);
}
//------------------------------------------------------------------------
void t_platform_controller::rotate_right(uint16_t speed, uint32_t acceleration)
{
	move_right_motor(-speed, 1);
	move_left_motor(speed, 1);
}
//------------------------------------------------------------------------