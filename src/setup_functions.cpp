// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#include <opencv2\imgproc\imgproc.hpp>

#include "setup_functions.h"

#include "jenny5_events.h"
#include "jenny5_defs.h"


//----------------------------------------------------------------
bool connect_to_platform(t_roboclaw_controller &platform_controller, int platform_com_port, char* error_string)
{
	if (!platform_controller.connect(platform_com_port - 1, 38400)) {
		sprintf(error_string, "Error attaching to Jenny 5' platform!\n");
		return false;
	}
	return true;
}
//----------------------------------------------------------------
bool connect_to_leg(t_roboclaw_controller &leg_controller, int leg_com_port, char* error_string)
{
	if (!leg_controller.connect(leg_com_port - 1, 38400)) {
		sprintf(error_string, "Error attaching to Jenny 5' leg!\n");
		return false;
	}
	return true;
}
//----------------------------------------------------------------
bool init_face_classifier(CascadeClassifier &face_classifier, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	// create cascade for face reco
	  // load haarcascade library
	if (!face_classifier.load("haarcascade_frontalface_alt.xml")) {
		sprintf(error_string, "Cannot load haarcascade! Please place the file in the correct folder!\n");
		return false;
	}

	return true;
}
//----------------------------------------------------------------

bool setup_lidar(t_jenny5_arduino_controller &LIDAR_controller, char* error_string)
{
	LIDAR_controller.send_create_LIDAR(5, 6, 7, 12);// dir, step, enable, IR_pin

	clock_t start_time = clock();

	bool lidar_controller_created = false;

	while (1) {
		if (!LIDAR_controller.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we make a little pause so that we don't kill the processor

		if (!lidar_controller_created)
			if (LIDAR_controller.query_for_event(LIDAR_CONTROLLER_CREATED_EVENT))  // have we received the event from Serial ?
				lidar_controller_created = true;

		if (lidar_controller_created)
			break;

		// measure the passed time 
		clock_t end_time = clock();

		double wait_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		// if more than 3 seconds then game over
		if (wait_time > NUM_SECONDS_TO_WAIT_FOR_CONNECTION) {
			if (!lidar_controller_created)
				sprintf(error_string, "Cannot create LIDAR controller! Game over!\n");
			return false;
		}
	}

	return true;
}
//----------------------------------------------------------------
