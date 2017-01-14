#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

//------------------------------------------------------------------------

void MainFrame::build_lidar_interface(void)
{
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
}