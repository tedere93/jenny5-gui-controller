// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

#include "utils.h"

int head_face_follow(t_jenny5_arduino_controller &head_controller, int head_com_port, VideoCapture &head_cam, CascadeClassifier &face_classifier, f_log_callback to_log);
