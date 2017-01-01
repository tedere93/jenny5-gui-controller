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

	p_com_ports = new wxPanel(this);
	p_predefined_tasks = new wxPanel(this);
	p_free_moves = new wxPanel(this);

	wxBoxSizer* sizer_main = new wxBoxSizer(wxHORIZONTAL);
	sizer_main->Add(p_com_ports);
	sizer_main->Add(p_predefined_tasks, 0, wxLEFT, 10);
	sizer_main->Add(p_free_moves, 0, wxLEFT, 10);

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

	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnMainWindowClose, this);

	SetSizer(sizer_main);

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
void MainFrame::on_head_face_follow_click(wxCommandEvent &event)
{
	int head_com_port = 9; // real port number

	char error_string[1000];
	if (head_face_follow(head_controller, head_com_port, head_cam, face_classifier, error_string) == -1) {
		wxMessageBox(error_string, "Error");
	}
}
//------------------------------------------------------------------------
void MainFrame::on_lidar_map_click(wxCommandEvent &event)
{
	int lidar_com_port = 8; // real port number

	char error_string[1000];
	if (lidar_map(head_controller, lidar_com_port, error_string) == -1) {
		wxMessageBox(error_string, "Error");
	}
}
//------------------------------------------------------------------------