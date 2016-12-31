#pragma once

#include <vector>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

#define C910_4_3_HORIZONTAL_FIELD_OF_VIEW 70.58
#define C910_4_3_VERTICAL_FIELD_OF_VIEW 55.92
#define C910_16_9_HORIZONTAL_FIELD_OF_VIEW 70.58
#define C910_16_9_VERTICAL_FIELD_OF_VIEW 41.94

#define C920_4_3_HORIZONTAL_FIELD_OF_VIEW 65.87
#define C920_4_3_VERTICAL_FIELD_OF_VIEW 51.73
#define C920_16_9_HORIZONTAL_FIELD_OF_VIEW 70.43
#define C920_16_9_VERTICAL_FIELD_OF_VIEW 43.31


struct	tracking_data
{
	double degrees_from_center_x;
	double degrees_from_center_y;

	tracking_data() {
		degrees_from_center_x = degrees_from_center_y = 0;
	}
};


tracking_data get_offset_angles(int webcam_model_number, double image_ratio, int image_width, int image_height, cv::Point position);

tracking_data get_offset_angles(int webcam_model_number, cv::Point position);

double determine_offset_angle(int position, double field_of_view, int number_of_pixels);

//---------------------------------------------------------------------
struct t_CENTER_POINT
{
	int x;
	int y;
	int range;
};
//---------------------------------------------------------------------

bool get_biggest_face(std::vector<cv::Rect> faces, t_CENTER_POINT &center);