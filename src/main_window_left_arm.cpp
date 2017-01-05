#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"

//------------------------------------------------------------------------
void MainFrame::build_left_arm_interface(void)
{
	p_left_arm = new wxPanel(p_commands_panel);
	wxBoxSizer* sizer_left_arm = new wxBoxSizer(wxVERTICAL);
	st_left_arm = new wxStaticText(p_left_arm, wxID_ANY, "Left arm");
	st_left_arm_com_port = new wxStaticText(p_left_arm, wxID_ANY, "COM port");
	tc_left_arm_com_port = new wxTextCtrl(p_left_arm, wxID_ANY, "1");
	b_connect_to_left_arm = new wxButton(p_left_arm, -1, "Connect");
	b_connect_to_left_arm->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_left_arm_click, this);
//-------
	wxPanel *p_left_arm_body_position = new wxPanel(p_left_arm);
	st_left_arm_body_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Body motor");
	tc_left_arm_body_motor_position = new wxTextCtrl(p_left_arm_body_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_body_home = new wxButton(p_left_arm_body_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_body_move = new wxButton(p_left_arm_body_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_left_arm_body = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_body->Add(tc_left_arm_body_motor_position);
	sizer_left_arm_body->Add(b_left_arm_body_move);
	sizer_left_arm_body->Add(b_left_arm_body_home);
	p_left_arm_body_position->SetSizer(sizer_left_arm_body);

	s_left_arm_body_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_BODY_MOTOR, _potentiometer_min_LEFT_ARM_BODY_MOTOR, _potentiometer_max_LEFT_ARM_BODY_MOTOR);
	//-------
	wxPanel *p_left_arm_SHOULDER_UP_DOWN_position = new wxPanel(p_left_arm);
	st_left_arm_SHOULDER_UP_DOWN_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Shoulder up down motor");
	tc_left_arm_SHOULDER_UP_DOWN_motor_position = new wxTextCtrl(p_left_arm_SHOULDER_UP_DOWN_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_UP_DOWN_home = new wxButton(p_left_arm_SHOULDER_UP_DOWN_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_UP_DOWN_move = new wxButton(p_left_arm_SHOULDER_UP_DOWN_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_left_arm_SHOULDER_UP_DOWN = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_SHOULDER_UP_DOWN->Add(tc_left_arm_SHOULDER_UP_DOWN_motor_position);
	sizer_left_arm_SHOULDER_UP_DOWN->Add(b_left_arm_SHOULDER_UP_DOWN_move);
	sizer_left_arm_SHOULDER_UP_DOWN->Add(b_left_arm_SHOULDER_UP_DOWN_home);
	p_left_arm_SHOULDER_UP_DOWN_position->SetSizer(sizer_left_arm_SHOULDER_UP_DOWN);

	s_left_arm_SHOULDER_UP_DOWN_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, _potentiometer_min_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR, _potentiometer_max_LEFT_ARM_SHOULDER_UP_DOWN_MOTOR);
	//-------
	wxPanel *p_left_arm_SHOULDER_LEFT_RIGHT_position = new wxPanel(p_left_arm);
	st_left_arm_SHOULDER_LEFT_RIGHT_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Shoulder left right motor");
	tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position = new wxTextCtrl(p_left_arm_SHOULDER_LEFT_RIGHT_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_LEFT_RIGHT_home = new wxButton(p_left_arm_SHOULDER_LEFT_RIGHT_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_SHOULDER_LEFT_RIGHT_move = new wxButton(p_left_arm_SHOULDER_LEFT_RIGHT_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_left_arm_SHOULDER_LEFT_RIGHT = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_SHOULDER_LEFT_RIGHT->Add(tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position);
	sizer_left_arm_SHOULDER_LEFT_RIGHT->Add(b_left_arm_SHOULDER_LEFT_RIGHT_move);
	sizer_left_arm_SHOULDER_LEFT_RIGHT->Add(b_left_arm_SHOULDER_LEFT_RIGHT_home);
	p_left_arm_SHOULDER_LEFT_RIGHT_position->SetSizer(sizer_left_arm_SHOULDER_LEFT_RIGHT);

	s_left_arm_SHOULDER_LEFT_RIGHT_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, _potentiometer_min_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR, _potentiometer_max_LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR);
	//-------
	wxPanel *p_left_arm_ELBOW_position = new wxPanel(p_left_arm);
	st_left_arm_ELBOW_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Elbow motor");
	tc_left_arm_ELBOW_motor_position = new wxTextCtrl(p_left_arm_ELBOW_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_ELBOW_home = new wxButton(p_left_arm_ELBOW_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_ELBOW_move = new wxButton(p_left_arm_ELBOW_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_left_arm_ELBOW = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_ELBOW->Add(tc_left_arm_ELBOW_motor_position);
	sizer_left_arm_ELBOW->Add(b_left_arm_ELBOW_move);
	sizer_left_arm_ELBOW->Add(b_left_arm_ELBOW_home);
	p_left_arm_ELBOW_position->SetSizer(sizer_left_arm_ELBOW);

	s_left_arm_ELBOW_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_ELBOW_MOTOR, _potentiometer_min_LEFT_ARM_ELBOW_MOTOR, _potentiometer_max_LEFT_ARM_ELBOW_MOTOR);
	//-------
	wxPanel *p_left_arm_FOREARM_position = new wxPanel(p_left_arm);
	st_left_arm_FOREARM_motor_position = new wxStaticText(p_left_arm, wxID_ANY, "Forearm motor");
	tc_left_arm_FOREARM_motor_position = new wxTextCtrl(p_left_arm_FOREARM_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_FOREARM_home = new wxButton(p_left_arm_FOREARM_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_left_arm_FOREARM_move = new wxButton(p_left_arm_FOREARM_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));

	wxBoxSizer *sizer_left_arm_FOREARM = new wxBoxSizer(wxHORIZONTAL);
	sizer_left_arm_FOREARM->Add(tc_left_arm_FOREARM_motor_position);
	sizer_left_arm_FOREARM->Add(b_left_arm_FOREARM_move);
	sizer_left_arm_FOREARM->Add(b_left_arm_FOREARM_home);
	p_left_arm_FOREARM_position->SetSizer(sizer_left_arm_FOREARM);

	s_left_arm_FOREARM_motor_position = new wxSlider(p_left_arm, -1, _potentiometer_min_LEFT_ARM_FOREARM_MOTOR, _potentiometer_min_LEFT_ARM_FOREARM_MOTOR, _potentiometer_max_LEFT_ARM_FOREARM_MOTOR);






	b_left_arm_refresh = new wxButton(p_left_arm, -1, "Refresh");
	b_left_arm_refresh->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_refresh_data_click, this);

	b_left_arm_home_all = new wxButton(p_left_arm, -1, "Home All");
	b_left_arm_home_all->Bind(wxEVT_BUTTON, &MainFrame::on_left_arm_home_all_click, this);


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

	sizer_left_arm->Add(b_left_arm_home_all, 0, wxTOP, 10);
	sizer_left_arm->Add(b_left_arm_refresh, 0, wxTOP, 10);

	p_left_arm->SetSizer(sizer_left_arm);
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_left_arm_click(wxCommandEvent &event)
{
	char error_string[1000];
	long left_arm_com_port;
	tc_left_arm_com_port->GetValue().ToLong(&left_arm_com_port); // real port number

	if (!left_arm_controller.is_open()) {
		if (connect_to_left_arm(left_arm_controller, left_arm_cam, left_arm_com_port, error_string)) {
			b_connect_to_left_arm->SetLabel("Disconnect");
			// show the firmware version number
			left_arm_controller.send_get_firmware_version();

			if (!setup_left_arm(left_arm_controller, error_string)) {
				write_to_log(error_string);
			}
			else {
				left_arm_controller.send_get_potentiometer_position(0);
				left_arm_controller.send_get_potentiometer_position(1);

			}
		}
		else {
			write_to_log(error_string);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from left arm");
		left_arm_controller.close_connection();
		b_connect_to_left_arm->SetLabel("Connect");
	}

}
//------------------------------------------------------------------------
void MainFrame::handle_left_arm_events(void)
{
	if (left_arm_controller.is_open()) {
		left_arm_controller.update_commands_from_serial();

		char firmware_version[100];
		strcpy(firmware_version, "Left arm firmware version: ");

		if (left_arm_controller.query_for_firmware_version_event(firmware_version + strlen(firmware_version))) {
			strcat(firmware_version, "\n");
			write_to_log(firmware_version);
		}

		intptr_t pot_position;
		char buffer[100];
		if (left_arm_controller.query_for_event(POTENTIOMETER_EVENT, HEAD_POTENTIOMETER_NECK_INDEX, &pot_position)) {
			sprintf(buffer, "Left arm body pot position (%d) = %d\n", HEAD_POTENTIOMETER_NECK_INDEX, (int)pot_position);
			write_to_log(buffer);
			tc_left_arm_body_motor_position->SetValue(wxString() << pot_position);
			s_left_arm_body_motor_position->SetValue(pot_position);
		}
		/*
		if (left_arm_controller.query_for_event(POTENTIOMETER_EVENT, HEAD_POTENTIOMETER_FACE_INDEX, &pot_position)) {
		sprintf(buffer, "Left arm pot position (%d) = %d\n", HEAD_POTENTIOMETER_FACE_INDEX, pot_position);
		write_to_log(buffer);
		tc_head_face_motor_position->SetValue(wxString() << pot_position);
		s_head_face_motor_position->SetValue(pot_position);
		}
		*/
		/*
		int button_state;
		if (left_arm_controller.query_for_event(BUTTON_EVENT, 0, &button_state)) {
		sprintf(buffer, "Button state = %d\n", button_state);
		write_to_log(buffer);
		tc_head_ultrasonic->SetValue(wxString() << button_state);
		}
		*/
	}
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_refresh_data_click(wxCommandEvent &event)
{
	left_arm_controller.send_get_potentiometer_position(LEFT_ARM_BODY_POTENTIOMETER_INDEX);
	left_arm_controller.send_get_potentiometer_position(LEFT_ARM_SHOULDER_UP_DOWN_POTENTIOMETER_INDEX);
	left_arm_controller.send_get_potentiometer_position(LEFT_ARM_SHOULDER_LEFT_RIGHT_POTENTIOMETER_INDEX);
	left_arm_controller.send_get_potentiometer_position(LEFT_ARM_ELBOW_POTENTIOMETER_INDEX);
	left_arm_controller.send_get_potentiometer_position(LEFT_ARM_FOREARM_POTENTIOMETER_INDEX);
	left_arm_controller.send_get_button_state(LEFT_ARM_GRIPPER_BUTTON_INDEX);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_home_all_click(wxCommandEvent &event)
{
	left_arm_controller.send_go_home_dc_motor(LEFT_ARM_BODY_MOTOR);
	left_arm_controller.send_go_home_dc_motor(LEFT_ARM_SHOULDER_UP_DOWN_MOTOR);
	left_arm_controller.send_go_home_dc_motor(LEFT_ARM_SHOULDER_LEFT_RIGHT_MOTOR);
	left_arm_controller.send_go_home_dc_motor(LEFT_ARM_ELBOW_MOTOR);
	left_arm_controller.send_go_home_dc_motor(LEFT_ARM_FOREARM_MOTOR);
	left_arm_controller.send_go_home_dc_motor(LEFT_ARM_GRIPPER_MOTOR);
}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_body_home_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_body_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_UP_DOWN_home_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_UP_DOWN_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_home_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_SHOULDER_LEFT_RIGHT_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_ELBOW_home_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_ELBOW_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_FOREARM_home_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------
void MainFrame::on_left_arm_FOREARM_move_click(wxCommandEvent &event)
{

}
//------------------------------------------------------------------------