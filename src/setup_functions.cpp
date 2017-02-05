// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#include <opencv2\imgproc\imgproc.hpp>

#include "setup_functions.h"

#include "jenny5_events.h"
#include "jenny5_defs.h"


//----------------------------------------------------------------
bool connect_to_left_arm(t_jenny5_arduino_controller &left_arm_controller, int LEFT_ARM_COM_PORT, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	if (!left_arm_controller.connect(LEFT_ARM_COM_PORT - 1, 115200)) { // real - 1
		sprintf(error_string, "Error attaching to Jenny 5' left arm!\n");
		return false;
	}

	bool left_arm_responded = false;

	// now wait to see if I have been connected
	// wait for no more than 3 seconds. If it takes more it means that something is not right, so we have to abandon it
	clock_t start_time = clock();

	while (1) {
		if (!left_arm_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!left_arm_responded)
			if (left_arm_controller.query_for_event(IS_ALIVE_EVENT, 0)) { // have we received the event from Serial ?
				left_arm_responded = true;
				break;
			}
		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {

			if (!left_arm_responded)
				sprintf(error_string, "Left arm does not respond! Game over!\n");

			return false;
		}
	}

	return true;
}
//----------------------------------------------------------------
bool connect_to_platform(t_roboclaw_controller &platform_controller, int platform_com_port, char* error_string)
{
	if (!platform_controller.connect(platform_com_port - 1, 38400)) {
		sprintf(error_string, "Error attaching to Jenny 5' platform!\n");
		return false;
	}
	return true;
}
//----------------------------------------------------------------
bool connect_to_leg(t_roboclaw_controller &leg_controller, int leg_com_port, char* error_string)
{
	if (!leg_controller.connect(leg_com_port - 1, 38400)) {
		sprintf(error_string, "Error attaching to Jenny 5' leg!\n");
		return false;
	}
	return true;
}
//----------------------------------------------------------------
bool init_face_classifier(CascadeClassifier &face_classifier, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	// create cascade for face reco
	  // load haarcascade library
	if (!face_classifier.load("haarcascade_frontalface_alt.xml")) {
		sprintf(error_string, "Cannot load haarcascade! Please place the file in the correct folder!\n");
		return false;
	}

	return true;
}
//----------------------------------------------------------------

bool setup_left_arm(t_jenny5_arduino_controller &left_arm_controller, char* error_string)
{

	int left_arm_motors_dir_pins[6] = { 12, 10, 8, 6, 4, 2 };
	int left_arm_motors_step_pins[6] = { 13, 11, 9, 7, 5, 3 };
	int left_arm_motors_enable_pins[6] = { 14, 14, 14, 14, 14, 14 };
	left_arm_controller.send_create_stepper_motors(6, left_arm_motors_dir_pins, left_arm_motors_step_pins, left_arm_motors_enable_pins);


	int left_arm_potentiometer_pins[5] = { 2, 3, 4, 5, 6 };
	left_arm_controller.send_create_potentiometers(5, left_arm_potentiometer_pins);

	int gripper_infrared_pins[1] = { 7 };

	left_arm_controller.send_create_infrared_sensors(1, gripper_infrared_pins);

	int gripper_button_pins[1] = { LEFT_ARM_GRIPPER_BUTTON_PIN };

	left_arm_controller.send_create_buttons(1, gripper_button_pins);

	clock_t start_time = clock();

	bool motors_controller_created = false;
	bool potentiometers_controller_created = false;
	bool infrared_controller_created = false;
	bool buttons_controller_created = false;

	while (1) {
		if (!left_arm_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (left_arm_controller.query_for_event(STEPPER_MOTORS_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
			motors_controller_created = true;

		if (left_arm_controller.query_for_event(INFRARED_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
			infrared_controller_created = true;

		if (left_arm_controller.query_for_event(BUTTONS_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
			buttons_controller_created = true;

		if (left_arm_controller.query_for_event(POTENTIOMETERS_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
			potentiometers_controller_created = true;

		if (motors_controller_created && potentiometers_controller_created && infrared_controller_created && buttons_controller_created)
			break;

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!motors_controller_created)
				sprintf(error_string, "Cannot create left arm's motors controller! Game over!\n");
			if (!potentiometers_controller_created)
				sprintf(error_string, "Cannot create left arm's potentiometers controller! Game over!\n");
			if (!infrared_controller_created)
				sprintf(error_string, "Cannot create left arm's infrared controller! Game over!\n");
			if (!buttons_controller_created)
				sprintf(error_string, "Cannot create left arm's buttons controller! Game over!\n");
			return false;
		}
	}

	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_GRIPPER_MOTOR, 500, 500); 
	
	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_BODY_MOTOR, 500, 500);
	
	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, 500, 500);
	
	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, 500, 500);
	
	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_ELBOW_MOTOR, 500, 500);
	
	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_FOREARM_MOTOR, 500, 500);
	
	

//	Sleep(100);
	bool LEFT_ARM_BODY_MOTOR_set_speed_accell = false;
	bool LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_set_speed_accell = false;
	bool LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_set_speed_accell = false;
	bool LEFT_ARM_ELBOW_MOTOR_set_speed_accell = false;
	bool LEFT_ARM_FOREARM_MOTOR_set_speed_accell = false;
	bool LEFT_ARM_GRIPPER_MOTOR_set_speed_accell = false;

	start_time = clock();

	while (1) {
		if (!left_arm_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_BODY_MOTOR))  // have we received the event from Serial ?
			LEFT_ARM_BODY_MOTOR_set_speed_accell = true;

		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_SHOULDER_UP_DOWN_MOTOR))  // have we received the event from Serial ?
			LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_set_speed_accell = true;

		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR))  // have we received the event from Serial ?
			LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_set_speed_accell = true;

		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_ELBOW_MOTOR))  // have we received the event from Serial ?
			LEFT_ARM_ELBOW_MOTOR_set_speed_accell = true;

		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_FOREARM_MOTOR))  // have we received the event from Serial ?
			LEFT_ARM_FOREARM_MOTOR_set_speed_accell = true;
		
		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_GRIPPER_MOTOR))  // have we received the event from Serial ?
		  LEFT_ARM_GRIPPER_MOTOR_set_speed_accell = true;
		

		if (LEFT_ARM_BODY_MOTOR_set_speed_accell && LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_set_speed_accell && LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_set_speed_accell &&
			LEFT_ARM_ELBOW_MOTOR_set_speed_accell && LEFT_ARM_FOREARM_MOTOR_set_speed_accell && LEFT_ARM_GRIPPER_MOTOR_set_speed_accell)
			break;

		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!LEFT_ARM_BODY_MOTOR_set_speed_accell)
				sprintf(error_string, "Cannot LEFT_ARM_BODY_MOTOR_set_speed_accell! Game over!\n");

			if (!LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_set_speed_accell)
				sprintf(error_string, "Cannot LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_set_speed_accell! Game over!\n");

			if (!LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_set_speed_accell)
				sprintf(error_string, "Cannot LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_set_speed_accell! Game over!\n");

			if (!LEFT_ARM_ELBOW_MOTOR_set_speed_accell)
				sprintf(error_string, "Cannot LEFT_ARM_ELBOW_MOTOR_set_speed_accell! Game over!\n");

			if (!LEFT_ARM_FOREARM_MOTOR_set_speed_accell)
				sprintf(error_string, "Cannot LEFT_ARM_FOREARM_MOTOR_set_speed_accell! Game over!\n");
			
			if (!LEFT_ARM_GRIPPER_MOTOR_set_speed_accell)
			sprintf(error_string, "Cannot LEFT_ARM_GRIPPER_MOTOR_set_speed_accell! Game over!\n");
			
			return false;
		}
	}

	int potentiometer_index_LEFT_ARM_BODY_MOTOR[1] = { 0 };
	int potentiometer_index_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR[1] = { 1 };
	int potentiometer_index_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR[1] = { 2 };
	int potentiometer_index_LEFT_ARM_ELBOW_MOTOR[1] = { 3 };
	int potentiometer_index_LEFT_ARM_FOREARM_MOTOR[1] = { 4 };
	int potentiometer_index_LEFT_ARM_GRIPPER_MOTOR[1] = { 5 };

	int potentiometer_min_LEFT_ARM_BODY_MOTOR[1] = { _potentiometer_min_LEFT_ARM_BODY_MOTOR };
	int potentiometer_max_LEFT_ARM_BODY_MOTOR[1] = { _potentiometer_max_LEFT_ARM_BODY_MOTOR };
	int potentiometer_home_LEFT_ARM_BODY_MOTOR[1] = { _potentiometer_home_LEFT_ARM_BODY_MOTOR };
	int potentiometer_dir_LEFT_ARM_BODY_MOTOR[1] = { -1 };

	int potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR[1] = { _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR };
	int potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR[1] = { _potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR };
	int potentiometer_home_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR[1] = { _potentiometer_home_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR };
	int potentiometer_dir_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR[1] = { -1 };

	int potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR[1] = { _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR };
	int potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR[1] = { _potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR };
	int potentiometer_home_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR[1] = { _potentiometer_home_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR };
	int potentiometer_dir_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR[1] = { 1 };

	int potentiometer_min_LEFT_ARM_ELBOW_MOTOR[1] = { _potentiometer_min_LEFT_ARM_ELBOW_MOTOR };
	int potentiometer_max_LEFT_ARM_ELBOW_MOTOR[1] = { _potentiometer_max_LEFT_ARM_ELBOW_MOTOR };
	int potentiometer_home_LEFT_ARM_ELBOW_MOTOR[1] = { 630 };
	int potentiometer_dir_LEFT_ARM_ELBOW_MOTOR[1] = { 1 };

	int potentiometer_min_LEFT_ARM_FOREARM_MOTOR[1] = { _potentiometer_min_LEFT_ARM_FOREARM_MOTOR };
	int potentiometer_max_LEFT_ARM_FOREARM_MOTOR[1] = { _potentiometer_max_LEFT_ARM_FOREARM_MOTOR };
	int potentiometer_home_LEFT_ARM_FOREARM_MOTOR[1] = { _potentiometer_home_LEFT_ARM_FOREARM_MOTOR };
	int potentiometer_dir_LEFT_ARM_FOREARM_MOTOR[1] = { 1 };

	int button_index_LEFT_ARM_GRIPPER_MOTOR[1] = { 0 };
	int button_direction_LEFT_ARM_GRIPPER_MOTOR[1] = { 1 };

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_BODY_MOTOR, 1,
		potentiometer_index_LEFT_ARM_BODY_MOTOR,
		potentiometer_min_LEFT_ARM_BODY_MOTOR,
		potentiometer_max_LEFT_ARM_BODY_MOTOR,
		potentiometer_home_LEFT_ARM_BODY_MOTOR,
		potentiometer_dir_LEFT_ARM_BODY_MOTOR,
		0, NULL, 0, NULL, NULL);

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, 1,
		potentiometer_index_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_home_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_dir_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, 0, NULL, 0, NULL, NULL);

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, 1,
		potentiometer_index_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_home_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_dir_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, 0, NULL, 0, NULL, NULL);

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_ELBOW_MOTOR, 1,
		potentiometer_index_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_min_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_max_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_home_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_dir_LEFT_ARM_ELBOW_MOTOR, 0, NULL, 0, NULL, NULL);

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_FOREARM_MOTOR, 1,
		potentiometer_index_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_min_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_max_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_home_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_dir_LEFT_ARM_FOREARM_MOTOR, 0, NULL, 0, NULL, NULL);

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_GRIPPER_MOTOR, 0,
		NULL, NULL, NULL, NULL, NULL, 0, NULL, 1, button_index_LEFT_ARM_GRIPPER_MOTOR, button_direction_LEFT_ARM_GRIPPER_MOTOR);

	return true;
}
//----------------------------------------------------------------
bool setup_lidar(t_jenny5_arduino_controller &LIDAR_controller, char* error_string)
{
	LIDAR_controller.send_create_LIDAR(5, 6, 7, 12);// dir, step, enable, IR_pin

	clock_t start_time = clock();

	bool lidar_controller_created = false;

	while (1) {
		if (!LIDAR_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!lidar_controller_created)
			if (LIDAR_controller.query_for_event(LIDAR_CONTROLLER_CREATED_EVENT))  // have we received the event from Serial ?
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
