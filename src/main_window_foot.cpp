#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

//------------------------------------------------------------------------
void MainFrame::build_foot_interface(void)
{
	p_foot = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_foot = new wxBoxSizer(wxVERTICAL);
	st_foot = new wxStaticText(p_foot, wxID_ANY, "Foot");
	st_foot_com_port = new wxStaticText(p_foot, wxID_ANY, "COM port");
	tc_foot_com_port = new wxTextCtrl(p_foot, wxID_ANY, "11");
	b_connect_to_foot = new wxButton(p_foot, -1, "Connect");
	b_connect_to_foot->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_foot_click, this);

	b_expand_foot = new wxButton(p_foot, -1, "Expand foot");
	b_expand_foot->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_foot_expand_mouse_down, this);
	b_expand_foot->Bind(wxEVT_LEFT_UP, &MainFrame::on_foot_expand_mouse_up, this);
	b_expand_foot->Enable(false);

	b_contract_foot = new wxButton(p_foot, -1, "Contract foot");
	b_contract_foot->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_foot_contract_mouse_down, this);
	b_contract_foot->Bind(wxEVT_LEFT_UP, &MainFrame::on_foot_contract_mouse_up, this);
	b_contract_foot->Enable(false);

	b_expand_top_foot_motor = new wxButton(p_foot, -1, "Expand top");
	b_expand_top_foot_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_foot_expand_top_motor_mouse_down, this);
	b_expand_top_foot_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_foot_expand_top_motor_mouse_up, this);
	b_expand_top_foot_motor->Enable(false);

	b_contract_top_foot_motor = new wxButton(p_foot, -1, "Contract top");
	b_contract_top_foot_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_foot_contract_bottom_motor_mouse_down, this);
	b_contract_top_foot_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_foot_contract_bottom_motor_mouse_up, this);
	b_contract_top_foot_motor->Enable(false);

	b_expand_bottom_foot_motor = new wxButton(p_foot, -1, "Expand bottom");
	b_expand_bottom_foot_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_foot_expand_bottom_motor_mouse_down, this);
	b_expand_bottom_foot_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_foot_expand_bottom_motor_mouse_up, this);
	b_expand_bottom_foot_motor->Enable(false);

	b_contract_bottom_foot_motor = new wxButton(p_foot, -1, "Contract bottom");
	b_contract_bottom_foot_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_foot_contract_bottom_motor_mouse_down, this);
	b_contract_bottom_foot_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_foot_contract_bottom_motor_mouse_up, this);
	b_contract_bottom_foot_motor->Enable(false);


	sizer_foot->Add(st_foot, 0, wxTOP, 10);
	sizer_foot->Add(st_foot_com_port, 0, wxTOP, 10);
	sizer_foot->Add(tc_foot_com_port);
	sizer_foot->Add(b_connect_to_foot, 0, wxTOP, 10);

	sizer_foot->Add(b_expand_foot, 0, wxTOP, 10);
	sizer_foot->Add(b_contract_foot);

	sizer_foot->Add(b_expand_top_foot_motor, 0, wxTOP, 10);
	sizer_foot->Add(b_contract_top_foot_motor);

	sizer_foot->Add(b_expand_bottom_foot_motor, 0, wxTOP, 10);
	sizer_foot->Add(b_contract_bottom_foot_motor);

	p_foot->SetSizer(sizer_foot);

	foot_set_enable_all(false);
}
//------------------------------------------------------------------------
void MainFrame::foot_set_enable_all(bool new_state)
{
	b_expand_foot->Enable(new_state);
	b_contract_foot->Enable(new_state);
		b_expand_top_foot_motor->Enable(new_state);
		b_contract_top_foot_motor->Enable(new_state);
		b_expand_bottom_foot_motor->Enable(new_state);
		b_contract_bottom_foot_motor->Enable(new_state);
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_foot_click(wxCommandEvent &event)
{
	char error_string[1000];
	long foot_com_port;
	tc_foot_com_port->GetValue().ToLong(&foot_com_port); // real port number

	if (!foot_controller.is_open()) {
		if (connect_to_foot(foot_controller, foot_com_port, error_string)) {
			b_connect_to_foot->SetLabel("Disconnect");
			foot_set_enable_all(true);
		}
		else {
			write_to_log(error_string);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from foot\n");
		foot_controller.close_connection();
		b_connect_to_foot->SetLabel("Connect");
		foot_set_enable_all(false);
	}
}
//------------------------------------------------------------------------
void MainFrame::on_foot_expand_mouse_down(wxMouseEvent &event)
{
	int foot_motor_speed = 10000;

	foot_controller.drive_M1_with_signed_duty_and_acceleration(foot_motor_speed, 1);
	foot_controller.drive_M2_with_signed_duty_and_acceleration(foot_motor_speed * 100, 1);
	b_expand_foot->SetLabel("Running");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_expand_mouse_up(wxMouseEvent &event)
{
	foot_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	foot_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
	b_expand_foot->SetLabel("Expand foot");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_contract_mouse_down(wxMouseEvent &event)
{
	int foot_motor_speed = -10000;

	foot_controller.drive_M1_with_signed_duty_and_acceleration(foot_motor_speed, 1);
	foot_controller.drive_M2_with_signed_duty_and_acceleration(foot_motor_speed * 100, 1);
	b_expand_foot->SetLabel("Running");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_contract_mouse_up(wxMouseEvent &event)
{
	foot_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	foot_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
	b_expand_foot->SetLabel("Contract foot");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_expand_top_motor_mouse_down(wxMouseEvent &event)
{
	int foot_motor_speed = 10000;

	foot_controller.drive_M2_with_signed_duty_and_acceleration(foot_motor_speed, 1);
	b_expand_foot->SetLabel("Running");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_expand_top_motor_mouse_up(wxMouseEvent &event)
{
	foot_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
	b_expand_foot->SetLabel("Expand foot");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_contract_top_motor_mouse_down(wxMouseEvent &event)
{
	int foot_motor_speed = -10000;

	foot_controller.drive_M2_with_signed_duty_and_acceleration(foot_motor_speed * 100, 1);
	b_expand_foot->SetLabel("Running");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_contract_top_motor_mouse_up(wxMouseEvent &event)
{
	foot_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
	b_expand_foot->SetLabel("Contract foot");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_expand_bottom_motor_mouse_down(wxMouseEvent &event)
{
	int foot_motor_speed = 10000;

	foot_controller.drive_M1_with_signed_duty_and_acceleration(foot_motor_speed, 1);
	b_expand_foot->SetLabel("Running");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_expand_bottom_motor_mouse_up(wxMouseEvent &event)
{
	foot_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	b_expand_foot->SetLabel("Expand foot");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_contract_bottom_motor_mouse_down(wxMouseEvent &event)
{
	int foot_motor_speed = -10000;

	foot_controller.drive_M1_with_signed_duty_and_acceleration(foot_motor_speed * 100, 1);
	b_expand_foot->SetLabel("Running");
}
//------------------------------------------------------------------------
void MainFrame::on_foot_contract_bottom_motor_mouse_up(wxMouseEvent &event)
{
	foot_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	b_expand_foot->SetLabel("Contract foot");
}
//------------------------------------------------------------------------