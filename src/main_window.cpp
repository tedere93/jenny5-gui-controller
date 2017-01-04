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




MainFrame *f_main;

//#include <vld.h>

#define TIMER_ID 1300

#define timer_interval 100

//------------------------------------------------------------------------
void MainFrame::build_interface(void)
{
	splitter_commands_log = new wxSplitterWindow(this);
	splitter_commands_log->SetSplitMode(wxSPLIT_HORIZONTAL);
	splitter_commands_log->SetMinimumPaneSize(100);

	p_commands_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 500));
	p_log_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));


	//--------------------------------------------------------
	build_head_interface();
	//----------------------------------------------------------------------
	build_left_arm_interface();
	//----------------------------------------------------------------------
	build_right_arm_interface();
	//----------------------------------------------------------------------
	p_platform = new wxPanel(p_commands_panel);
	p_lidar = new wxPanel(p_commands_panel);
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

	//----------------------------------------------------------------------
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

	//----------------------------------------------------------------------
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
	build_interface();

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
void MainFrame::on_connect_to_lidar_click(wxCommandEvent &event)
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
	handle_head_events();
	handle_left_arm_events();
}
//------------------------------------------------------------------------
