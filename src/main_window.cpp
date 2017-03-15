// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#include <opencv2\imgproc\imgproc.hpp>

#include "main_window.h"
#include "setup_functions.h"

#include "utils.h"
#include "head_controller.h"
#include "lidar_controller.h"
#include "left_arm_controller.h"
#include "platform_controller.h"
#include "leg_controller.h"


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

	p_commands_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 800));
	p_log_panel = new wxPanel(splitter_commands_log, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));

	//--------------------------------------------------------
	build_predefined_task_interface();
	//--------------------------------------------------------
	build_head_interface();
	//----------------------------------------------------------------------
	build_left_arm_interface();
	//----------------------------------------------------------------------
	build_right_arm_interface();
	//----------------------------------------------------------------------
	build_platform_interface();
	//----------------------------------------------------------------------
	build_leg_interface();
	//----------------------------------------------------------------------
	build_lidar_interface();
	//----------------------------------------------------------------------

	//----------------------------------------------------------------------
	wxBoxSizer* sizer_commands = new wxBoxSizer(wxHORIZONTAL);

	sizer_commands->Add(p_predefined_tasks, 0, wxLEFT, 10);
	sizer_commands->Add(p_head, 0, wxLEFT, 10);
	sizer_commands->Add(p_lidar, 0, wxLEFT, 10);
	sizer_commands->Add(p_platform, 0, wxLEFT, 10);
	sizer_commands->Add(p_leg, 0, wxLEFT, 10);
	sizer_commands->Add(p_left_arm, 0, wxLEFT, 10);
	sizer_commands->Add(p_right_arm, 0, wxLEFT, 10);

	p_commands_panel->SetSizer(sizer_commands);


	tc_log = new wxTextCtrl(p_log_panel, -1, "Jenny 5 controller log\n", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	wxBoxSizer* sizer_log = new wxBoxSizer(wxVERTICAL);
	sizer_log->Add(tc_log, 1, wxEXPAND, 0);
	p_log_panel->SetSizer(sizer_log);


	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnMainWindowClose, this);

	Bind(wxEVT_LEFT_UP, &MainFrame::on_platform_2d_mouse_up, this);


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

	jenny5_head_controller.disconnect();
	left_arm_controller.disconnect();
//	right_arm_controller.close_connection();
	LIDAR_controller.disconnect();
	platform_controller.disconnect();
	leg_controller.disconnect();

	Destroy();
}
//------------------------------------------------------------------------
void write_to_log(char* str)
{
	char *s = current_time_to_string();
	*(f_main->tc_log) << wxString(s) + wxString(':') + wxString(str);
}//------------------------------------------------------------------------
void MainFrame::on_connect_to_right_arm_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_timer(wxTimerEvent& event)
{
	handle_head_events();
	handle_left_arm_events();
}
//------------------------------------------------------------------------
