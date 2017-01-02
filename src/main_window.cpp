#include <opencv2\imgproc\imgproc.hpp>

#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

#include "head_face_follow.h"
#include "lidar_map.h"

MainFrame *f_main;

#include <vld.h>

//------------------------------------------------------------------------
void MainFrame::BuildInterface(void)
{
	splitter_commands_log = new wxSplitterWindow(this);
	splitter_commands_log->SetSplitMode(wxSPLIT_HORIZONTAL);
	splitter_commands_log->SetMinimumPaneSize(100);

	wxPanel *p_commands_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 500));
	wxPanel *p_log_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));


	p_com_ports = new wxPanel(p_commands_panel);
	p_predefined_tasks = new wxPanel(p_commands_panel);
	p_free_moves = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_commands = new wxBoxSizer(wxHORIZONTAL);
	sizer_commands->Add(p_com_ports);
	sizer_commands->Add(p_predefined_tasks, 0, wxLEFT, 10);
	sizer_commands->Add(p_free_moves, 0, wxLEFT, 10);

	p_commands_panel->SetSizer(sizer_commands);

	wxBoxSizer* sizer_predefined_tasks = new wxBoxSizer(wxVERTICAL);

	b_head_face_following = new wxButton(p_predefined_tasks, wxID_ANY, "Head follow face");
	b_head_face_following->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_follow_click, this);

	b_lidar_map = new wxButton(p_predefined_tasks, wxID_ANY, "LIDAR map");
	b_lidar_map->Bind(wxEVT_BUTTON, &MainFrame::on_lidar_map_click, this);
	
	sizer_predefined_tasks->Add(b_head_face_following);
	sizer_predefined_tasks->Add(b_lidar_map);

	p_predefined_tasks->SetSizer(sizer_predefined_tasks);

	wxBoxSizer* sizer_com_ports = new wxBoxSizer(wxVERTICAL);

	st_head_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Head COM port");
	tc_head_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "9");
	b_connect_to_head = new wxButton(p_com_ports, -1, "Connect to head");
	b_connect_to_head->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_head_click, this);

	st_left_arm_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Left arm COM port");
	tc_left_arm_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "1");
	b_connect_to_left_arm = new wxButton(p_com_ports, -1, "Connect to left");
	b_connect_to_left_arm->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_left_arm_click, this);

	st_right_arm_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Right COM port");
	tc_right_arm_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "2");
	b_connect_to_right_arm = new wxButton(p_com_ports, -1, "Connect to right");
	b_connect_to_right_arm->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_right_arm_click, this);

	st_lidar_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Lidar COM port");
	tc_lidar_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "8");
	b_connect_to_lidar = new wxButton(p_com_ports, -1, "Connect to lidar");
	b_connect_to_lidar->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_lidar_click, this);

	st_platform_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Platform COM port");
	tc_platform_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "4");
	b_connect_to_platform = new wxButton(p_com_ports, -1, "Connect to platform");
	b_connect_to_platform->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_platform_click, this);

	sizer_com_ports->Add(st_head_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_head_com_port);
	sizer_com_ports->Add(b_connect_to_head);

	sizer_com_ports->Add(st_left_arm_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_left_arm_com_port);
	sizer_com_ports->Add(b_connect_to_left_arm);
	
	sizer_com_ports->Add(st_right_arm_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_right_arm_com_port);
	sizer_com_ports->Add(b_connect_to_right_arm);
	
	sizer_com_ports->Add(st_lidar_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_lidar_com_port);
	sizer_com_ports->Add(b_connect_to_lidar);
	
	sizer_com_ports->Add(st_platform_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_platform_com_port);
	sizer_com_ports->Add(b_connect_to_platform);

	p_com_ports->SetSizer(sizer_com_ports);

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
}
//------------------------------------------------------------------------
void MainFrame::OnMainWindowClose(wxCloseEvent& WXUNUSED(event))
{


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

//	char error_string[1000];
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

	if (connect_to_head(head_controller, head_cam, head_com_port, error_string)) {
		b_connect_to_head->SetLabel("Disconnect head");
		// show the firmware version number
		head_controller.send_get_firmware_version();
		Sleep(100);
		char firmware_version[100];
		strcpy(firmware_version, "Head firmware version: ");
		head_controller.update_commands_from_serial();
		if (head_controller.query_for_firmware_version_event(firmware_version + strlen(firmware_version))) {
			strcat(firmware_version, "\n");
			write_to_log(firmware_version);
		}
	}
	else {
		head_controller.close_connection();
		b_connect_to_head->SetLabel("Connect head");
	}
}
//------------------------------------------------------------------------
void  MainFrame::on_connect_to_lidar_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void  MainFrame::on_connect_to_left_arm_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void  MainFrame::on_connect_to_right_arm_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void  MainFrame::on_connect_to_platform_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------