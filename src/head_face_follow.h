#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

int head_face_follow(t_jenny5_arduino_controller head_controller, int head_com_port, VideoCapture head_cam, CascadeClassifier face_classifier, char *error_string);
