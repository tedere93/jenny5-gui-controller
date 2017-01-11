// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#include <opencv2\imgproc\imgproc.hpp>

#include "setup_functions.h"

#include "jenny5_events.h"
#include "jenny5_gui_defs.h"


//----------------------------------------------------------------
bool connect_to_head(t_jenny5_arduino_controller &head_controller, VideoCapture &head_cam, int HEAD_COM_PORT, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	if (!head_controller.connect(HEAD_COM_PORT - 1, 115200)) { // real - 1
		sprintf(error_string, "Error attaching to Jenny 5' head!\n");
		return false;
	}


	bool head_responded = false;

	// now wait to see if I have been connected
	// wait for no more than 3 seconds. If it takes more it means that something is not right, so we have to abandon it
	clock_t start_time = clock();

	while (1) {
		if (!head_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!head_responded)
			if (head_controller.query_for_event(IS_ALIVE_EVENT, 0)) { // have we received the event from Serial ?
				head_responded = true;
				break;
			}

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!head_responded)
				sprintf(error_string, "Head does not respond! Game over!\n");

			return false;
		}
	}
	// connect to video camera

	head_cam.open(HEAD_CAMERA_INDEX);	// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
	if (!head_cam.isOpened())	// check if we succeeded
	{
		sprintf(error_string, "Couldn't open head's video camera!\n");
		head_controller.close_connection();
		return false;
	}

	return true;
}
//----------------------------------------------------------------
bool connect_to_left_arm(t_jenny5_arduino_controller &left_arm_controller, VideoCapture &left_hand_cam, int LEFT_ARM_COM_PORT, char* error_string)
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
	// connect to video camera

	left_hand_cam.open(0);			// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
	if (!left_hand_cam.isOpened())	// check if we succeeded
	{
		sprintf(error_string, "Couldn't open left arm's video camera!\n");
		left_arm_controller.close_connection();
		return false;
	}
	/*
	else {
		Mat frame;
		left_hand_cam >> frame;
		printf("left arm video size: %dx%d\n", frame.rows, frame.cols);
	}
	*/
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
bool connect_to_lidar(t_jenny5_arduino_controller &lidar_controller, int lidar_com_port, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	if (!lidar_controller.connect(lidar_com_port - 1, 115200)) { // real number - 1
		sprintf(error_string, "Error attaching to Jenny 5' LIDAR!\n");
		return false;
	}

	// now wait to see if I have been connected
	// wait for no more than 3 seconds. If it takes more it means that something is not right, so we have to abandon it
	clock_t start_time = clock();

	bool LIDAR_responded = false;

	while (1) {
		if (!lidar_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!LIDAR_responded)
			if (lidar_controller.query_for_event(IS_ALIVE_EVENT)) {  // have we received the event from Serial ?
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

bool setup_head(t_jenny5_arduino_controller &head_controller, char* error_string)
{

	int head_motors_dir_pins[2] = { 5, 2 };
	int head_motors_step_pins[2] = { 6, 3 };
	int head_motors_enable_pins[2] = { 7, 4 };
	head_controller.send_create_stepper_motors(2, head_motors_dir_pins, head_motors_step_pins, head_motors_enable_pins);

	int head_sonars_trig_pins[1] = { 10 };
	int head_sonars_echo_pins[1] = { 11 };

	head_controller.send_create_sonars(1, head_sonars_trig_pins, head_sonars_echo_pins);

	int head_potentiometer_pins[2] = { 0, 1 };
	head_controller.send_create_potentiometers(2, head_potentiometer_pins);

	bool motors_controller_created = false;
	bool sonars_controller_created = false;
	bool potentiometers_controller_created = false;

	clock_t start_time = clock();
	while (1) {
		if (!head_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (head_controller.query_for_event(STEPPER_MOTORS_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
			motors_controller_created = true;

		if (head_controller.query_for_event(SONARS_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
		sonars_controller_created = true;

		if (head_controller.query_for_event(POTENTIOMETERS_CONTROLLER_CREATED_EVENT, 0))  // have we received the event from Serial ?
			potentiometers_controller_created = true;

		if (motors_controller_created && sonars_controller_created && potentiometers_controller_created)
			break;

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!motors_controller_created)
				sprintf(error_string, "Cannot create head's motors controller! Game over!\n");
			if (!sonars_controller_created)
				sprintf(error_string, "Cannot create head's sonars controller! Game over!\n");
			if (!potentiometers_controller_created)
				sprintf(error_string, "Cannot create head's potentiometers controller! Game over!\n");
			return false;
		}
	}

	head_controller.send_set_stepper_motor_speed_and_acceleration(HEAD_MOTOR_NECK, 1500, 500);
	head_controller.send_set_stepper_motor_speed_and_acceleration(HEAD_MOTOR_FACE, 1500, 500);

	bool HEAD_MOTOR_HORIZONTAL_set_speed_accell = false;
	bool HEAD_MOTOR_VERTICAL_set_speed_accell = false;

	start_time = clock();

	while (1) {
		if (!head_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (head_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, HEAD_MOTOR_NECK))  // have we received the event from Serial ?
			HEAD_MOTOR_HORIZONTAL_set_speed_accell = true;
		if (head_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, HEAD_MOTOR_FACE))  // have we received the event from Serial ?
			HEAD_MOTOR_VERTICAL_set_speed_accell = true;

		if (HEAD_MOTOR_HORIZONTAL_set_speed_accell && HEAD_MOTOR_VERTICAL_set_speed_accell)
			break;

		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!HEAD_MOTOR_HORIZONTAL_set_speed_accell)
				sprintf(error_string, "Cannot HEAD_MOTOR_HORIZONTAL_set_speed_accell! Game over!\n");
			if (!HEAD_MOTOR_VERTICAL_set_speed_accell)
				sprintf(error_string, "Cannot HEAD_MOTOR_VERTICAL_set_speed_accell! Game over!\n");
			return false;
		}
	}

	int potentiometer_index_head_horizontal_motor[1] = { 0 };
	int potentiometer_index_head_vertical_motor[1] = { 1 };


	int head_horizontal_motor_potentiometer_min[1] = { _head_horizontal_motor_potentiometer_min };
	int head_horizontal_motor_potentiometer_max[1] = { _head_horizontal_motor_potentiometer_max };
	int head_horizontal_motor_potentiometer_home[1] = { _head_horizontal_motor_potentiometer_home };
	int head_horizontal_motor_potentiometer_dir[1] = { -1 };


	int head_vertical_motor_potentiometer_min[1] = { _head_vertical_motor_potentiometer_min };
	int head_vertical_motor_potentiometer_max[1] = { _head_vertical_motor_potentiometer_max };
	int head_vertical_motor_potentiometer_home[1] = { _head_vertical_motor_potentiometer_home };
	int head_vertical_motor_potentiometer_dir[1] = { 1 };

	head_controller.send_attach_sensors_to_stepper_motor(HEAD_MOTOR_NECK, 1, potentiometer_index_head_horizontal_motor, head_horizontal_motor_potentiometer_min, head_horizontal_motor_potentiometer_max, head_horizontal_motor_potentiometer_home, head_horizontal_motor_potentiometer_dir, 0, NULL, 0, NULL);
	head_controller.send_attach_sensors_to_stepper_motor(HEAD_MOTOR_FACE, 1, potentiometer_index_head_vertical_motor, head_vertical_motor_potentiometer_min, head_vertical_motor_potentiometer_max, head_vertical_motor_potentiometer_home, head_vertical_motor_potentiometer_dir, 0, NULL, 0, NULL);

	return true;
}
//----------------------------------------------------------------
bool setup_left_arm(t_jenny5_arduino_controller &left_arm_controller, char* error_string)
{

	int left_arm_motors_dir_pins[6] = { 12, 10, 8, 6, 4, 2 };
	int left_arm_motors_step_pins[6] = { 13, 11, 9, 7, 5, 3 };
	int left_arm_motors_enable_pins[6] = { 14, 14, 14, 14, 14, 14 };
	left_arm_controller.send_create_stepper_motors(5, left_arm_motors_dir_pins, left_arm_motors_step_pins, left_arm_motors_enable_pins);


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

	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_BODY_MOTOR, 500, 500);

	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, 500, 500);


	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, 500, 500);


	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_ELBOW_MOTOR, 500, 500);

	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_FOREARM_MOTOR, 500, 500);
	/*
	Sleep(100);
	left_arm_controller.send_set_stepper_motor_speed_and_acceleration(LEFT_ARM_GRIPPER_MOTOR, 1000, 500);
	Sleep(100);
	*/
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
		/*
		if (left_arm_controller.query_for_event(STEPPER_MOTOR_SET_SPEED_ACCELL_EVENT, LEFT_ARM_GRIPPER_MOTOR))  // have we received the event from Serial ?
		LEFT_ARM_GRIPPER_MOTOR_set_speed_accell = true;
		*/

		if (LEFT_ARM_BODY_MOTOR_set_speed_accell && LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_set_speed_accell && LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_set_speed_accell &&
			LEFT_ARM_ELBOW_MOTOR_set_speed_accell && LEFT_ARM_FOREARM_MOTOR_set_speed_accell)// && LEFT_ARM_GRIPPER_MOTOR_set_speed_accell)
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
			/*
			if (!LEFT_ARM_GRIPPER_MOTOR_set_speed_accell)
			sprintf(error_string, "Cannot LEFT_ARM_GRIPPER_MOTOR_set_speed_accell! Game over!");
			*/
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


	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_BODY_MOTOR, 1,
		potentiometer_index_LEFT_ARM_BODY_MOTOR,
		potentiometer_min_LEFT_ARM_BODY_MOTOR,
		potentiometer_max_LEFT_ARM_BODY_MOTOR,
		potentiometer_home_LEFT_ARM_BODY_MOTOR,
		potentiometer_dir_LEFT_ARM_BODY_MOTOR,
		0, NULL, 0, NULL);


	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, 1,
		potentiometer_index_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_home_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR,
		potentiometer_dir_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, 0, NULL, 0, NULL);


	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, 1,
		potentiometer_index_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_home_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR,
		potentiometer_dir_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, 0, NULL, 0, NULL);


	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_ELBOW_MOTOR, 1,
		potentiometer_index_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_min_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_max_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_home_LEFT_ARM_ELBOW_MOTOR,
		potentiometer_dir_LEFT_ARM_ELBOW_MOTOR, 0, NULL, 0, NULL);

	left_arm_controller.send_attach_sensors_to_stepper_motor(LEFT_ARM_FOREARM_MOTOR, 1,
		potentiometer_index_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_min_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_max_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_home_LEFT_ARM_FOREARM_MOTOR,
		potentiometer_dir_LEFT_ARM_FOREARM_MOTOR, 0, NULL, 0, NULL);
	Sleep(100);

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
