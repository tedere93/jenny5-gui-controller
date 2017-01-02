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

	wxPanel *p_commands_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 300));
	wxPanel *p_log_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 500));

	splitter_commands_log->SplitHorizontally(p_commands_panel, p_log_panel);

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
	st_left_arm_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Left arm COM port");
	tc_left_arm_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "1");
	st_right_arm_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Right COM port");
	tc_right_arm_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "2");
	st_lidar_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Lidar COM port");
	tc_lidar_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "3");
	st_platform_com_port = new wxStaticText(p_com_ports, wxID_ANY, "Platform COM port");
	tc_platform_com_port = new wxTextCtrl(p_com_ports, wxID_ANY, "4");

	sizer_com_ports->Add(st_head_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_head_com_port);
	sizer_com_ports->Add(st_left_arm_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_left_arm_com_port);
	sizer_com_ports->Add(st_right_arm_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_right_arm_com_port);
	sizer_com_ports->Add(st_lidar_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_lidar_com_port);
	sizer_com_ports->Add(st_platform_com_port, 0, wxTOP, 10);
	sizer_com_ports->Add(tc_platform_com_port);

	p_com_ports->SetSizer(sizer_com_ports);

	tc_log = new wxTextCtrl(p_log_panel, -1, "Jenny 5 controller log\n", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	wxBoxSizer* sizer_log = new wxBoxSizer(wxVERTICAL);
	sizer_log->Add(tc_log, 1, wxEXPAND, 0);
	p_log_panel->SetSizer(sizer_log);


	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnMainWindowClose, this);

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
	*(f_main->tc_log) << wxString(str);
}//------------------------------------------------------------------------
void MainFrame::on_head_face_follow_click(wxCommandEvent &event)
{
	int head_com_port = 9; // real port number

//	char error_string[1000];
	if (head_face_follow(head_controller, head_com_port, head_cam, face_classifier, write_to_log) == -1) {
	}
}
//------------------------------------------------------------------------
void MainFrame::on_lidar_map_click(wxCommandEvent &event)
{
	int lidar_com_port = 8; // real port number

	char error_string[1000];
	if (lidar_map(lidar_controller, lidar_com_port, error_string) == -1) {
		wxMessageBox(error_string, "Error");
	}
}

//------------------------------------------------------------------------