#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "jenny5_arduino_controller.h"

#define HEAD_MOTOR_NECK 0
#define HEAD_MOTOR_FACE 1

#define HEAD_POTENTIOMETER_NECK_INDEX 0
#define HEAD_POTENTIOMETER_FACE_INDEX 1
#define HEAD_ULTRASONIC_FACE_INDEX 0

#define HEAD_CAMERA_INDEX 0


// head
#define _head_horizontal_motor_potentiometer_min 329
#define _head_horizontal_motor_potentiometer_max 829
#define _head_horizontal_motor_potentiometer_home 529

#define _head_vertical_motor_potentiometer_min 332
#define _head_vertical_motor_potentiometer_max 832
#define _head_vertical_motor_potentiometer_home 632

#define HEAD_RADIUS_TO_REVERT 70
#define CAM_PIXELS_TOLERANCE 100

class t_head_controller {
public:
	cv::VideoCapture head_cam;
	t_jenny5_arduino_controller head_arduino_controller;
	cv::CascadeClassifier face_classifier;
	t_head_controller();

	bool connect(int HEAD_COM_PORT, char* error_string);
	bool is_connected(void);
	void disconnect(void);
	bool setup(char* error_string);

	void send_get_arduino_firmware_version(void);

	void send_get_sensors_value(void);
	void send_home_all(void);
	void send_neck_home(void);
	void send_face_home(void);

	void send_neck_to_sensor_position(int head_neck_new_position);
	void send_face_to_sensor_position(int head_face_new_position);
	bool home_all_motors(char* error_string);
	void send_disable_motors(void);
};

extern t_head_controller jenny5_head_controller;