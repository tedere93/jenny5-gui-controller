#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

//------------------------------------------------------------------------
void MainFrame::build_right_arm_interface(void)
{
	p_right_arm = new wxPanel(p_commands_panel);

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

}
//------------------------------------------------------------------------
