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