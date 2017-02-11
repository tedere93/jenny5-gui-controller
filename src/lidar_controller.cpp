#include "lidar_controller.h"
#include "jenny5_defs.h"

t_lidar_controller LIDAR_controller;

//----------------------------------------------------------------
t_lidar_controller::t_lidar_controller(void)
{

}
//----------------------------------------------------------------
bool t_lidar_controller::connect(int lidar_com_port, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	if (!arduino_controller.connect(lidar_com_port - 1, 115200)) { // real number - 1
		sprintf(error_string, "Error attaching to Jenny 5' LIDAR!\n");
		return false;
	}

	// now wait to see if I have been connected
	// wait for no more than 3 seconds. If it takes more it means that something is not right, so we have to abandon it
	clock_t start_time = clock();

	bool LIDAR_responded = false;

	while (1) {
		if (!arduino_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!LIDAR_responded)
			if (arduino_controller.query_for_event(IS_ALIVE_EVENT)) {  // have we received the event from Serial ?
				LIDAR_responded = true;
				break;
			}

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!LIDAR_responded)
				sprintf(error_string, "LIDAR does not respond! Game over!\n");
			return false;
		}
	}

	return true;
}
//----------------------------------------------------------------
bool t_lidar_controller::setup(char* error_string)
{
	arduino_controller.send_create_LIDAR(5, 6, 7, 12);// dir, step, enable, IR_pin

	clock_t start_time = clock();

	bool lidar_controller_created = false;

	while (1) {
		if (!arduino_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!lidar_controller_created)
			if (arduino_controller.query_for_event(LIDAR_CONTROLLER_CREATED_EVENT))  // have we received the event from Serial ?
				lidar_controller_created = true;

		if (lidar_controller_created)
			break;

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!lidar_controller_created)
				sprintf(error_string, "Cannot create LIDAR controller! Game over!\n");
			return false;
		}
	}

	return true;
}
//----------------------------------------------------------------
bool t_lidar_controller::update_data(void)
{
	int motor_position;
	intptr_t distance;

	bool at_least_one_new_LIDAR_distance = false;

	while (arduino_controller.query_for_event(LIDAR_READ_EVENT, &motor_position, &distance)) {  // have we received the event from Serial ?
		lidar_distances[motor_position] = distance;
		at_least_one_new_LIDAR_distance = true;
	}
	return at_least_one_new_LIDAR_distance;
}
//----------------------------------------------------------------
void t_lidar_controller::disconnect(void)
{
	arduino_controller.close_connection();
}
//----------------------------------------------------------------
bool t_lidar_controller::is_connected(void)
{
	return arduino_controller.is_open();
}
//----------------------------------------------------------------
