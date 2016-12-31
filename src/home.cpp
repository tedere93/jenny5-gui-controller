
#include "home.h"
#include "jenny5_gui_defs.h"


//----------------------------------------------------------------
bool home_head_motors(t_jenny5_arduino_controller &head_controller, char* error_string)
{
	// must home the head
	head_controller.send_go_home_stepper_motor(HEAD_MOTOR_HORIZONTAL);
	head_controller.send_go_home_stepper_motor(HEAD_MOTOR_VERTICAL);

	printf("Head motors home started ...");
	clock_t start_time = clock();
	bool horizontal_motor_homed = false;
	bool vertical_motor_homed = false;

	while (1) {
		if (!head_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!horizontal_motor_homed)
			if (head_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_HORIZONTAL))  // have we received the event from Serial ?
				horizontal_motor_homed = true;

		if (!vertical_motor_homed)
			if (head_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_VERTICAL))  // have we received the event from Serial ?
				vertical_motor_homed = true;

		if (horizontal_motor_homed && vertical_motor_homed)
			break;

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 5 seconds and no home
		if (wait_time > 5) {
			if (!vertical_motor_homed)
				sprintf(error_string, "Cannot home vertical motor! Game over!");
			if (!horizontal_motor_homed)
				sprintf(error_string, "Cannot home horizontal motor! Game over!");
			return false;
		}
	}

	printf("DONE\n");
	return true;
}
//----------------------------------------------------------------
bool home_left_arm_motors(t_jenny5_arduino_controller &left_arm_controller, char* error_string)
{
	// must home the head

	left_arm_controller.send_go_home_stepper_motor(LEFT_ARM_BODY_MOTOR);


	left_arm_controller.send_go_home_stepper_motor(LEFT_ARM_SHOULDER_UP_DOWN_MOTOR);


	left_arm_controller.send_go_home_stepper_motor(LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR);


	left_arm_controller.send_go_home_stepper_motor(LEFT_ARM_ELBOW_MOTOR);

	left_arm_controller.send_go_home_stepper_motor(LEFT_ARM_FOREARM_MOTOR);

	//left_arm_controller.send_go_home_stepper_motor(LEFT_ARM_GRIPPER_MOTOR);

	printf("Left arm motors home started ...");
	clock_t start_time = clock();
	bool motor_homed_LEFT_ARM_BODY_MOTOR = false;
	bool motor_homed_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR = false;
	bool motor_homed_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR = false;
	bool motor_homed_LEFT_ARM_ELBOW_MOTOR = false;
	bool motor_homed_LEFT_ARM_FOREARM_MOTOR = false;
	//	bool motor_homed_LEFT_ARM_GRIPPER_MOTOR = false;

	while (1) {
		if (!left_arm_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!motor_homed_LEFT_ARM_BODY_MOTOR)
			if (left_arm_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, LEFT_ARM_BODY_MOTOR))  // have we received the event from Serial ?
				motor_homed_LEFT_ARM_BODY_MOTOR = true;

		if (!motor_homed_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR)
			if (left_arm_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, LEFT_ARM_SHOULDER_UP_DOWN_MOTOR))  // have we received the event from Serial ?
				motor_homed_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR = true;

		if (!motor_homed_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR)
			if (left_arm_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR))  // have we received the event from Serial ?
				motor_homed_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR = true;

		if (!motor_homed_LEFT_ARM_ELBOW_MOTOR)
			if (left_arm_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, LEFT_ARM_ELBOW_MOTOR))  // have we received the event from Serial ?
				motor_homed_LEFT_ARM_ELBOW_MOTOR = true;

		if (!motor_homed_LEFT_ARM_FOREARM_MOTOR)
			if (left_arm_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, LEFT_ARM_FOREARM_MOTOR))  // have we received the event from Serial ?
				motor_homed_LEFT_ARM_FOREARM_MOTOR = true;

		//	if (!motor_homed_LEFT_ARM_GRIPPER_MOTOR)
		//	if (left_arm_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, LEFT_ARM_GRIPPER_MOTOR))  // have we received the event from Serial ?
		//	motor_homed_LEFT_ARM_GRIPPER_MOTOR = true;

		if (motor_homed_LEFT_ARM_BODY_MOTOR && motor_homed_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR && motor_homed_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR &&
			motor_homed_LEFT_ARM_ELBOW_MOTOR && motor_homed_LEFT_ARM_FOREARM_MOTOR)// && motor_homed_LEFT_ARM_GRIPPER_MOTOR)
			break;

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 5 seconds and no home
		if (wait_time > 5) {
			if (!motor_homed_LEFT_ARM_BODY_MOTOR)
				sprintf(error_string, "Cannot home motor_homed_LEFT_ARM_BODY_MOTOR! Game over!");

			if (!motor_homed_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR)
				sprintf(error_string, "Cannot home motor_homed_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR! Game over!");

			if (!motor_homed_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR)
				sprintf(error_string, "Cannot home motor_homed_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR! Game over!");

			if (!motor_homed_LEFT_ARM_ELBOW_MOTOR)
				sprintf(error_string, "Cannot home motor_homed_LEFT_ARM_ELBOW_MOTOR! Game over!");

			if (!motor_homed_LEFT_ARM_FOREARM_MOTOR)
				sprintf(error_string, "Cannot home motor_homed_LEFT_ARM_FOREARM_MOTOR! Game over!");

			//if (!motor_homed_LEFT_ARM_GRIPPER_MOTOR)
			//sprintf(error_string, "Cannot home motor_homed_LEFT_ARM_GRIPPER_MOTOR! Game over!");
			return false;
		}
	}

	printf("DONE\n");
	return true;
}
//----------------------------------------------------------------
