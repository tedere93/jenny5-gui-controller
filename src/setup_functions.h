// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#include "opencv2\objdetect\objdetect.hpp"

bool init_face_classifier(cv::CascadeClassifier &face_classifier, char* error_string);
