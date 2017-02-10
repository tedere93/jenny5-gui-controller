#include "platform_controller.h"

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
bool t_platform_controller::connect(int PLATFORM_COM_PORT, char* error_string)
{
	if (!roboclaw_controller.connect(PLATFORM_COM_PORT - 1, 38400)) {
		sprintf(error_string, "Error attaching to Jenny 5' platform!\n");
		return false;
	}
	return true;
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
void t_platform_controller::move_left_motor(uint32_t speed, uint32_t acceleration)
{
	roboclaw_controller.drive_M1_with_signed_duty_and_acceleration(speed, acceleration);
}
//------------------------------------------------------------------------
void t_platform_controller::move_right_motor(uint32_t speed, uint32_t acceleration)
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