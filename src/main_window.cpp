// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#include <opencv2\imgproc\imgproc.hpp>

#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

#include "head_face_follow.h"
#include "lidar_map.h"


MainFrame *f_main;

//#include <vld.h>

#define TIMER_ID 1300

#define timer_interval 100

//------------------------------------------------------------------------
void MainFrame::BuildInterface(void)
{
	splitter_commands_log = new wxSplitterWindow(this);
	splitter_commands_log->SetSplitMode(wxSPLIT_HORIZONTAL);
	splitter_commands_log->SetMinimumPaneSize(100);

	wxPanel *p_commands_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 500));
	wxPanel *p_log_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));


	p_predefined_tasks = new wxPanel(p_commands_panel);
	p_head = new wxPanel(p_commands_panel);
	p_left_arm = new wxPanel(p_commands_panel);
	p_right_arm = new wxPanel(p_commands_panel);
	p_lidar = new wxPanel(p_commands_panel);
	p_platform = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_predefined_tasks = new wxBoxSizer(wxVERTICAL);
	st_predefined_tasks = new wxStaticText(p_predefined_tasks, -1, "Predefined tasks");
	b_head_face_following = new wxButton(p_predefined_tasks, wxID_ANY, "Head follow face");
	b_head_face_following->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_follow_click, this);
	b_lidar_map = new wxButton(p_predefined_tasks, wxID_ANY, "LIDAR map");
	b_lidar_map->Bind(wxEVT_BUTTON, &MainFrame::on_lidar_map_click, this);
	
	sizer_predefined_tasks->Add(st_predefined_tasks, 0, wxTOP, 10);
	sizer_predefined_tasks->Add(b_head_face_following, 0, wxTOP, 10);
	sizer_predefined_tasks->Add(b_lidar_map, 0, wxTOP, 10);

	p_predefined_tasks->SetSizer(sizer_predefined_tasks);

	wxBoxSizer* sizer_head = new wxBoxSizer(wxVERTICAL);
	st_head = new wxStaticText(p_head, wxID_ANY, "Head");
	st_head_com_port = new wxStaticText(p_head, wxID_ANY, "COM port");
	tc_head_com_port = new wxTextCtrl(p_head, wxID_ANY, "9");
	b_connect_to_head = new wxButton(p_head, -1, "Connect");
	b_connect_to_head->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_head_click, this);

	wxPanel *p_head_neck_position = new wxPanel(p_head);
	st_head_neck_motor_position = new wxStaticText(p_head, wxID_ANY, "Neck motor");
	tc_head_neck_motor_position = new wxTextCtrl(p_head_neck_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_head_neck_home = new wxButton(p_head_neck_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_head_neck_move = new wxButton(p_head_neck_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_neck = new wxBoxSizer(wxHORIZONTAL);
	sizer_neck->Add(tc_head_neck_motor_position);
	sizer_neck->Add(b_head_neck_move);
	sizer_neck->Add(b_head_neck_home);
	p_head_neck_position->SetSizer(sizer_neck);

	s_head_neck_motor_position = new wxSlider(p_head, -1, _head_horizontal_motor_potentiometer_min, _head_horizontal_motor_potentiometer_min, _head_horizontal_motor_potentiometer_max);

	wxPanel *p_head_face_position = new wxPanel(p_head);
	st_head_face_motor_position = new wxStaticText(p_head, wxID_ANY, "Face motor");
	tc_head_face_motor_position = new wxTextCtrl(p_head_face_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	s_head_face_motor_position = new wxSlider(p_head, -1, _head_vertical_motor_potentiometer_min, _head_vertical_motor_potentiometer_min, _head_vertical_motor_potentiometer_max);
	b_head_face_home = new wxButton(p_head_face_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_head_face_move = new wxButton(p_head_face_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_face = new wxBoxSizer(wxHORIZONTAL);
	sizer_face->Add(tc_head_face_motor_position);
	sizer_face->Add(b_head_face_move);
	sizer_face->Add(b_head_face_home);
	p_head_face_position->SetSizer(sizer_face);

	st_head_ultrasonic = new wxStaticText(p_head, wxID_ANY, "Ultrasonic");
	tc_head_ultrasonic = new wxTextCtrl(p_head, wxID_ANY, "0");
	tc_head_ultrasonic->SetEditable(false);
	
	b_head_refresh = new wxButton(p_head, -1, "Refresh");
	b_head_refresh->Bind(wxEVT_BUTTON, &MainFrame::on_head_refresh_data_click, this);

	b_head_home_all = new wxButton(p_head, -1, "Home All");
	b_head_home_all->Bind(wxEVT_BUTTON, &MainFrame::on_head_home_all_click, this);
	

	sizer_head->Add(st_head, 0, wxTOP, 10);
	sizer_head->Add(st_head_com_port, 0, wxTOP, 10);
	sizer_head->Add(tc_head_com_port);
	sizer_head->Add(b_connect_to_head, 0, wxTOP, 10);
	sizer_head->Add(st_head_neck_motor_position, 0, wxTOP, 10);
	sizer_head->Add(p_head_neck_position);
	sizer_head->Add(s_head_neck_motor_position);
	sizer_head->Add(st_head_face_motor_position, 0, wxTOP, 10);
	sizer_head->Add(p_head_face_position);
	sizer_head->Add(s_head_face_motor_position);
	sizer_head->Add(st_head_ultrasonic, 0, wxTOP, 10);
	sizer_head->Add(tc_head_ultrasonic);
	sizer_head->Add(b_head_home_all, 0, wxTOP, 10);
	sizer_head->Add(b_head_refresh, 0, wxTOP, 10);

	p_head->SetSizer(sizer_head);

	wxBoxSizer* sizer_left_arm = new wxBoxSizer(wxVERTICAL);
	st_left_arm = new wxStaticText(p_left_arm, wxID_ANY, "Left arm");
	st_left_arm_com_port = new wxStaticText(p_left_arm, wxID_ANY, "COM port");
	tc_left_arm_com_port = new wxTextCtrl(p_left_arm, wxID_ANY, "1");
	b_connect_to_left_arm = new wxButton(p_left_arm, -1, "Connect");
	b_connect_to_left_arm->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_left_arm_click, this);
	sizer_left_arm->Add(st_left_arm, 0, wxTOP, 10);
	sizer_left_arm->Add(st_left_arm_com_port, 0, wxTOP, 10);
	sizer_left_arm->Add(tc_left_arm_com_port);
	sizer_left_arm->Add(b_connect_to_left_arm, 0, wxTOP, 10);
	p_left_arm->SetSizer(sizer_left_arm);

	wxBoxSizer* sizer_right_arm = new wxBoxSizer(wxVERTICAL);
	st_right_arm = new wxStaticText(p_right_arm, wxID_ANY, "Right arm");
	st_right_arm_com_port = new wxStaticText(p_right_arm, wxID_ANY, "COM port");
	tc_right_arm_com_port = new wxTextCtrl(p_right_arm, wxID_ANY, "2");
	b_connect_to_right_arm = new wxButton(p_right_arm, -1, "Connect");
	b_connect_to_right_arm->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_right_arm_click, this);
	sizer_right_arm->Add(st_right_arm, 0, wxTOP, 10);
	sizer_right_arm->Add(st_right_arm_com_port, 0, wxTOP, 10);
	sizer_right_arm->Add(tc_right_arm_com_port);
	sizer_right_arm->Add(b_connect_to_right_arm, 0, wxTOP, 10);
	p_right_arm->SetSizer(sizer_right_arm);

	wxBoxSizer* sizer_lidar = new wxBoxSizer(wxVERTICAL);
	st_lidar = new wxStaticText(p_lidar, wxID_ANY, "LIDAR");
	st_lidar_com_port = new wxStaticText(p_lidar, wxID_ANY, "COM port");
	tc_lidar_com_port = new wxTextCtrl(p_lidar, wxID_ANY, "8");
	b_connect_to_lidar = new wxButton(p_lidar, -1, "Connect");
	b_connect_to_lidar->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_lidar_click, this);
	sizer_lidar->Add(st_lidar, 0, wxTOP, 10);
	sizer_lidar->Add(st_lidar_com_port, 0, wxTOP, 10);
	sizer_lidar->Add(tc_lidar_com_port);
	sizer_lidar->Add(b_connect_to_lidar, 0, wxTOP, 10);
	p_lidar->SetSizer(sizer_lidar);

	wxBoxSizer* sizer_platform = new wxBoxSizer(wxVERTICAL);
	st_platform = new wxStaticText(p_platform, wxID_ANY, "Platform");
	st_platform_com_port = new wxStaticText(p_platform, wxID_ANY, "COM port");
	tc_platform_com_port = new wxTextCtrl(p_platform, wxID_ANY, "4");
	b_connect_to_platform = new wxButton(p_platform, -1, "Connect");
	b_connect_to_platform->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_platform_click, this);
	sizer_platform->Add(st_platform, 0, wxTOP, 10);
	sizer_platform->Add(st_platform_com_port, 0, wxTOP, 10);
	sizer_platform->Add(tc_platform_com_port);
	sizer_platform->Add(b_connect_to_platform, 0, wxTOP, 10);
	p_platform->SetSizer(sizer_platform);

	wxBoxSizer* sizer_commands = new wxBoxSizer(wxHORIZONTAL);

	sizer_commands->Add(p_predefined_tasks, 0, wxLEFT, 10);
	sizer_commands->Add(p_head, 0, wxLEFT, 10);
	sizer_commands->Add(p_lidar, 0, wxLEFT, 10);
	sizer_commands->Add(p_platform, 0, wxLEFT, 10);
	sizer_commands->Add(p_left_arm, 0, wxLEFT, 10);
	sizer_commands->Add(p_right_arm, 0, wxLEFT, 10);

	p_commands_panel->SetSizer(sizer_commands);


	tc_log = new wxTextCtrl(p_log_panel, -1, "Jenny 5 controller log\n", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	wxBoxSizer* sizer_log = new wxBoxSizer(wxVERTICAL);
	sizer_log->Add(tc_log, 1, wxEXPAND, 0);
	p_log_panel->SetSizer(sizer_log);


	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnMainWindowClose, this);

	splitter_commands_log->SplitHorizontally(p_commands_panel, p_log_panel);

	wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
	main_sizer->Add(splitter_commands_log, 1, wxEXPAND, 0);

	SetAutoLayout(true);
	SetSizer(main_sizer);
}
//------------------------------------------------------------------------
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	BuildInterface();

	t_timer = new wxTimer;
	t_timer->SetOwner(this, TIMER_ID);
	Bind(wxEVT_TIMER, &MainFrame::on_timer, this);
	t_timer->Start(timer_interval);
}
//------------------------------------------------------------------------
void MainFrame::OnMainWindowClose(wxCloseEvent& WXUNUSED(event))
{
	t_timer->Stop();
	delete t_timer;

	head_controller.close_connection();
	left_arm_controller.close_connection();
	right_arm_controller.close_connection();
	lidar_controller.close_connection();
	platform_controller.close_connection();

	Destroy();
}
//------------------------------------------------------------------------
void write_to_log(char* str)
{
	char *s = current_time_to_string();
	*(f_main->tc_log) << wxString(s) + wxString(':') + wxString(str);
}//------------------------------------------------------------------------
void MainFrame::on_head_face_follow_click(wxCommandEvent &event)
{
	long head_com_port;
	tc_head_com_port->GetValue().ToLong(&head_com_port); // real port number

	if (head_face_follow(head_controller, head_com_port, head_cam, face_classifier, write_to_log) == -1) {
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
void  MainFrame::on_connect_to_head_click(wxCommandEvent &event)
{
	char error_string[1000];
	long head_com_port;
	tc_head_com_port->GetValue().ToLong(&head_com_port); // real port number

	if (!head_controller.is_open()) {
		if (connect_to_head(head_controller, head_cam, head_com_port, error_string)) {
			b_connect_to_head->SetLabel("Disconnect");
			// show the firmware version number
			head_controller.send_get_firmware_version();

			if (!setup_head(head_controller, error_string)) {
				write_to_log(error_string);
			}
			else {
				head_controller.send_get_potentiometer_position(0);
				head_controller.send_get_potentiometer_position(1);
				head_controller.send_get_sonar_distance(0);
			}
		}
		else {
			write_to_log(error_string);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from head");
		head_controller.close_connection();
		b_connect_to_head->SetLabel("Connect");
	}
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_lidar_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_left_arm_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_right_arm_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_platform_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_timer(wxTimerEvent& event)
{
	if (head_controller.is_open()) {
		head_controller.update_commands_from_serial();

		char firmware_version[100];
		strcpy(firmware_version, "Head firmware version: ");

		if (head_controller.query_for_firmware_version_event(firmware_version + strlen(firmware_version))) {
			strcat(firmware_version, "\n");
			write_to_log(firmware_version);
		}

		int pot_position;
		char buffer[100];
		if (head_controller.query_for_event(POTENTIOMETER_EVENT, HEAD_POTENTIOMETER_HORIZONTAL_INDEX, &pot_position)) {
			sprintf(buffer, "Head pot position (%d) = %d\n", HEAD_POTENTIOMETER_HORIZONTAL_INDEX, pot_position);
			write_to_log(buffer);
			tc_head_neck_motor_position->SetValue(wxString() << pot_position);
			s_head_neck_motor_position->SetValue(pot_position);
		}
		if (head_controller.query_for_event(POTENTIOMETER_EVENT, HEAD_POTENTIOMETER_VERTICAL_INDEX, &pot_position)) {
			sprintf(buffer, "Head pot position (%d) = %d\n", HEAD_POTENTIOMETER_VERTICAL_INDEX, pot_position);
			write_to_log(buffer);
			tc_head_face_motor_position->SetValue(wxString() << pot_position);
			s_head_face_motor_position->SetValue(pot_position);
		}

		int ultrasonic_distance;
		if (head_controller.query_for_event(SONAR_EVENT, 0, &ultrasonic_distance)) {
			sprintf(buffer, "Head ultrasonic distance = %d\n", ultrasonic_distance);
			write_to_log(buffer);
			tc_head_ultrasonic->SetValue(wxString() << ultrasonic_distance);
		}
		

	}
}
//------------------------------------------------------------------------
void MainFrame::on_head_refresh_data_click(wxCommandEvent &event)
{
	head_controller.send_get_potentiometer_position(0);
	head_controller.send_get_potentiometer_position(1);
	head_controller.send_get_sonar_distance(0);
}
//------------------------------------------------------------------------
void MainFrame::on_head_home_all_click(wxCommandEvent &event)
{
	head_controller.send_go_home_dc_motor(0);
	head_controller.send_go_home_dc_motor(1);
}
//------------------------------------------------------------------------
void MainFrame::on_head_neck_home_click(wxCommandEvent &event)
{
	head_controller.send_go_home_dc_motor(0);
}
//------------------------------------------------------------------------
void MainFrame::on_head_neck_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_head_face_home_click(wxCommandEvent &event)
{
	head_controller.send_go_home_dc_motor(1);
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------