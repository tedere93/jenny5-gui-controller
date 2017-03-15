#include "main_window.h"
#include "setup_functions.h"
#include "jenny5_defs.h"
#include "left_arm_controller.h"

//------------------------------------------------------------------------
void MainFrame::build_left_arm_interface(void)
{
	p_left_arm = new wxPanel(p_commands_panel);
	wxBoxSizer* sizer_left_arm = new wxBoxSizer(wxVERTICAL);
	st_left_arm = new wxStaticText(p_left_arm, wxID_ANY, "Left arm");
	st_left_arm_com_port = new wxStaticText(p_left_arm, wxID_ANY, "COM port");
	tc_left_arm_com_port = new wxTextCtrl(p_left_arm, wxID_ANY, "5");
	b_connect_to_left_arm = new wxButton(p_left_arm, -1, "Connect");
	b_connect_to_left_arm->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_left_arm_click, this);
//-------
	wxPanel *p_left_arm_body_position = new wxPanel(p_left_arm);
	st_left_arm_body_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Body motor");
	tc_left_arm_body_motor_position = new wxTextCtrl(p_left_arm_body_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_body_home = new wxButton(p_left_arm_body_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_body_home->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_body_home_click, this);
	b_left_arm_body_move = new wxButton(p_left_arm_body_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_body_move->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_body_move_click, this);

	wxBoxSizer *sizer_left_arm_body = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_body->Add(tc_left_arm_body_motor_position);
	sizer_left_arm_body->Add(b_left_arm_body_move);
	sizer_left_arm_body->Add(b_left_arm_body_home);
	p_left_arm_body_position->SetSizer(sizer_left_arm_body);

	s_left_arm_body_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_BODY_MOTOR, _potentiometer_min_LEFT_ARM_BODY_MOTOR, _potentiometer_max_LEFT_ARM_BODY_MOTOR);
	s_left_arm_body_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_left_arm_body_slider_move, this);

	//-------
	wxPanel *p_left_arm_SHOULDER_UP_DOWN_position = new wxPanel(p_left_arm);
	st_left_arm_SHOULDER_UP_DOWN_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Shoulder up down motor");
	tc_left_arm_SHOULDER_UP_DOWN_motor_position = new wxTextCtrl(p_left_arm_SHOULDER_UP_DOWN_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_UP_DOWN_home = new wxButton(p_left_arm_SHOULDER_UP_DOWN_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_UP_DOWN_home->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_SHOULDER_UP_DOWN_home_click, this);
	b_left_arm_SHOULDER_UP_DOWN_move = new wxButton(p_left_arm_SHOULDER_UP_DOWN_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_UP_DOWN_move->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_SHOULDER_UP_DOWN_move_click, this);

	wxBoxSizer *sizer_left_arm_SHOULDER_UP_DOWN = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_SHOULDER_UP_DOWN->Add(tc_left_arm_SHOULDER_UP_DOWN_motor_position);
	sizer_left_arm_SHOULDER_UP_DOWN->Add(b_left_arm_SHOULDER_UP_DOWN_move);
	sizer_left_arm_SHOULDER_UP_DOWN->Add(b_left_arm_SHOULDER_UP_DOWN_home);
	p_left_arm_SHOULDER_UP_DOWN_position->SetSizer(sizer_left_arm_SHOULDER_UP_DOWN);

	s_left_arm_SHOULDER_UP_DOWN_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, _potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR);
	s_left_arm_SHOULDER_UP_DOWN_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_left_arm_SHOULDER_UP_DOWN_slider_move, this);
	//-------
	wxPanel *p_left_arm_SHOULDER_LEFT_RIGHT_position = new wxPanel(p_left_arm);
	st_left_arm_SHOULDER_LEFT_RIGHT_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Shoulder left right motor");
	tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position = new wxTextCtrl(p_left_arm_SHOULDER_LEFT_RIGHT_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_LEFT_RIGHT_home = new wxButton(p_left_arm_SHOULDER_LEFT_RIGHT_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_LEFT_RIGHT_home->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_home_click, this);
	b_left_arm_SHOULDER_LEFT_RIGHT_move = new wxButton(p_left_arm_SHOULDER_LEFT_RIGHT_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_LEFT_RIGHT_move->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_move_click, this);

	wxBoxSizer *sizer_left_arm_SHOULDER_LEFT_RIGHT = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_SHOULDER_LEFT_RIGHT->Add(tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position);
	sizer_left_arm_SHOULDER_LEFT_RIGHT->Add(b_left_arm_SHOULDER_LEFT_RIGHT_move);
	sizer_left_arm_SHOULDER_LEFT_RIGHT->Add(b_left_arm_SHOULDER_LEFT_RIGHT_home);
	p_left_arm_SHOULDER_LEFT_RIGHT_position->SetSizer(sizer_left_arm_SHOULDER_LEFT_RIGHT);

	s_left_arm_SHOULDER_LEFT_RIGHT_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, _potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR);
	s_left_arm_SHOULDER_LEFT_RIGHT_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_slider_move, this);
	//-------
	wxPanel *p_left_arm_ELBOW_position = new wxPanel(p_left_arm);
	st_left_arm_ELBOW_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Elbow motor");
	tc_left_arm_ELBOW_motor_position = new wxTextCtrl(p_left_arm_ELBOW_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_ELBOW_home = new wxButton(p_left_arm_ELBOW_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_ELBOW_home->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_ELBOW_home_click, this);
	b_left_arm_ELBOW_move = new wxButton(p_left_arm_ELBOW_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_ELBOW_move->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_ELBOW_move_click, this);

	wxBoxSizer *sizer_left_arm_ELBOW = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_ELBOW->Add(tc_left_arm_ELBOW_motor_position);
	sizer_left_arm_ELBOW->Add(b_left_arm_ELBOW_move);
	sizer_left_arm_ELBOW->Add(b_left_arm_ELBOW_home);
	p_left_arm_ELBOW_position->SetSizer(sizer_left_arm_ELBOW);

	s_left_arm_ELBOW_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_ELBOW_MOTOR, _potentiometer_min_LEFT_ARM_ELBOW_MOTOR, _potentiometer_max_LEFT_ARM_ELBOW_MOTOR);
	s_left_arm_ELBOW_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_left_arm_ELBOW_slider_move, this);
	//-------
	wxPanel *p_left_arm_FOREARM_position = new wxPanel(p_left_arm);
	st_left_arm_FOREARM_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Forearm motor");
	tc_left_arm_FOREARM_motor_position = new wxTextCtrl(p_left_arm_FOREARM_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_FOREARM_home = new wxButton(p_left_arm_FOREARM_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_FOREARM_home->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_FOREARM_home_click, this);
	b_left_arm_FOREARM_move = new wxButton(p_left_arm_FOREARM_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_FOREARM_move->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_FOREARM_move_click, this);

	wxBoxSizer *sizer_left_arm_FOREARM = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_FOREARM->Add(tc_left_arm_FOREARM_motor_position);
	sizer_left_arm_FOREARM->Add(b_left_arm_FOREARM_move);
	sizer_left_arm_FOREARM->Add(b_left_arm_FOREARM_home);
	p_left_arm_FOREARM_position->SetSizer(sizer_left_arm_FOREARM);

	s_left_arm_FOREARM_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_FOREARM_MOTOR, _potentiometer_min_LEFT_ARM_FOREARM_MOTOR, _potentiometer_max_LEFT_ARM_FOREARM_MOTOR);
	s_left_arm_FOREARM_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_left_arm_FOREARM_slider_move, this);
	//-------
	st_left_arm_gripper_IR_signal_strength = new wxStaticText(p_left_arm, wxID_ANY, "Gripper IR signal");
	tc_left_arm_gripper_IR_signal_strength = new wxTextCtrl(p_left_arm, wxID_ANY, "0");
	tc_left_arm_gripper_IR_signal_strength->SetEditable(false);

	cb_left_arm_gripper_closed = new wxCheckBox(p_left_arm, -1, "Gripper closed");
	cb_left_arm_gripper_closed->Enable(false);

	b_left_arm_close_gripper = new wxButton(p_left_arm, -1, "Close Gripper");
	b_left_arm_close_gripper->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_close_gripper_click, this);

	b_left_arm_open_gripper = new wxButton(p_left_arm, -1, "Open Gripper");
	b_left_arm_open_gripper->Bind(wxEVT_LEFT_DOWN, &MainFrame::on_left_arm_open_gripper_mouse_down, this);
	b_left_arm_open_gripper->Bind(wxEVT_LEFT_UP, &MainFrame::on_left_arm_open_gripper_mouse_up, this);

	//-------
	b_left_arm_refresh = new wxButton(p_left_arm, -1, "Read sensors");
	b_left_arm_refresh->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_refresh_data_click, this);

	b_left_arm_home_all = new wxButton(p_left_arm, -1, "Home All");
	b_left_arm_home_all->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_home_all_click, this);

	b_disable_all_left_arm_motors = new wxButton(p_left_arm, -1, "Disable motors");
	b_disable_all_left_arm_motors->Bind(wxEVT_BUTTON, &MainFrame::on_disable_all_left_arm_motors_clicked, this);
	//-------

	b_show_left_arm_camera = new wxButton(p_left_arm, -1, "View camera");
	b_show_left_arm_camera->Bind(wxEVT_BUTTON, &MainFrame::on_show_left_arm_camera_click, this);



	sizer_left_arm->Add(st_left_arm, 0, wxTOP, 10);
	sizer_left_arm->Add(st_left_arm_com_port, 0, wxTOP, 10);
	sizer_left_arm->Add(tc_left_arm_com_port);
	sizer_left_arm->Add(b_connect_to_left_arm, 0, wxTOP, 10);

	sizer_left_arm->Add(st_left_arm_body_motor_position, 0, wxTOP, 10);
	sizer_left_arm->Add(p_left_arm_body_position);
	sizer_left_arm->Add(s_left_arm_body_motor_position);

	sizer_left_arm->Add(st_left_arm_SHOULDER_UP_DOWN_motor_position, 0, wxTOP, 10);
	sizer_left_arm->Add(p_left_arm_SHOULDER_UP_DOWN_position);
	sizer_left_arm->Add(s_left_arm_SHOULDER_UP_DOWN_motor_position);

	sizer_left_arm->Add(st_left_arm_SHOULDER_LEFT_RIGHT_motor_position, 0, wxTOP, 10);
	sizer_left_arm->Add(p_left_arm_SHOULDER_LEFT_RIGHT_position);
	sizer_left_arm->Add(s_left_arm_SHOULDER_LEFT_RIGHT_motor_position);

	sizer_left_arm->Add(st_left_arm_ELBOW_motor_position, 0, wxTOP, 10);
	sizer_left_arm->Add(p_left_arm_ELBOW_position);
	sizer_left_arm->Add(s_left_arm_ELBOW_motor_position);

	sizer_left_arm->Add(st_left_arm_FOREARM_motor_position, 0, wxTOP, 10);
	sizer_left_arm->Add(p_left_arm_FOREARM_position);
	sizer_left_arm->Add(s_left_arm_FOREARM_motor_position);

	sizer_left_arm->Add(st_left_arm_gripper_IR_signal_strength, 0, wxTOP, 10);
	sizer_left_arm->Add(tc_left_arm_gripper_IR_signal_strength);

	sizer_left_arm->Add(cb_left_arm_gripper_closed, 0, wxTOP, 10);

	sizer_left_arm->Add(b_left_arm_close_gripper, 0, wxTOP, 10);
	
	sizer_left_arm->Add(b_left_arm_open_gripper, 0, wxTOP, 10);

	sizer_left_arm->Add(b_left_arm_home_all, 0, wxTOP, 10);
	sizer_left_arm->Add(b_left_arm_refresh, 0, wxTOP, 10);

	sizer_left_arm->Add(b_disable_all_left_arm_motors, 0, wxTOP, 10);

	sizer_left_arm->Add(b_show_left_arm_camera, 0, wxTOP, 10);

	p_left_arm->SetSizer(sizer_left_arm);
	left_arm_set_enable_all(false);
}
//------------------------------------------------------------------------
void MainFrame::left_arm_set_enable_all(bool new_state)
{
	s_left_arm_body_motor_position->Enable(new_state);
	b_left_arm_body_home->Enable(new_state);
	b_left_arm_body_move->Enable(new_state);
	tc_left_arm_body_motor_position->Enable(new_state);

	tc_left_arm_SHOULDER_UP_DOWN_motor_position->Enable(new_state);
	s_left_arm_SHOULDER_UP_DOWN_motor_position->Enable(new_state);
	b_left_arm_SHOULDER_UP_DOWN_home->Enable(new_state);
	b_left_arm_SHOULDER_UP_DOWN_move->Enable(new_state);

	tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position->Enable(new_state);
	s_left_arm_SHOULDER_LEFT_RIGHT_motor_position->Enable(new_state);
	b_left_arm_SHOULDER_LEFT_RIGHT_home->Enable(new_state);
	b_left_arm_SHOULDER_LEFT_RIGHT_move->Enable(new_state);

	tc_left_arm_ELBOW_motor_position->Enable(new_state);
	s_left_arm_ELBOW_motor_position->Enable(new_state);
	b_left_arm_ELBOW_home->Enable(new_state);
	b_left_arm_ELBOW_move->Enable(new_state);

	tc_left_arm_FOREARM_motor_position->Enable(new_state);
	s_left_arm_FOREARM_motor_position->Enable(new_state);
	b_left_arm_FOREARM_home->Enable(new_state);
	b_left_arm_FOREARM_move->Enable(new_state);

	b_left_arm_refresh->Enable(new_state);
	b_left_arm_home_all->Enable(new_state);

	b_left_arm_close_gripper->Enable(new_state);
	b_left_arm_open_gripper->Enable(new_state);

	b_disable_all_left_arm_motors->Enable(new_state);
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_left_arm_click(wxCommandEvent &event)
{
	char error_string[1000];
	long left_arm_com_port;
	tc_left_arm_com_port->GetValue().ToLong(&left_arm_com_port); // real port number

	if (!left_arm_controller.is_connected()) {
		int error_index = left_arm_controller.connect(left_arm_com_port);
		write_to_log(left_arm_controller.error_to_string(error_index));
		if (error_index == E_OK) {
			b_connect_to_left_arm->SetLabel("Disconnect");
			// show the firmware version number
			left_arm_controller.send_get_arduino_firmware_version();

			if (!left_arm_controller.setup(error_string)) {
				write_to_log(error_string);
			}
			else {
				left_arm_controller.send_get_sensors_value();

				left_arm_set_enable_all(true);
			}
		}
		else {
			write_to_log(error_string);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from left arm");
		left_arm_controller.disconnect();
		b_connect_to_left_arm->SetLabel("Connect");
		left_arm_set_enable_all(false);
	}

}
//------------------------------------------------------------------------
void MainFrame::handle_left_arm_events(void)
{
	if (left_arm_controller.is_connected()) {
		left_arm_controller.arduino_controller.update_commands_from_serial();

		char firmware_version[100];
		strcpy(firmware_version, "Left arm firmware version: ");
		if (left_arm_controller.arduino_controller.query_for_firmware_version_event(firmware_version + strlen(firmware_version))) {
			strcat(firmware_version, "\n");
			write_to_log(firmware_version);
		}
		
		intptr_t pot_position;
		char buffer[1000];
		if (left_arm_controller.arduino_controller.query_for_event(POTENTIOMETER_EVENT, LEFT_ARM_BODY_POTENTIOMETER_INDEX, &pot_position)) {
			sprintf(buffer, "Left arm body pot position (%d) = %d\n", LEFT_ARM_BODY_POTENTIOMETER_INDEX, (int)pot_position);
			write_to_log(buffer);
			tc_left_arm_body_motor_position->SetValue(wxString() << pot_position);
			s_left_arm_body_motor_position->SetValue(pot_position);
		}
		if (left_arm_controller.arduino_controller.query_for_event(POTENTIOMETER_EVENT, LEFT_ARM_SHOULDER_UP_DOWN_POTENTIOMETER_INDEX, &pot_position)) {
			sprintf(buffer, "Left arm SHOULDER_UP_DOWN pot position (%d) = %d\n", LEFT_ARM_SHOULDER_UP_DOWN_POTENTIOMETER_INDEX, (int)pot_position);
			write_to_log(buffer);
			tc_left_arm_SHOULDER_UP_DOWN_motor_position->SetValue(wxString() << pot_position);
			s_left_arm_SHOULDER_UP_DOWN_motor_position->SetValue(pot_position);
		}		
		if (left_arm_controller.arduino_controller.query_for_event(POTENTIOMETER_EVENT, LEFT_ARM_SHOULDER_LEFT_RIGHT_POTENTIOMETER_INDEX, &pot_position)) {
			sprintf(buffer, "Left arm SHOULDER_LEFT_RIGHT pot position (%d) = %d\n", LEFT_ARM_SHOULDER_LEFT_RIGHT_POTENTIOMETER_INDEX, (int)pot_position);
			write_to_log(buffer);
			tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position->SetValue(wxString() << pot_position);
			s_left_arm_SHOULDER_LEFT_RIGHT_motor_position->SetValue(pot_position);
		}
		if (left_arm_controller.arduino_controller.query_for_event(POTENTIOMETER_EVENT, LEFT_ARM_ELBOW_POTENTIOMETER_INDEX, &pot_position)) {
			sprintf(buffer, "Left arm ELBOW pot position (%d) = %d\n", LEFT_ARM_ELBOW_POTENTIOMETER_INDEX, (int)pot_position);
			write_to_log(buffer);
			tc_left_arm_ELBOW_motor_position->SetValue(wxString() << pot_position);
			s_left_arm_ELBOW_motor_position->SetValue(pot_position);
		}
		if (left_arm_controller.arduino_controller.query_for_event(POTENTIOMETER_EVENT, LEFT_ARM_FOREARM_POTENTIOMETER_INDEX, &pot_position)) {
			sprintf(buffer, "Left arm FOREARM pot position (%d) = %d\n", LEFT_ARM_FOREARM_POTENTIOMETER_INDEX, (int)pot_position);
			write_to_log(buffer);
			tc_left_arm_FOREARM_motor_position->SetValue(wxString() << pot_position);
			s_left_arm_FOREARM_motor_position->SetValue(pot_position);
		}

		intptr_t infrared_signal_strength;
		if (left_arm_controller.arduino_controller.query_for_event(INFRARED_EVENT, LEFT_ARM_GRIPPER_INFRARED_INDEX, &infrared_signal_strength)) {
			sprintf(buffer, "Left arm GRIPPER infrared signal strength (%d) = %d\n", LEFT_ARM_GRIPPER_INFRARED_INDEX, (int)infrared_signal_strength);
			write_to_log(buffer);
			tc_left_arm_gripper_IR_signal_strength->SetValue(wxString() << infrared_signal_strength);
		}

		intptr_t button_state;
		if (left_arm_controller.arduino_controller.query_for_event(BUTTON_EVENT, LEFT_ARM_GRIPPER_BUTTON_INDEX, &button_state)) {
			sprintf(buffer, "Left arm GRIPPER button state (%d) = %d\n", LEFT_ARM_GRIPPER_BUTTON_INDEX, (int)button_state);
			write_to_log(buffer);
			cb_left_arm_gripper_closed->SetValue((bool)button_state);
		}
	}
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_refresh_data_click(wxCommandEvent &event)
{
	left_arm_controller.send_get_sensors_value();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_home_all_click(wxCommandEvent &event)
{
	char error_str[100];
	left_arm_controller.home_all_motors(error_str);
	write_to_log(error_str);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_body_home_click(wxCommandEvent &event)
{
	left_arm_controller.send_LEFT_ARM_BODY_MOTOR_home();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_body_move_click(wxCommandEvent &event)
{
	long new_position;
	tc_left_arm_body_motor_position->GetValue().ToLong(&new_position);
	left_arm_controller.send_LEFT_ARM_BODY_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_body_slider_move(wxCommandEvent& event)
{
	long new_position = s_left_arm_body_motor_position->GetValue();
	left_arm_controller.send_LEFT_ARM_BODY_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_UP_DOWN_home_click(wxCommandEvent &event)
{
	left_arm_controller.send_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_home();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_UP_DOWN_move_click(wxCommandEvent &event)
{
	long new_position;
	tc_left_arm_SHOULDER_UP_DOWN_motor_position->GetValue().ToLong(&new_position);
	left_arm_controller.send_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_UP_DOWN_slider_move(wxCommandEvent& event)
{
	long new_position = s_left_arm_SHOULDER_UP_DOWN_motor_position->GetValue();
	left_arm_controller.send_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_home_click(wxCommandEvent &event)
{
	left_arm_controller.send_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_home();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_move_click(wxCommandEvent &event)
{
	long new_position;
	tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position->GetValue().ToLong(&new_position);
	left_arm_controller.send_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_slider_move(wxCommandEvent& event)
{
	long new_position = s_left_arm_SHOULDER_LEFT_RIGHT_motor_position->GetValue();
	left_arm_controller.send_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_ELBOW_home_click(wxCommandEvent &event)
{
	left_arm_controller.send_LEFT_ARM_ELBOW_MOTOR_home();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_ELBOW_move_click(wxCommandEvent &event)
{
	long new_position;
	tc_left_arm_ELBOW_motor_position->GetValue().ToLong(&new_position);
	left_arm_controller.send_LEFT_ARM_ELBOW_MOTOR_to_sensor_position(new_position);

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_ELBOW_slider_move(wxCommandEvent& event)
{
	long new_position = s_left_arm_ELBOW_motor_position->GetValue();
	left_arm_controller.send_LEFT_ARM_ELBOW_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_FOREARM_home_click(wxCommandEvent &event)
{
	left_arm_controller.send_LEFT_ARM_FOREARM_MOTOR_home();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_FOREARM_move_click(wxCommandEvent &event)
{
	long new_position;
	tc_left_arm_FOREARM_motor_position->GetValue().ToLong(&new_position);
	left_arm_controller.send_LEFT_ARM_FOREARM_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_FOREARM_slider_move(wxCommandEvent& event)
{
	long new_position = s_left_arm_FOREARM_motor_position->GetValue();
	left_arm_controller.send_LEFT_ARM_FOREARM_MOTOR_to_sensor_position(new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_close_gripper_click(wxCommandEvent &event)
{
	left_arm_controller.send_LEFT_ARM_GRIPPER_MOTOR_home();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_open_gripper_mouse_down(wxMouseEvent &event)
{
	left_arm_controller.send_LEFT_ARM_GRIPPER_MOTOR_start_open();
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_open_gripper_mouse_up(wxMouseEvent &event)
{
	left_arm_controller.send_LEFT_ARM_GRIPPER_MOTOR_stop_open();
}
//------------------------------------------------------------------------
void MainFrame::on_show_left_arm_camera_click(wxCommandEvent &event)
{
	char error_string[1000];
	if (left_arm_controller.left_arm_cam.isOpened()) {
		sprintf(error_string, "Left arm video camera already open!\n");
		write_to_log(error_string);
		return;
	}
	if (!left_arm_controller.left_arm_cam.open(LEFT_ARM_CAMERA_INDEX)){	// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
		sprintf(error_string, "Couldn't open left arm's video camera!\n");
		write_to_log(error_string);
		return;
	}

	Mat cam_frame; // images used in the proces

	namedWindow("Left arm camera", WINDOW_AUTOSIZE); // window to display the results

	bool active = true;
	while (active) {        // starting infinit loop
		left_arm_controller.left_arm_cam >> cam_frame; // put captured-image frame in frame

		imshow("Left arm camera", cam_frame); // display the result

		int key = waitKey(1);
		if (key == VK_ESCAPE)  // break the loop
			active = false;
	}

	destroyWindow("Left arm camera");
	left_arm_controller.left_arm_cam.release();
}
//------------------------------------------------------------------------
void MainFrame::on_disable_all_left_arm_motors_clicked(wxCommandEvent &event)
{
	left_arm_controller.send_disable_motors();
}
//------------------------------------------------------------------------