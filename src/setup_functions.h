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


bool init_face_classifier(CascadeClassifier &face_classifier, char* error_string);

bool connect_to_platform(t_roboclaw_controller &platform_controller, int platform_com_port, char* error_string);
bool connect_to_leg(t_roboclaw_controller &leg_controller, int leg_com_port, char* error_string);
