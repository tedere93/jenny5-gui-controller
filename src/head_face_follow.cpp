#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>


#include "home.h"
#include "setup_functions.h"
#include "utils.h"
#include "jenny5_arduino_controller.h"
#include "jenny5_gui_defs.h"


using namespace cv;

//----------------------------------------------------------------
int head_face_follow(t_jenny5_arduino_controller head_controller, int head_com_port, VideoCapture head_cam, CascadeClassifier face_classifier, char *error_string)
{
	// initialization

	if (!init_head(head_controller, head_cam, head_com_port, error_string)) {
		printf("%s\n", error_string);
		printf("Press Enter to terminate ...");
		getchar();
		return -1;
	}
	else
		printf("Head initialization succceded.\n");

	// initialization
	if (!init_face_classifier(face_classifier, error_string)) {
		printf("%s\n", error_string);
		printf("Press Enter to terminate ...");
		getchar();
		return -1;
	}
	else
		printf("Face classifier initialization succceded.\n");

	// setup
	if (!setup_head(head_controller, error_string)) {
		printf("%s\n", error_string);
		printf("Press Enter to terminate ...");
		getchar();
		return -1;
	}
	else
		printf("Head setup succceded.\n");


	//  home
	if (!home_head_motors(head_controller, error_string)) {
		printf("%s\n", error_string);
		printf("Press Enter to terminate ...");
		getchar();
		return -1;
	}
	else
		printf("Head home succceded.\n");


	Mat cam_frame; // images used in the proces
	Mat gray_frame;

	namedWindow("Head camera", WINDOW_AUTOSIZE); // window to display the results

	bool active = true;
	while (active) {        // starting infinit loop

		if (!head_controller.update_commands_from_serial())
			Sleep(DOES_NOTHING_SLEEP); // no new data from serial ... we make a little pause so that we don't kill the processor

		head_cam >> cam_frame; // put captured-image frame in frame

		cvtColor(cam_frame, gray_frame, CV_BGR2GRAY); // convert to gray and equalize
		equalizeHist(gray_frame, gray_frame);

		std::vector<Rect> faces;// create an array to store the faces found

								// find and store the faces
		face_classifier.detectMultiScale(gray_frame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(50, 50));

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
									   //head_controller.send_move_motor(MOTOR_HEAD_HORIZONTAL, 0);// stops 
									   //head_controller.send_move_motor(MOTOR_HEAD_VERTICAL, 0);
		}

		imshow("Head camera", cam_frame); // display the result

		if (head_controller.get_sonar_state(0) == COMMAND_DONE) {// I ping the sonar only if no ping was sent before
			head_controller.send_get_sonar_distance(0);
			head_controller.set_sonar_state(0, COMMAND_SENT);
			printf("U0# - sent\n");
		}

		if (face_found) {// 
						 // horizontal movement motor

						 // send a command to the module so that the face is in the center of the image
			if (head_center.x < cam_frame.cols / 2 - TOLERANCE) {
				tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
				int num_steps_x = angle_offset.degrees_from_center_x / 1.8 * 27.0;

				head_controller.send_move_stepper_motor(HEAD_MOTOR_HORIZONTAL, num_steps_x);
				head_controller.set_stepper_motor_state(HEAD_MOTOR_HORIZONTAL, COMMAND_SENT);
				printf("M%d %d# - sent\n", HEAD_MOTOR_HORIZONTAL, num_steps_x);

				//	head_controller.set_sonar_state(0, COMMAND_DONE); // if the motor has been moved the previous distances become invalid
			}
			else
				if (head_center.x > cam_frame.cols / 2 + TOLERANCE) {
					tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
					int num_steps_x = angle_offset.degrees_from_center_x / 1.8 * 27.0;

					head_controller.send_move_stepper_motor(HEAD_MOTOR_HORIZONTAL, num_steps_x);
					head_controller.set_stepper_motor_state(HEAD_MOTOR_HORIZONTAL, COMMAND_SENT);
					printf("M%d %d# - sent\n", HEAD_MOTOR_HORIZONTAL, num_steps_x);

					//	head_controller.set_sonar_state(0, COMMAND_DONE); // if the motor has been moved the previous distances become invalid
				}
				else {
					// face is in the center, so I do not move
					Sleep(DOES_NOTHING_SLEEP);
				}

				// vertical movement motor
				// send a command to the module so that the face is in the center of the image
				if (head_center.y < cam_frame.rows / 2 - TOLERANCE) {
					tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
					int num_steps_y = angle_offset.degrees_from_center_y / 1.8 * 27.0;

					head_controller.send_move_stepper_motor(HEAD_MOTOR_VERTICAL, num_steps_y);
					head_controller.set_stepper_motor_state(HEAD_MOTOR_VERTICAL, COMMAND_SENT);
					printf("M%d %d# - sent\n", HEAD_MOTOR_VERTICAL, num_steps_y);
					//	head_controller.set_sonar_state(0, COMMAND_DONE); // if the motor has been moved the previous distances become invalid
				}
				else
					if (head_center.y > cam_frame.rows / 2 + TOLERANCE) {
						tracking_data angle_offset = get_offset_angles(920, Point(head_center.x, head_center.y));
						int num_steps_y = angle_offset.degrees_from_center_y / 1.8 * 27.0;

						head_controller.send_move_stepper_motor(HEAD_MOTOR_VERTICAL, num_steps_y);
						head_controller.set_stepper_motor_state(HEAD_MOTOR_VERTICAL, COMMAND_SENT);
						printf("M%d -%d# - sent\n", HEAD_MOTOR_VERTICAL, num_steps_y);
						//		head_controller.set_sonar_state(0, COMMAND_DONE); // if the motor has been moved the previous distances become invalid
					}

		}

		// now extract the executed moves from the queue ... otherwise they will just stay there
		if (head_controller.get_stepper_motor_state(HEAD_MOTOR_HORIZONTAL) == COMMAND_SENT) {// if a command has been sent
			if (head_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_HORIZONTAL)) { // have we received the event from Serial ?
				head_controller.set_stepper_motor_state(HEAD_MOTOR_VERTICAL, COMMAND_DONE);
				printf("M%d# - done\n", HEAD_MOTOR_VERTICAL);
			}
		}

		// now extract the moves done from the queue
		if (head_controller.get_stepper_motor_state(HEAD_MOTOR_VERTICAL) == COMMAND_SENT) {// if a command has been sent
			if (head_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_VERTICAL)) { // have we received the event from Serial ?
				head_controller.set_stepper_motor_state(HEAD_MOTOR_VERTICAL, COMMAND_DONE);
				printf("M%d# - done\n", HEAD_MOTOR_VERTICAL);
			}
		}

		// read to see if there is any distance received from sonar
		if (head_controller.get_sonar_state(0) == COMMAND_SENT) {// if a command has been sent
			int distance;
			if (head_controller.query_for_event(SONAR_EVENT, 0, &distance)) { // have we received the event from Serial ?
				head_controller.set_sonar_state(0, COMMAND_DONE);
				printf("distance = %d cm\n", distance);
			}
		}

		int key = waitKey(1);
		if (key == VK_ESCAPE)  // break the loop
			active = false;
	}

	head_controller.send_move_stepper_motor(HEAD_MOTOR_HORIZONTAL, 0);
	head_controller.send_move_stepper_motor(HEAD_MOTOR_VERTICAL, 0);

	head_controller.close_connection();

	destroyWindow("Head camera");

	return 0;
}
//----------------------------------------------------------------