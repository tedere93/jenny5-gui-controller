// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "jenny5_arduino_controller.h"
#include "roboclaw_controller.h"

using namespace std;
using namespace cv;

bool connect_to_head(t_jenny5_arduino_controller &head_controller, VideoCapture &head_cam, int HEAD_COM_PORT, char* error_string);
bool connect_to_left_arm(t_jenny5_arduino_controller &left_arm_controller, VideoCapture &left_hand_cam, int LEFT_ARM_COM_PORT, char* error_string);
bool init_face_classifier(CascadeClassifier &face_classifier, char* error_string);
bool connect_to_lidar(t_jenny5_arduino_controller &lidar_controller, int lidar_com_port, char* error_string);
bool connect_to_platform(t_roboclaw_controller &platform_controller, int platform_com_port, char* error_string);

bool setup_head(t_jenny5_arduino_controller &head_controller, char* error_string);
bool setup_left_arm(t_jenny5_arduino_controller &left_arm_controller, char* error_string);
bool setup_lidar(t_jenny5_arduino_controller &lidar_controller, char* error_string);
