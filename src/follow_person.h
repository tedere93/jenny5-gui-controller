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
#include "head_controller.h"
#include "lidar_controller.h"
#include "platform_controller.h"


int follow_person(t_head_controller &jenny5_head_controller, t_lidar_controller &LIDAR_controller, t_platform_controller & platform_controller, cv::CascadeClassifier &face_classifier, f_log_callback to_log, f_stop_callback stop_function, char* head_window_name, char* LIDAR_window_name);
