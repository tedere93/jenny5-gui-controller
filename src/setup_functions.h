#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "jenny5_arduino_controller.h"

using namespace std;
using namespace cv;

bool init_head(t_jenny5_arduino_controller &head_controller, VideoCapture &head_cam, int HEAD_COM_PORT, char* error_string);
bool init_left_arm(t_jenny5_arduino_controller &left_arm_controller, VideoCapture left_hand_cam, int LEFT_ARM_COM_PORT, char* error_string);
bool init_face_classifier(CascadeClassifier &face_classifier, char* error_string);
bool setup_head(t_jenny5_arduino_controller &head_controller, char* error_string);
bool setup_left_arm(t_jenny5_arduino_controller &left_arm_controller, char* error_string);
