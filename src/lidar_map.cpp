#define _USE_MATH_DEFINES

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>


#include "home.h"
#include "setup_functions.h"
#include "utils.h"
#include "jenny5_arduino_controller.h"
#include "jenny5_gui_defs.h"
#include "lidar_map.h"



using namespace cv;

int lidar_distances[LIDAR_NUM_STEPS];
double lidar_map_scale_factor = 0.1;

//----------------------------------------------------------------
static void on_mouse(int event, int x, int y, int flags, void *userdata)
{
	if (event == EVENT_MOUSEWHEEL) {
		int delta = getMouseWheelDelta(flags);

		t_user_data* user_data = (t_user_data*)userdata;
		Point center(user_data->image_width / 2, user_data->image_width / 2);
		for (int i = 0; i < LIDAR_NUM_STEPS; i++) {
			Point old_p;
			old_p.x = -lidar_distances[i] * lidar_map_scale_factor * sin(i / 100.0 * M_PI - M_PI / 2);
			old_p.y = -lidar_distances[i] * lidar_map_scale_factor * cos(i / 100.0 * M_PI - M_PI / 2);
			circle(*(user_data->lidar_image), center + old_p, 5, Scalar(0, 0, 0), 1, 8);
		}
		char text[100];
		sprintf(text, "scale = %.2lf", lidar_map_scale_factor);
		int font_face = FONT_HERSHEY_SCRIPT_SIMPLEX;
		cv::Point text_position(10, 25);

		cv::putText(*(user_data->lidar_image), text, text_position, font_face, 1, Scalar::all(0), 1, 8);
		// delete the robot
		rectangle(*user_data->lidar_image, Point(center.x - 175 * lidar_map_scale_factor, center.y), Point(center.x + lidar_map_scale_factor * 175, center.y + 600 * lidar_map_scale_factor), Scalar(0, 0, 0));


		if (delta > 0)
			lidar_map_scale_factor += 0.01;
		else
			if (delta < 0)
				lidar_map_scale_factor -= 0.01;

		if (lidar_map_scale_factor < 0.01)
			lidar_map_scale_factor = 0.01;

		for (int i = 0; i < LIDAR_NUM_STEPS; i++) {
			// draw the new point
			Point new_p;
			new_p.x = -lidar_distances[i] * lidar_map_scale_factor * sin(i / 100.0 * M_PI - M_PI / 2);
			new_p.y = -lidar_distances[i] * lidar_map_scale_factor * cos(i / 100.0 * M_PI - M_PI / 2);
			circle(*(user_data->lidar_image), center + new_p, 5, Scalar(0, 0, 255), 1, 8);
		}

		// robot
		rectangle(*user_data->lidar_image, Point(center.x - 175 * lidar_map_scale_factor, center.y), Point(center.x + lidar_map_scale_factor * 175, center.y + 600 * lidar_map_scale_factor), Scalar(0, 255, 0));

		sprintf(text, "scale = %.2lf", lidar_map_scale_factor);
		cv::putText(*user_data->lidar_image, text, text_position, font_face, 1, Scalar::all(255), 1, 8);
	}
}
//----------------------------------------------------------------
int lidar_map(t_jenny5_arduino_controller &LIDAR_controller, int lidar_com_port, char *error_string)
{

	// setup
	if (!connect_to_lidar(LIDAR_controller, lidar_com_port, error_string)) {
		printf("%s\n", error_string);
		printf("Press Enter to terminate...");
		getchar();
		return -1;
	}
	else
		printf("Connection OK.\n");

	// setup
	if (!setup_lidar(LIDAR_controller, error_string)) {
		printf("%s\n", error_string);
		printf("Press Enter to terminate...");
		getchar();
		return -1;
	}
	else
		printf("Setup OK.\n");

	for (int i = 0; i < LIDAR_NUM_STEPS; i++)
		lidar_distances[i] = 0;


	LIDAR_controller.send_set_LIDAR_motor_speed_and_acceleration(60, 100);
	LIDAR_controller.send_LIDAR_go();

	namedWindow("LIDAR map", WINDOW_AUTOSIZE);

	int image_width = 600;
	Mat lidar_image = Mat::zeros(image_width, image_width, CV_8UC3);
	Point center(image_width / 2, image_width / 2);
	//LIDAR
	circle(lidar_image, center, 10, Scalar(0, 255, 0), 1, 8);
	// robot
	rectangle(lidar_image, Point(center.x - 175 * lidar_map_scale_factor, center.y), Point(center.x + lidar_map_scale_factor * 175, center.y + 600 * lidar_map_scale_factor), Scalar(0, 255, 0));

	t_user_data user_data;

	user_data.lidar_image = &lidar_image;
	user_data.image_width = image_width;

	setMouseCallback("LIDAR map", on_mouse, &user_data);

	char text[100];
	sprintf(text, "scale = %.2lf", lidar_map_scale_factor);
	int font_face = FONT_HERSHEY_SCRIPT_SIMPLEX;
	cv::Point text_position(10, 25);
	cv::putText(lidar_image, text, text_position, font_face, 1, Scalar::all(255), 1, 8);

	printf("Now running the main loop. Press Escape when want to exit!\n");
	bool active = true;

	while (active) {        // starting infinit loop

		if (!LIDAR_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		int motor_position, distance;
		while (LIDAR_controller.query_for_event(LIDAR_READ_EVENT, &motor_position, &distance)) {  // have we received the event from Serial ?

																								  // delete old distance
			Point old_p;
			old_p.x = -lidar_distances[motor_position] * lidar_map_scale_factor * sin(motor_position / 100.0 * M_PI - M_PI / 2);
			old_p.y = -lidar_distances[motor_position] * lidar_map_scale_factor * cos(motor_position / 100.0 * M_PI - M_PI / 2);
			circle(lidar_image, center + old_p, 5, Scalar(0, 0, 0), 1, 8);

			// draw the new point
			lidar_distances[motor_position] = distance;
			Point new_p;
			new_p.x = -distance * lidar_map_scale_factor * sin(motor_position / 100.0 * M_PI - M_PI / 2);
			new_p.y = -distance * lidar_map_scale_factor * cos(motor_position / 100.0 * M_PI - M_PI / 2);
			circle(lidar_image, center + new_p, 5, Scalar(0, 0, 255), 1, 8);
			cout << "Motor position = " << motor_position << " LIDAR distance = " << distance << endl;
		}

		imshow("LIDAR map", lidar_image);

		if (waitKey(1) == VK_ESCAPE)  // break the loop
			active = false;
	}

	LIDAR_controller.send_LIDAR_stop();

	LIDAR_controller.close_connection();

	destroyWindow("LIDAR map");

	printf("\n\nProgram over. Press Enter!");

	return 0;
}
//----------------------------------------------------------------