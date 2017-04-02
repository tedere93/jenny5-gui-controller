// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

//#include <opencv2\imgproc\imgproc.hpp>

#include "setup_functions.h"

//----------------------------------------------------------------
bool init_face_classifier(cv::CascadeClassifier &face_classifier, char* error_string)
{
	//-------------- START INITIALIZATION ------------------------------

	// create cascade for face reco
	  // load haarcascade library
	if (face_classifier.empty())
		if (!face_classifier.load("haarcascade_frontalface_alt.xml")) {
			sprintf(error_string, "Cannot load haarcascade! Please place the file in the correct folder!\n");
			return false;
		}

	return true;
}
//----------------------------------------------------------------