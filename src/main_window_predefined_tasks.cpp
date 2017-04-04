#include "main_window.h"
#include "setup_functions.h"

#include "head_face_follow.h"
#include "lidar_map.h"
#include "follow_person.h"
#include "head_controller.h"
#include "lidar_controller.h"
#include "platform_controller.h"
#include "jenny5_defs.h"

using namespace cv;

//------------------------------------------------------------------------
void MainFrame::build_predefined_task_interface(void)
{
	p_predefined_tasks = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_predefined_tasks = new wxBoxSizer(wxVERTICAL);
	st_predefined_tasks = new wxStaticText(p_predefined_tasks, -1, "Predefined tasks");
	b_head_face_following = new wxButton(p_predefined_tasks, wxID_ANY, "Head follow face");
	b_head_face_following->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_follow_click, this);
	b_lidar_map = new wxButton(p_predefined_tasks, wxID_ANY, "LIDAR map");
	b_lidar_map->Bind(wxEVT_BUTTON, &MainFrame::on_lidar_map_click, this);
	b_follow_person = new wxButton(p_predefined_tasks, wxID_ANY, "Follow person");
	b_follow_person->Bind(wxEVT_BUTTON, &MainFrame::on_follow_person_click, this);


	sizer_predefined_tasks->Add(st_predefined_tasks, 0, wxTOP, 10);
	sizer_predefined_tasks->Add(b_head_face_following, 0, wxTOP, 10);
	sizer_predefined_tasks->Add(b_lidar_map, 0, wxTOP, 10);
	sizer_predefined_tasks->Add(b_follow_person, 0, wxTOP, 10);

	p_predefined_tasks->SetSizer(sizer_predefined_tasks);
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_follow_click(wxCommandEvent &event)
{
	long head_com_port;
	tc_head_com_port->GetValue().ToLong(&head_com_port); // real port number

	CascadeClassifier face_classifier;

	char error_string[1000];

	int error_index = jenny5_head_controller.connect(head_com_port);
	write_to_log(jenny5_head_controller.error_to_string(error_index));

	if (error_index == E_OK) {
		if (!jenny5_head_controller.setup(error_string)) {
			write_to_log(error_string);
		}
	}
	else
		return;

	if (!jenny5_head_controller.head_cam.open(HEAD_CAMERA_INDEX)) {	// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
		write_to_log("Couldn't open head's video camera!\n");
		return;
	}
	else {
		write_to_log("Head camera connection succceded.\n");
	}
	// initialization

	if (!init_face_classifier(face_classifier, error_string)) {
		write_to_log(error_string);
		return;
	}
	else {
		write_to_log("Face classifier initialization succceded.\n");
	}
	//  home
	if (!jenny5_head_controller.home_all_motors(error_string)) {
		write_to_log(error_string);
		return;
	}
	else {
		write_to_log("Head home succceded.\n");
	}

	namedWindow("Head camera");

	head_face_follow(jenny5_head_controller, face_classifier, write_to_log, NULL, "Head camera");

	destroyWindow("Head camera");

	jenny5_head_controller.disconnect();
	//if (head_face_follow(jenny5_head_controller, head_com_port, face_classifier, write_to_log) == -1) {
//	}
}
//------------------------------------------------------------------------
void MainFrame::on_lidar_map_click(wxCommandEvent &event)
{
	long lidar_com_port; // real port number
	tc_lidar_com_port->GetValue().ToLong(&lidar_com_port); // real port number

	if (lidar_map(LIDAR_controller, lidar_com_port, write_to_log) == -1) {

	}
}
//------------------------------------------------------------------------
void MainFrame::on_follow_person_click(wxCommandEvent &event)
{
	long lidar_com_port; // real port number
	tc_lidar_com_port->GetValue().ToLong(&lidar_com_port); // real port number

	long head_com_port;
	tc_head_com_port->GetValue().ToLong(&head_com_port); // real port number

	long platform_com_port;
	tc_platform_com_port->GetValue().ToLong(&platform_com_port); // real port number



	CascadeClassifier face_classifier;

	char error_string[1000];

	int error_index = jenny5_head_controller.connect(head_com_port);
	write_to_log(jenny5_head_controller.error_to_string(error_index));

	if (error_index == E_OK) {
		if (!jenny5_head_controller.setup(error_string)) {
			write_to_log(error_string);
		}
	}
	else
		return;

	if (!jenny5_head_controller.head_cam.open(HEAD_CAMERA_INDEX)) {	// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
		write_to_log("Couldn't open head's video camera!\n");
		return;
	}
	else {
		write_to_log("Head camera connection succceded.\n");
	}
	// initialization

	if (!init_face_classifier(face_classifier, error_string)) {
		write_to_log(error_string);
		return;
	}
	else {
		write_to_log("Face classifier initialization succceded.\n");
	}
	//  home
	if (!jenny5_head_controller.home_all_motors(error_string)) {
		write_to_log(error_string);
		return;
	}
	else {
		write_to_log("Head home succceded.\n");
	}

	error_index = LIDAR_controller.connect(lidar_com_port);
	write_to_log(LIDAR_controller.error_to_string(error_index));
	if (error_index != E_OK) {
		return;
	}

	// setup
	if (!LIDAR_controller.setup(error_string)) {
		write_to_log(error_string);
		return;
	}
	else
		write_to_log("Setup LIDAR OK.\n");

	error_index = platform_controller.connect(platform_com_port);
	if (error_index != E_OK) {
		write_to_log(CANNOT_CONNECT_TO_JENNY5_PLATFORM_STR);
		return;
	}
	else
		write_to_log("Platform connection succceded.\n");


	namedWindow("Head camera", WINDOW_AUTOSIZE); // window to display the head camera results
	namedWindow("LIDAR map", WINDOW_AUTOSIZE); // LIDAR window

	if (follow_person(jenny5_head_controller, LIDAR_controller, platform_controller, face_classifier, write_to_log, NULL, "Head camera", "LIDAR map") == -1) {

	}

	// close connection
	jenny5_head_controller.disconnect();
	LIDAR_controller.disconnect();
	platform_controller.disconnect();

	destroyWindow("LIDAR map");
	destroyWindow("Head camera");
}
//------------------------------------------------------------------------