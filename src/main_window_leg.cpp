#include "main_window.h"
#include "setup_functions.h"
#include "jenny5_defs.h"
#include "leg_controller.h"

//------------------------------------------------------------------------
void MainFrame::build_leg_interface(void)
{
	p_leg = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_leg = new wxBoxSizer(wxVERTICAL);
	st_leg = new wxStaticText(p_leg, wxID_ANY, "Leg");
	st_leg_com_port = new wxStaticText(p_leg, wxID_ANY, "COM port");
	tc_leg_com_port = new wxTextCtrl(p_leg, wxID_ANY, "23");
	b_connect_to_leg = new wxButton(p_leg, -1, "Connect");
	b_connect_to_leg->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_leg_click, this);

	st_leg_speed = new wxStaticText(p_leg, wxID_ANY, "Speed");
	s_leg_speed = new wxSlider(p_leg, -1, 0, 0, 32000);
	s_leg_speed->Bind(wxEVT_SLIDER, &MainFrame::on_leg_speed_slider_move, this);
	tc_leg_speed = new wxTextCtrl(p_leg, wxID_ANY, "0");
	tc_leg_speed->SetEditable(false);

	b_expand_leg = new wxButton(p_leg, -1, "Expand leg");
	b_expand_leg->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_leg_expand_mouse_down, this);
	b_expand_leg->Bind(wxEVT_LEFT_UP, &MainFrame::on_leg_expand_mouse_up, this);
	b_expand_leg->Enable(false);

	b_contract_leg = new wxButton(p_leg, -1, "Contract leg");
	b_contract_leg->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_leg_contract_mouse_down, this);
	b_contract_leg->Bind(wxEVT_LEFT_UP, &MainFrame::on_leg_contract_mouse_up, this);
	b_contract_leg->Enable(false);

	b_expand_top_leg_motor = new wxButton(p_leg, -1, "Expand top");
	b_expand_top_leg_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_leg_expand_top_motor_mouse_down, this);
	b_expand_top_leg_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_leg_expand_top_motor_mouse_up, this);
	b_expand_top_leg_motor->Enable(false);

	b_contract_top_leg_motor = new wxButton(p_leg, -1, "Contract top");
	b_contract_top_leg_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_leg_contract_top_motor_mouse_down, this);
	b_contract_top_leg_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_leg_contract_top_motor_mouse_up, this);
	b_contract_top_leg_motor->Enable(false);

	b_expand_bottom_leg_motor = new wxButton(p_leg, -1, "Expand bottom");
	b_expand_bottom_leg_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_leg_expand_bottom_motor_mouse_down, this);
	b_expand_bottom_leg_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_leg_expand_bottom_motor_mouse_up, this);
	b_expand_bottom_leg_motor->Enable(false);

	b_contract_bottom_leg_motor = new wxButton(p_leg, -1, "Contract bottom");
	b_contract_bottom_leg_motor->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_leg_contract_bottom_motor_mouse_down, this);
	b_contract_bottom_leg_motor->Bind(wxEVT_LEFT_UP, &MainFrame::on_leg_contract_bottom_motor_mouse_up, this);
	b_contract_bottom_leg_motor->Enable(false);


	sizer_leg->Add(st_leg, 0, wxTOP, 10);
	sizer_leg->Add(st_leg_com_port, 0, wxTOP, 10);
	sizer_leg->Add(tc_leg_com_port);
	sizer_leg->Add(b_connect_to_leg, 0, wxTOP, 10);

	sizer_leg->Add(st_leg_speed, 0, wxTOP, 10);
	sizer_leg->Add(s_leg_speed);
	sizer_leg->Add(tc_leg_speed);

	sizer_leg->Add(b_expand_leg, 0, wxTOP, 10);
	sizer_leg->Add(b_contract_leg);

	sizer_leg->Add(b_expand_top_leg_motor, 0, wxTOP, 10);
	sizer_leg->Add(b_contract_top_leg_motor);

	sizer_leg->Add(b_expand_bottom_leg_motor, 0, wxTOP, 10);
	sizer_leg->Add(b_contract_bottom_leg_motor);

	p_leg->SetSizer(sizer_leg);

	leg_set_enable_all(false);
}
//------------------------------------------------------------------------
void MainFrame::leg_set_enable_all(bool new_state)
{
	b_expand_leg->Enable(new_state);
	b_contract_leg->Enable(new_state);
	b_expand_top_leg_motor->Enable(new_state);
	b_contract_top_leg_motor->Enable(new_state);
	b_expand_bottom_leg_motor->Enable(new_state);
	b_contract_bottom_leg_motor->Enable(new_state);	
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_leg_click(wxCommandEvent &event)
{

	long leg_com_port;
	tc_leg_com_port->GetValue().ToLong(&leg_com_port); // real port number

	if (!leg_controller.is_connected()) {
		if (leg_controller.connect(leg_com_port) == E_OK) {
			write_to_log(Connected_to_leg_STR);

			b_connect_to_leg->SetLabel("Disconnect");
			leg_set_enable_all(true);
		}
		else {
			write_to_log(CANNOT_CONNECT_TO_JENNY5_LEG_STR);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from leg\n");
		leg_controller.disconnect();
		b_connect_to_leg->SetLabel("Connect");
		leg_set_enable_all(false);
	}
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_expand_mouse_down(wxMouseEvent &event)
{
	long leg_motor_speed;
	tc_leg_speed->GetValue().ToLong(&leg_motor_speed);

	leg_controller.expand_both(leg_motor_speed, 1);
	
	b_expand_leg->SetLabel("Expanding leg");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_expand_mouse_up(wxMouseEvent &event)
{
	leg_controller.stop_motors();
	b_expand_leg->SetLabel("Expand leg");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_contract_mouse_down(wxMouseEvent &event)
{
	long leg_motor_speed;
	tc_leg_speed->GetValue().ToLong(&leg_motor_speed);

	leg_controller.contract_both(leg_motor_speed, 1);
	b_contract_leg->SetLabel("Contracting leg");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_contract_mouse_up(wxMouseEvent &event)
{
	leg_controller.stop_motors();
	b_contract_leg->SetLabel("Contract leg");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_expand_top_motor_mouse_down(wxMouseEvent &event)
{
	long leg_motor_speed;
	tc_leg_speed->GetValue().ToLong(&leg_motor_speed);

	leg_controller.expand_top(leg_motor_speed, 1);
	b_expand_top_leg_motor->SetLabel("Expanding top");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_expand_top_motor_mouse_up(wxMouseEvent &event)
{
	leg_controller.stop_motors();
	b_expand_top_leg_motor->SetLabel("Expand top");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_contract_top_motor_mouse_down(wxMouseEvent &event)
{
	long leg_motor_speed;
	tc_leg_speed->GetValue().ToLong(&leg_motor_speed);

	leg_controller.contract_top(leg_motor_speed, 1);
	b_contract_top_leg_motor->SetLabel("Contracting top");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_contract_top_motor_mouse_up(wxMouseEvent &event)
{
	leg_controller.stop_motors();
	b_contract_top_leg_motor->SetLabel("Contract leg");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_expand_bottom_motor_mouse_down(wxMouseEvent &event)
{
	long leg_motor_speed;
	tc_leg_speed->GetValue().ToLong(&leg_motor_speed);

	leg_controller.expand_bottom(leg_motor_speed, 1);
	b_expand_bottom_leg_motor->SetLabel("Expanding bottom");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_expand_bottom_motor_mouse_up(wxMouseEvent &event)
{
	leg_controller.stop_motors();
	b_expand_bottom_leg_motor->SetLabel("Expand leg");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_contract_bottom_motor_mouse_down(wxMouseEvent &event)
{
	long leg_motor_speed;
	tc_leg_speed->GetValue().ToLong(&leg_motor_speed);

	leg_controller.contract_bottom(leg_motor_speed, 1);
	b_contract_bottom_leg_motor->SetLabel("Contracting bottom");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_contract_bottom_motor_mouse_up(wxMouseEvent &event)
{
	leg_controller.stop_motors();
	b_contract_bottom_leg_motor->SetLabel("Contract bottom");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_leg_speed_slider_move(wxCommandEvent & event)
{
	long leg_speed_new_position = s_leg_speed->GetValue();
	tc_leg_speed->SetValue(wxString() << leg_speed_new_position);
	event.Skip();
}
//------------------------------------------------------------------------