#pragma once
#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "jenny5_arduino_controller.h"

#define LEFT_ARM_BODY_MOTOR 0
#define LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 1
#define LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 2
#define LEFT_ARM_ELBOW_MOTOR 3
#define LEFT_ARM_FOREARM_MOTOR 4
#define LEFT_ARM_GRIPPER_MOTOR 5

#define LEFT_ARM_BODY_POTENTIOMETER_INDEX 0
#define LEFT_ARM_SHOULDER_UP_DOWN_POTENTIOMETER_INDEX 1
#define LEFT_ARM_SHOULDER_LEFT_RIGHT_POTENTIOMETER_INDEX 2
#define LEFT_ARM_ELBOW_POTENTIOMETER_INDEX 3
#define LEFT_ARM_FOREARM_POTENTIOMETER_INDEX 4
#define LEFT_ARM_GRIPPER_BUTTON_INDEX 0
#define LEFT_ARM_GRIPPER_INFRARED_INDEX 0

#define LEFT_ARM_GRIPPER_BUTTON_PIN 15

// left arm
#define _potentiometer_min_LEFT_ARM_BODY_MOTOR 380
#define _potentiometer_max_LEFT_ARM_BODY_MOTOR 800
#define _potentiometer_home_LEFT_ARM_BODY_MOTOR 640

#define _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 170
#define _potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 600
#define _potentiometer_home_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 500

#define _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 230
#define _potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 750
#define _potentiometer_home_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 740

#define _potentiometer_min_LEFT_ARM_ELBOW_MOTOR 480
#define _potentiometer_max_LEFT_ARM_ELBOW_MOTOR 830
#define _potentiometer_home_LEFT_ARM_ELBOW_MOTOR 630

#define _potentiometer_min_LEFT_ARM_FOREARM_MOTOR 230
#define _potentiometer_max_LEFT_ARM_FOREARM_MOTOR 720
#define _potentiometer_home_LEFT_ARM_FOREARM_MOTOR 440

#define LEFT_ARM_CAMERA_INDEX 1

class t_left_arm_controller {
public:
	cv::VideoCapture left_arm_cam;
	t_jenny5_arduino_controller arduino_controller;
	cv::CascadeClassifier face_classifier;
	t_left_arm_controller(void);

	bool connect(int LEF_ARM_COM_PORT, char* error_string);
	bool is_connected(void);
	void disconnect(void);
	bool setup(char* error_string);

	void send_get_arduino_firmware_version(void);

	void send_get_sensors_value(void);

#define LEFT_ARM_BODY_MOTOR 0
#define LEFT_ARM_SHOULDER_UP_DOWN_MOTOR 1
#define LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR 2
#define LEFT_ARM_ELBOW_MOTOR 3
#define LEFT_ARM_FOREARM_MOTOR 4
#define LEFT_ARM_GRIPPER_MOTOR 5

	void send_LEFT_ARM_BODY_MOTOR_home(void);
	void send_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_home(void);
	void send_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_home(void);
	void send_LEFT_ARM_ELBOW_MOTOR_home(void);
	void send_LEFT_ARM_FOREARM_MOTOR_home(void);
	void send_LEFT_ARM_GRIPPER_MOTOR_home(void);

	void send_LEFT_ARM_BODY_MOTOR_to_sensor_position(int new_position);
	void send_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_to_sensor_position(int new_position);
	void send_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_to_sensor_position(int new_position);
	void send_LEFT_ARM_ELBOW_MOTOR_to_sensor_position(int new_position);
	void send_LEFT_ARM_FOREARM_MOTOR_to_sensor_position(int new_position);
	void send_LEFT_ARM_GRIPPER_MOTOR_start_open(void);
	void send_LEFT_ARM_GRIPPER_MOTOR_stop_open(void);
	

	bool home_all_motors(char* error_string);
	void send_disable_motors(void);
};

extern t_left_arm_controller left_arm_controller;