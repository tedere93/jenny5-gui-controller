#include "main_window.h"

#include "jenny5_defs.h"
#include "utils.h"
#include "platform_controller.h"

#define RECTANGULAR_SLIDER_SIZE 120
#define speed_factor 100

bool _mouse_down = false;
//------------------------------------------------------------------------
void MainFrame::build_platform_interface(void)
{
	p_platform = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_platform = new wxBoxSizer(wxVERTICAL);
	st_platform = new wxStaticText(p_platform, wxID_ANY, "Platform");
	st_platform_com_port = new wxStaticText(p_platform, wxID_ANY, "COM port");
	tc_platform_com_port = new wxTextCtrl(p_platform, wxID_ANY, "20");
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
	b_run_platform_motors->Enable(false);


	st_platform_rotate_speed = new wxStaticText(p_platform, wxID_ANY, "Rotate speed");
	s_platform_rotate_speed = new wxSlider(p_platform, -1, 0, -100, 100);
	s_platform_rotate_speed->Bind(wxEVT_SLIDER, &MainFrame::on_platform_rotate_speed_slider_move, this);
	tc_platform_rotate_speed = new wxTextCtrl(p_platform, -1, "0");

	b_rotate_platform = new wxButton(p_platform, -1, "Rotate");
	b_rotate_platform->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_platform_rotate_mouse_down, this);
	b_rotate_platform->Bind(wxEVT_LEFT_UP, &MainFrame::on_platform_rotate_mouse_up, this);
	b_rotate_platform->Enable(false);

	p_platform_2d_slider = new wxPanel(p_platform, -1, wxDefaultPosition, wxSize(RECTANGULAR_SLIDER_SIZE, RECTANGULAR_SLIDER_SIZE));
	p_platform_2d_slider->SetBackgroundColour(wxColour(255, 255, 255));
	
	p_platform_2d_slider->Bind(wxEVT_MOTION, &MainFrame::on_platform_2d_mouse_move, this);
	p_platform_2d_slider->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_platform_2d_mouse_down, this);
	p_platform_2d_slider->Bind(wxEVT_LEFT_UP, &MainFrame::on_platform_2d_mouse_up, this);
	p_platform_2d_slider->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::on_platform_2d_mouse_up, this);
	

	p_platform->Bind(wxEVT_LEFT_UP, &MainFrame::on_platform_2d_mouse_up, this);
	
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

	sizer_platform->Add(st_platform_rotate_speed, 0, wxTOP, 10);
	sizer_platform->Add(s_platform_rotate_speed);
	sizer_platform->Add(tc_platform_rotate_speed);


	sizer_platform->Add(b_rotate_platform, 0, wxTOP, 10);

	sizer_platform->Add(p_platform_2d_slider, 0, wxTOP, 10);

	p_platform->SetSizer(sizer_platform);
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_platform_click(wxCommandEvent &event)
{

	long platform_com_port;
	tc_platform_com_port->GetValue().ToLong(&platform_com_port); // real port number

	if (!platform_controller.is_connected()) {
		if (platform_controller.connect(platform_com_port) == E_OK) {
			write_to_log(Connected_to_platform_STR);
			b_connect_to_platform->SetLabel("Disconnect");
			// show the firmware version number
			double battery_voltage = platform_controller.roboclaw_controller.get_main_battery_voltage();
			tc_platform_battery_voltage->SetValue(wxString() << battery_voltage);

			b_run_platform_motors->Enable(true);
			b_rotate_platform->Enable(true);
			_mouse_down = false;
		}
		else {
			write_to_log(CANNOT_CONNECT_TO_JENNY5_PLATFORM_STR);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from platform\n");
		platform_controller.disconnect();
		b_connect_to_platform->SetLabel("Connect");
		b_run_platform_motors->Enable(false);
		b_rotate_platform->Enable(false);
	}
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_run_motors_mouse_down(wxMouseEvent &event)
{
	long platform_left_motor_speed;
	long platform_right_motor_speed;
	tc_platform_left_motor_speed->GetValue().ToLong(&platform_left_motor_speed);
	tc_platform_right_motor_speed->GetValue().ToLong(&platform_right_motor_speed);

	platform_controller.move_right_motor(platform_right_motor_speed * speed_factor, 1);
	platform_controller.move_left_motor(platform_left_motor_speed * speed_factor, 1);
	b_run_platform_motors->SetLabel("Running");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_run_motors_mouse_up(wxMouseEvent &event)
{
	platform_controller.stop_motors();
	b_run_platform_motors->SetLabel("Run");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_left_motor_slider_move(wxCommandEvent& event)
{
	long platform_left_motor_speed_new_position = s_platform_left_motor_speed->GetValue(); 
	tc_platform_left_motor_speed->SetValue(wxString() << platform_left_motor_speed_new_position);
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_right_motor_slider_move(wxCommandEvent& event)
{
	long platform_right_motor_speed_new_position = s_platform_right_motor_speed->GetValue();
	tc_platform_right_motor_speed->SetValue(wxString() << platform_right_motor_speed_new_position);
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_rotate_speed_slider_move(wxCommandEvent & event)
{
	long platform_rotate_speed_new_position = s_platform_rotate_speed->GetValue();
	tc_platform_rotate_speed->SetValue(wxString() << platform_rotate_speed_new_position);
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_rotate_mouse_down(wxMouseEvent &event)
{
	long platform_rotate_speed;
	tc_platform_rotate_speed->GetValue().ToLong(&platform_rotate_speed);
	
	platform_controller.move_right_motor(platform_rotate_speed * speed_factor, 1);
	platform_controller.move_left_motor(-platform_rotate_speed * speed_factor, 1);
	b_run_platform_motors->SetLabel("Rotating");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_rotate_mouse_up(wxMouseEvent &event)
{
	platform_controller.stop_motors();
	
	b_rotate_platform->SetLabel("Rotate");
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_2d_mouse_move(wxMouseEvent& event)
{
	if (_mouse_down) {
		wxPoint pos = event.GetPosition();

		long platform_left_motor_speed = RECTANGULAR_SLIDER_SIZE - pos.y - RECTANGULAR_SLIDER_SIZE / 2;
		long platform_right_motor_speed = RECTANGULAR_SLIDER_SIZE - pos.y - RECTANGULAR_SLIDER_SIZE / 2;

		if (pos.x > RECTANGULAR_SLIDER_SIZE / 2) {
			platform_left_motor_speed += (pos.x - RECTANGULAR_SLIDER_SIZE / 2) / 2;
		}
		else
			platform_right_motor_speed += -(pos.x - RECTANGULAR_SLIDER_SIZE / 2) / 2;

		tc_platform_left_motor_speed->SetValue(wxString() << platform_left_motor_speed);
		tc_platform_right_motor_speed->SetValue(wxString() << platform_right_motor_speed);

		platform_controller.move_right_motor(platform_right_motor_speed * speed_factor, 1);
		platform_controller.move_left_motor(platform_left_motor_speed * speed_factor, 1);
	}
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_2d_mouse_down(wxMouseEvent& event)
{
	_mouse_down = true;
	event.Skip();
}
//------------------------------------------------------------------------
void MainFrame::on_platform_2d_mouse_up(wxMouseEvent& event)
{
	_mouse_down = false;
	platform_controller.stop_motors();

	long platform_left_motor_speed = 0;
	long platform_right_motor_speed = 0;

	tc_platform_left_motor_speed->SetValue(wxString() << platform_left_motor_speed);
	tc_platform_right_motor_speed->SetValue(wxString() << platform_right_motor_speed);
	event.Skip();
}
//------------------------------------------------------------------------