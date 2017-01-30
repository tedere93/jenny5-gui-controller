#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_defs.h"
#include  "utils.h"

#include "head_face_follow.h"
#include "lidar_map.h"
#include "follow_person.h"
#include "head_controller.h"

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

	if (head_face_follow(jenny5_head_controller, head_com_port, face_classifier, write_to_log) == -1) {
	}
}
//------------------------------------------------------------------------
void MainFrame::on_lidar_map_click(wxCommandEvent &event)
{
	long lidar_com_port; // real port number
	tc_lidar_com_port->GetValue().ToLong(&lidar_com_port); // real port number

	if (lidar_map(lidar_controller, lidar_com_port, write_to_log) == -1) {

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

	if (follow_person(jenny5_head_controller, head_com_port, lidar_controller, lidar_com_port, platform_controller, platform_com_port, write_to_log) == -1) {

	}
}
//------------------------------------------------------------------------