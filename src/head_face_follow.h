// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2\highgui\highgui.hpp"

#include "utils.h"
#include "head_controller.h"

int head_face_follow(t_head_controller *jenny5_head_controller, cv::CascadeClassifier *face_classifier, f_log_callback to_log, f_stop_callback stop_function, char* window_name);