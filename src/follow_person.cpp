// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------
#define _USE_MATH_DEFINES

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>


#include "home.h"
#include "setup_functions.h"
#include "utils.h"

#include "jenny5_gui_defs.h"


using namespace cv;
//----------------------------------------------------------------
bool clear_ahead(int *lidar_distances)
{
	for (int i = 40; i < 60; i++)
		if (lidar_distances[i] < 800)
			return false;
	return true;
}
//----------------------------------------------------------------
int follow_person(t_jenny5_arduino_controller &head_controller, int head_com_port, t_jenny5_arduino_controller &lidar_controller, int lidar_com_port, t_roboclaw_controller & tracks_controller, int platform_com_port, VideoCapture &head_cam, CascadeClassifier &face_classifier, f_log_callback to_log)
{
	// initialization

	char error_string[1000];

	if (!connect_to_head(head_controller, head_com_port, error_string)) {
		to_log(error_string);
		return -1;
	}
	else
		to_log("Head connection succceded.\n");

	if (!head_cam.open(HEAD_CAMERA_INDEX)) {	// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
		to_log("Couldn't open head's video camera!\n");
		return -1;
	}
	else
		to_log("Head camera connection succceded.\n");


	if (!connect_to_lidar(lidar_controller, lidar_com_port, error_string)) {
		to_log(error_string);
		return -1;
	}
	else
		to_log("Lidar connection succceded.\n");

	if (!connect_to_platform(tracks_controller, platform_com_port, error_string)) {
		to_log(error_string);
		return -1;
	}
	else
		to_log("Platform connection succceded.\n");

	// initialization
	if (!init_face_classifier(face_classifier, error_string)) {
		to_log(error_string);
		return -1;
	}
	else
		to_log("Face classifier initialization succceded.\n");

	// setup
	if (!setup_head(head_controller, error_string)) {
		to_log(error_string);
		return -1;
	}
	else
		to_log("Head setup succceded.\n");


	//  home
	if (!home_head_motors(head_controller, error_string)) {
		to_log(error_string);
		return -1;
	}
	else
		to_log("Head home succceded.\n");


	int lidar_distances[LIDAR_NUM_STEPS];


	lidar_controller.send_set_LIDAR_motor_speed_and_acceleration(30, 100);
	lidar_controller.send_LIDAR_go();

	namedWindow("LIDAR map", WINDOW_AUTOSIZE);
	// draw the robot
	int w = 600;
	Mat lidar_map_image = Mat::zeros(w, w, CV_8UC3);
	Point center(w / 2, w / 2);
	circle(lidar_map_image, center, 20.0, Scalar(0, 255, 0), 1, 8);
	// finish drawing robot

	Mat cam_frame; // images used in the proces
	Mat gray_frame;

	namedWindow("Head camera", WINDOW_AUTOSIZE); // window to display the results

	double scale_factor = 0.5;

	bool active = true;
	while (active)        // starting infinit loop
	{
		if (!head_controller.update_commands_from_serial() && !lidar_controller.update_commands_from_serial())
			Sleep(DOES_NOTHING_SLEEP); // no new data from serial ... we take a little break so that we don't kill the processor
		else {

			// extract all data from LIDAR 
			int motor_position;
				intptr_t distance;
			bool at_least_one_new_LIDAR_distance = false;
			while (lidar_controller.query_for_event(LIDAR_READ_EVENT, &motor_position, &distance)) {  // have we received the event from Serial ?

																									  // delete old distance
				Point old_p;
				old_p.x = -lidar_distances[motor_position] / scale_factor * sin(motor_position / 100.0 * M_PI - M_PI / 2);
				old_p.y = -lidar_distances[motor_position] / scale_factor * cos(motor_position / 100.0 * M_PI - M_PI / 2);
				circle(lidar_map_image, center + old_p, 5.0, Scalar(0, 0, 0), 1, 8);

				// draw the new point
				lidar_distances[motor_position] = distance;
				Point new_p;
				new_p.x = -distance / scale_factor * sin(motor_position / 100.0 * M_PI - M_PI / 2);
				new_p.y = -distance / scale_factor * cos(motor_position / 100.0 * M_PI - M_PI / 2);
				circle(lidar_map_image, center + new_p, 5.0, Scalar(0, 0, 255), 1, 8);
				//cout << "Motor position = " << motor_position << " LIDAR distance = " << distance << endl;

				at_least_one_new_LIDAR_distance = true;
			}

			if (at_least_one_new_LIDAR_distance)
				imshow("LIDAR map", lidar_map_image);

		}
		head_cam >> cam_frame; // put captured-image frame in frame

		cvtColor(cam_frame, gray_frame, CV_BGR2GRAY); // convert to gray and equalize
		equalizeHist(gray_frame, gray_frame);

		std::vector<Rect> faces;// create an array to store the found faces

								// find and store the faces
		face_classifier.detectMultiScale(gray_frame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		t_CENTER_POINT head_center;

		bool face_found = get_biggest_face(faces, head_center);

		if (face_found) {
			Point p1(head_center.x - head_center.range, head_center.y - head_center.range);
			Point p2(head_center.x + head_center.range, head_center.y + head_center.range);
			// draw an outline for the faces
			rectangle(cam_frame, p1, p2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}
		else {
			Sleep(DOES_NOTHING_SLEEP); // no face found
									   // I have to move the head right-left; top-down
		}

		imshow("Head camera", cam_frame); // display the result

		if (face_found) {

			// send a command to the module so that the face is in the center of the image
			if (head_center.x > cam_frame.cols / 2 + CAM_PIXELS_TOLERANCE) {

				//tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
				//int num_steps_x = (int)(angle_offset.degrees_from_center_x / 1.8 * 8) * TRACKS_MOTOR_REDUCTION;

				// rotate
				tracks_controller.drive_M1_with_signed_duty_and_acceleration(DC_MOTOR_SPEED_ROTATE, 1);
				tracks_controller.drive_M2_with_signed_duty_and_acceleration(-DC_MOTOR_SPEED_ROTATE, 1);
				printf("rotate right - sent\n");
			}
			else
				if (head_center.x < cam_frame.cols / 2 - CAM_PIXELS_TOLERANCE) {

					//					tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
					//					int num_steps_x = (int)(angle_offset.degrees_from_center_x / 1.8 * 8) * TRACKS_MOTOR_REDUCTION;

					// rotate
					tracks_controller.drive_M1_with_signed_duty_and_acceleration(-DC_MOTOR_SPEED_ROTATE, 1);
					tracks_controller.drive_M2_with_signed_duty_and_acceleration(DC_MOTOR_SPEED_ROTATE, 1);
					printf("rotate left - sent\n");
				}
				else {

					// face is in the center, so I move equaly with both motors
					if (head_center.range < HEAD_RADIUS_TO_REVERT) {
						// move forward
						// only if LIDAR distance to the front point is very far from the robot
						if (clear_ahead(lidar_distances)) {
							tracks_controller.drive_M1_with_signed_duty_and_acceleration(-DC_MOTOR_SPEED, 1);
							tracks_controller.drive_M2_with_signed_duty_and_acceleration(-DC_MOTOR_SPEED, 1);

							printf("move ahead - sent\n");
						}
						else {
							// stop the robot -- here I have to move around the obstacle
							tracks_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
							tracks_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
							printf("cannot move ahead - obstacle detected\n");
						}
					}
					else {
						// move backward
						tracks_controller.drive_M1_with_signed_duty_and_acceleration(DC_MOTOR_SPEED, 1);
						tracks_controller.drive_M2_with_signed_duty_and_acceleration(DC_MOTOR_SPEED, 1);
						printf("move backward - sent\n");
					}

				}

				// vertical movement motor
				// send a command to the module so that the face is in the center of the image
				if (head_center.y < cam_frame.rows / 2 - CAM_PIXELS_TOLERANCE) {
					tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
					int num_steps_y = angle_offset.degrees_from_center_y / 1.8 * 27.0;

					head_controller.send_move_stepper_motor(HEAD_MOTOR_FACE, num_steps_y);
					head_controller.set_stepper_motor_state(HEAD_MOTOR_FACE, COMMAND_SENT);
					printf("move head down M%d %d# - sent\n", HEAD_MOTOR_FACE, num_steps_y);
					//	head_controller.set_sonar_state(0, COMMAND_DONE); // if the motor has been moved the previous distances become invalid
				}
				else
					if (head_center.y > cam_frame.rows / 2 + CAM_PIXELS_TOLERANCE) {
						tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
						int num_steps_y = angle_offset.degrees_from_center_y / 1.8 * 27.0;

						head_controller.send_move_stepper_motor(HEAD_MOTOR_FACE, num_steps_y);
						head_controller.set_stepper_motor_state(HEAD_MOTOR_FACE, COMMAND_SENT);
						printf("hove head up M%d -%d# - sent\n", HEAD_MOTOR_FACE, num_steps_y);
						//		head_controller.set_sonar_state(0, COMMAND_DONE); // if the motor has been moved the previous distances become invalid
					}
		}
		else {
			// no face found ... so stop the platoform motors
			tracks_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
			tracks_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);

			printf("no face found - motors stopped\n");
		}

		// now extract the executed moves from the queue ... otherwise they will just sit there and will occupy memory
		if (head_controller.get_stepper_motor_state(HEAD_MOTOR_NECK) == COMMAND_SENT) {// if a command has been sent
			if (head_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_NECK)) { // have we received the event from Serial ?
				head_controller.set_stepper_motor_state(HEAD_MOTOR_NECK, COMMAND_DONE);
				printf("M%d# - done\n", HEAD_MOTOR_NECK);
			}
		}

		// now extract the moves done from the queue
		if (head_controller.get_stepper_motor_state(HEAD_MOTOR_FACE) == COMMAND_SENT) {// if a command has been sent
			if (head_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_FACE)) { // have we received the event from Serial ?
				head_controller.set_stepper_motor_state(HEAD_MOTOR_FACE, COMMAND_DONE);
				printf("M%d# - done\n", HEAD_MOTOR_FACE);
			}
		}

		if (waitKey(1) >= 0)  // break the loop
			active = false;
	}

	// stops all motors
	head_controller.send_move_stepper_motor(HEAD_MOTOR_FACE, 0);
	head_controller.send_move_stepper_motor(HEAD_MOTOR_NECK, 0);

	head_controller.send_disable_stepper_motor(HEAD_MOTOR_FACE);
	head_controller.send_disable_stepper_motor(HEAD_MOTOR_NECK);

	tracks_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	tracks_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);

	lidar_controller.send_LIDAR_stop();

	// close connection
	head_controller.close_connection();
	lidar_controller.close_connection();
	tracks_controller.close_connection();

	return true;
}
//----------------------------------------------------------------