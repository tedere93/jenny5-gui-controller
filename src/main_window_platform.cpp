#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

//------------------------------------------------------------------------
void MainFrame::build_platform_interface(void)
{
	p_platform = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_platform = new wxBoxSizer(wxVERTICAL);
	st_platform = new wxStaticText(p_platform, wxID_ANY, "Platform");
	st_platform_com_port = new wxStaticText(p_platform, wxID_ANY, "COM port");
	tc_platform_com_port = new wxTextCtrl(p_platform, wxID_ANY, "11");
	b_connect_to_platform = new wxButton(p_platform, -1, "Connect");
	b_connect_to_platform->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_platform_click, this);

	st_platform_battery_voltage = new wxStaticText(p_platform, wxID_ANY, "Battery voltage");
	tc_platform_battery_voltage = new wxTextCtrl(p_platform, wxID_ANY, "0");
	tc_platform_battery_voltage->SetEditable(false);

	st_platform_left_motor_speed = new wxStaticText(p_platform, wxID_ANY, "Left motor speed");;
	s_platform_left_motor_speed = new wxSlider(p_platform, -1, 0, -100, 100);
	s_platform_left_motor_speed->Bind(wxEVT_SLIDER, &MainFrame::on_platform_left_motor_slider_move, this);
	tc_platform_left_motor_speed = new wxTextCtrl(p_platform, -1, "0");
	tc_platform_left_motor_speed->SetEditable(false);

	st_platform_right_motor_speed = new wxStaticText(p_platform, wxID_ANY, "Right motor speed");
	s_platform_right_motor_speed = new wxSlider(p_platform, -1, 0, -100, 100);
	s_platform_right_motor_speed->Bind(wxEVT_SLIDER, &MainFrame::on_platform_right_motor_slider_move, this);
	tc_platform_right_motor_speed = new wxTextCtrl(p_platform, -1, "0");
	tc_platform_right_motor_speed->SetEditable(false);
	
	b_run_platform_motors = new wxButton(p_platform, -1, "Run");
	b_run_platform_motors->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_platform_run_motors_mouse_down, this);
	b_run_platform_motors->Bind(wxEVT_LEFT_UP, &MainFrame::on_platform_run_motors_mouse_up, this);

	sizer_platform->Add(st_platform, 0, wxTOP, 10);
	sizer_platform->Add(st_platform_com_port, 0, wxTOP, 10);
	sizer_platform->Add(tc_platform_com_port);
	sizer_platform->Add(b_connect_to_platform, 0, wxTOP, 10);

	sizer_platform->Add(st_platform_battery_voltage, 0, wxTOP, 10);
	sizer_platform->Add(tc_platform_battery_voltage);

	
	sizer_platform->Add(st_platform_left_motor_speed, 0, wxTOP, 10);
	sizer_platform->Add(s_platform_left_motor_speed);
	sizer_platform->Add(tc_platform_left_motor_speed);
	
	sizer_platform->Add(st_platform_right_motor_speed, 0, wxTOP, 10);
	sizer_platform->Add(s_platform_right_motor_speed);
	sizer_platform->Add(tc_platform_right_motor_speed);


	sizer_platform->Add(b_run_platform_motors, 0, wxTOP, 10);

	p_platform->SetSizer(sizer_platform);
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_platform_click(wxCommandEvent &event)
{
	char error_string[1000];
	long platform_com_port;
	tc_platform_com_port->GetValue().ToLong(&platform_com_port); // real port number

	if (!platform_controller.is_open()) {
		if (connect_to_platform(platform_controller, platform_com_port, error_string)) {
			b_connect_to_platform->SetLabel("Disconnect");
			// show the firmware version number
			double battery_voltage = platform_controller.get_main_battery_voltage();
			tc_platform_battery_voltage->SetValue(wxString() << battery_voltage);
		}
		else {
			write_to_log(error_string);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from platform\n");
		platform_controller.close_connection();
		b_connect_to_platform->SetLabel("Connect");
	}
}
//------------------------------------------------------------------------
void MainFrame::on_platform_run_motors_mouse_down(wxMouseEvent &event)
{
	long platform_left_motor_speed;
	long platform_right_motor_speed;
	tc_platform_left_motor_speed->GetValue().ToLong(&platform_left_motor_speed);
	tc_platform_right_motor_speed->GetValue().ToLong(&platform_right_motor_speed);

	platform_controller.drive_M1_with_signed_duty_and_acceleration(platform_left_motor_speed, 1);
	platform_controller.drive_M2_with_signed_duty_and_acceleration(-platform_right_motor_speed, 1);
}
//------------------------------------------------------------------------
void MainFrame::on_platform_run_motors_mouse_up(wxMouseEvent &event)
{
	platform_controller.drive_M1_with_signed_duty_and_acceleration(0, 1);
	platform_controller.drive_M2_with_signed_duty_and_acceleration(0, 1);
}
//------------------------------------------------------------------------
void MainFrame::on_platform_left_motor_slider_move(wxCommandEvent& event)
{
	long platform_left_motor_speed_new_position = s_platform_left_motor_speed->GetValue(); 
	tc_platform_left_motor_speed->SetValue(wxString() << platform_left_motor_speed_new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_platform_right_motor_slider_move(wxCommandEvent& event)
{
	long platform_right_motor_speed_new_position = s_platform_right_motor_speed->GetValue();
	tc_platform_right_motor_speed->SetValue(wxString() << platform_right_motor_speed_new_position);
}
//------------------------------------------------------------------------