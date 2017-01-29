#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_defs.h"
#include "head_controller.h"
#include  "utils.h"

//------------------------------------------------------------------------
void MainFrame::build_head_interface(void)
{
	p_head = new wxPanel(p_commands_panel);

	wxBoxSizer* sizer_head = new wxBoxSizer(wxVERTICAL);
	st_head = new wxStaticText(p_head, wxID_ANY, "Head");
	st_head_com_port = new wxStaticText(p_head, wxID_ANY, "COM port");
	tc_head_com_port = new wxTextCtrl(p_head, wxID_ANY, "7");
	b_connect_to_head = new wxButton(p_head, -1, "Connect");
	b_connect_to_head->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_head_click, this);

	wxPanel *p_head_neck_position = new wxPanel(p_head);
	st_head_neck_motor_position = new wxStaticText(p_head, wxID_ANY, "Neck motor");
	tc_head_neck_motor_position = new wxTextCtrl(p_head_neck_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	b_head_neck_home = new wxButton(p_head_neck_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	
	b_head_neck_home->Bind(wxEVT_BUTTON, &MainFrame::on_head_neck_home_click, this);

	b_head_neck_move = new wxButton(p_head_neck_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_head_neck_move->Bind(wxEVT_BUTTON, &MainFrame::on_head_neck_move_click, this);

	wxBoxSizer *sizer_neck = new wxBoxSizer(wxHORIZONTAL);
	sizer_neck->Add(tc_head_neck_motor_position);
	sizer_neck->Add(b_head_neck_move);
	sizer_neck->Add(b_head_neck_home);
	p_head_neck_position->SetSizer(sizer_neck);

	s_head_neck_motor_position = new wxSlider(p_head, -1, _head_horizontal_motor_potentiometer_min, _head_horizontal_motor_potentiometer_min, _head_horizontal_motor_potentiometer_max);
	s_head_neck_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_head_neck_slider_move, this);

	wxPanel *p_head_face_position = new wxPanel(p_head);
	st_head_face_motor_position = new wxStaticText(p_head, wxID_ANY, "Face motor");
	tc_head_face_motor_position = new wxTextCtrl(p_head_face_position, wxID_ANY, "0", wxDefaultPosition, wxSize(40, -1));
	s_head_face_motor_position = new wxSlider(p_head, -1, _head_vertical_motor_potentiometer_min, _head_vertical_motor_potentiometer_min, _head_vertical_motor_potentiometer_max);
	
	s_head_face_motor_position->Bind(wxEVT_SLIDER, &MainFrame::on_head_face_slider_move, this);

	b_head_face_home = new wxButton(p_head_face_position, -1, "Home", wxDefaultPosition, wxSize(40, -1));
	b_head_face_home->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_home_click, this);
	

	b_head_face_move = new wxButton(p_head_face_position, -1, "Move", wxDefaultPosition, wxSize(40, -1));
	b_head_face_move->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_move_click, this);
	
	

	wxBoxSizer *sizer_face = new wxBoxSizer(wxHORIZONTAL);
	sizer_face->Add(tc_head_face_motor_position);
	sizer_face->Add(b_head_face_move);
	sizer_face->Add(b_head_face_home);
	p_head_face_position->SetSizer(sizer_face);

	st_head_ultrasonic = new wxStaticText(p_head, wxID_ANY, "Ultrasonic");
	tc_head_ultrasonic = new wxTextCtrl(p_head, wxID_ANY, "0");
	tc_head_ultrasonic->SetEditable(false);

	b_head_refresh = new wxButton(p_head, -1, "Read sensors");
	b_head_refresh->Bind(wxEVT_BUTTON, &MainFrame::on_head_refresh_data_click, this);
	

	b_head_home_all = new wxButton(p_head, -1, "Home All");
	b_head_home_all->Bind(wxEVT_BUTTON, &MainFrame::on_head_home_all_click, this);

	b_disable_all_head_motors = new wxButton(p_head, -1, "Disable motors");
	b_disable_all_head_motors->Bind(wxEVT_BUTTON, &MainFrame::on_disable_all_head_motors_clicked, this);
	
	b_show_head_camera = new wxButton(p_head, -1, "View camera");
	b_show_head_camera->Bind(wxEVT_BUTTON, &MainFrame::on_show_head_camera_click, this);

	sizer_head->Add(st_head, 0, wxTOP, 10);
	sizer_head->Add(st_head_com_port, 0, wxTOP, 10);
	sizer_head->Add(tc_head_com_port);
	sizer_head->Add(b_connect_to_head, 0, wxTOP, 10);
	sizer_head->Add(st_head_neck_motor_position, 0, wxTOP, 10);
	sizer_head->Add(p_head_neck_position);
	sizer_head->Add(s_head_neck_motor_position);
	sizer_head->Add(st_head_face_motor_position, 0, wxTOP, 10);
	sizer_head->Add(p_head_face_position);
	sizer_head->Add(s_head_face_motor_position);
	sizer_head->Add(st_head_ultrasonic, 0, wxTOP, 10);
	sizer_head->Add(tc_head_ultrasonic);
	sizer_head->Add(b_head_home_all, 0, wxTOP, 10);
	sizer_head->Add(b_head_refresh, 0, wxTOP, 10);
	sizer_head->Add(b_disable_all_head_motors, 0, wxTOP, 10);
	sizer_head->Add(b_show_head_camera, 0, wxTOP, 10);

	head_set_enable_all(false);

	p_head->SetSizer(sizer_head);
}
//------------------------------------------------------------------------
void MainFrame::head_set_enable_all(bool new_state)
{
	b_head_neck_move->Enable(new_state);
	b_head_neck_home->Enable(new_state);
	s_head_neck_motor_position->Enable(new_state);

	b_head_face_home->Enable(new_state);
	s_head_face_motor_position->Enable(new_state);
	b_head_face_move->Enable(new_state);
	
	b_head_refresh->Enable(new_state);
	b_head_home_all->Enable(new_state);

	b_disable_all_head_motors->Enable(new_state);
}
//--------------------------------------------------------------------------
void  MainFrame::on_connect_to_head_click(wxCommandEvent &event)
{
	char error_string[1000];
	long head_com_port;
	tc_head_com_port->GetValue().ToLong(&head_com_port); // real port number

	if (!jenny5_head_controller.is_connected()) {
		if (jenny5_head_controller.connect(head_com_port, error_string)) {
			b_connect_to_head->SetLabel("Disconnect");
			// show the firmware version number
			jenny5_head_controller.send_get_arduino_firmware_version();

			if (!jenny5_head_controller.setup(error_string)) {
				write_to_log(error_string);
			}
			else {
				jenny5_head_controller.send_get_sensors_value();

				head_set_enable_all(true);
			}
		}
		else {
			write_to_log(error_string);
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from head\n");
		jenny5_head_controller.disconnect();
		b_connect_to_head->SetLabel("Connect");
		head_set_enable_all(false);
	}
}
//------------------------------------------------------------------------
void MainFrame::on_head_refresh_data_click(wxCommandEvent &event)
{
	jenny5_head_controller.send_get_sensors_value();
}
//------------------------------------------------------------------------
void MainFrame::on_head_home_all_click(wxCommandEvent &event)
{
	jenny5_head_controller.send_home_all();
}
//------------------------------------------------------------------------
void MainFrame::on_head_neck_home_click(wxCommandEvent &event)
{
	jenny5_head_controller.send_neck_home();
}
//------------------------------------------------------------------------
void MainFrame::on_head_neck_move_click(wxCommandEvent &event)
{
	long head_neck_new_position;
	tc_head_neck_motor_position->GetValue().ToLong(&head_neck_new_position);

	jenny5_head_controller.send_neck_to_sensor_position(head_neck_new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_head_neck_slider_move(wxCommandEvent& event)
{
	long head_neck_new_position = s_head_neck_motor_position->GetValue();

	jenny5_head_controller.send_neck_to_sensor_position(head_neck_new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_home_click(wxCommandEvent &event)
{
	jenny5_head_controller.send_face_home();
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_move_click(wxCommandEvent &event)
{
	long head_face_new_position;
	tc_head_face_motor_position->GetValue().ToLong(&head_face_new_position); // real port number

	jenny5_head_controller.send_face_to_sensor_position(head_face_new_position);
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_slider_move(wxCommandEvent& event)
{
	long head_face_new_position = s_head_face_motor_position->GetValue(); // real port number

	jenny5_head_controller.send_face_to_sensor_position(head_face_new_position);
}
//------------------------------------------------------------------------
void MainFrame::handle_head_events(void)
{
	if (jenny5_head_controller.is_connected()) {
		jenny5_head_controller.head_arduino_controller.update_commands_from_serial();

		char firmware_version[100];
		strcpy(firmware_version, "Head firmware version: ");

		if (jenny5_head_controller.head_arduino_controller.query_for_firmware_version_event(firmware_version + strlen(firmware_version))) {
			strcat(firmware_version, "\n");
			write_to_log(firmware_version);
		}

		intptr_t pot_position;
		char buffer[100];
		if (jenny5_head_controller.head_arduino_controller.query_for_event(POTENTIOMETER_EVENT, HEAD_POTENTIOMETER_NECK_INDEX, &pot_position)) {
			sprintf(buffer, "Head neck position = %d\n", (int)pot_position);
			write_to_log(buffer);
			tc_head_neck_motor_position->SetValue(wxString() << pot_position);
			s_head_neck_motor_position->SetValue(pot_position);
		}

		if (jenny5_head_controller.head_arduino_controller.query_for_event(POTENTIOMETER_EVENT, HEAD_POTENTIOMETER_FACE_INDEX, &pot_position)) {
			sprintf(buffer, "Head face position = %d\n", (int)pot_position);
			write_to_log(buffer);
			tc_head_face_motor_position->SetValue(wxString() << pot_position);
			s_head_face_motor_position->SetValue(pot_position);
		}

		intptr_t ultrasonic_distance;
		if (jenny5_head_controller.head_arduino_controller.query_for_event(SONAR_EVENT, 0, &ultrasonic_distance)) {
			sprintf(buffer, "Head ultrasonic distance = %d\n", (int)ultrasonic_distance);
			write_to_log(buffer);
			tc_head_ultrasonic->SetValue(wxString() << ultrasonic_distance);
		}
		/*
		intptr_t motor_steps_left_to_move;
		if (jenny5_head_controller.head_arduino_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_NECK, &motor_steps_left_to_move)) {
			//sprintf(buffer, "Head pot position (%d) = %d\n", HEAD_POTENTIOMETER_NECK_INDEX, (int)pot_position);
			write_to_log(buffer);
			jenny5_head_controller.head_arduino_controller.send_get_potentiometer_position(HEAD_POTENTIOMETER_NECK_INDEX); // request potentiometer position
		}

		if (jenny5_head_controller.head_arduino_controller.query_for_event(STEPPER_MOTOR_MOVE_DONE_EVENT, HEAD_MOTOR_FACE, &motor_steps_left_to_move)) {
			//sprintf(buffer, "Head pot position (%d) = %d\n", HEAD_POTENTIOMETER_FACE_INDEX, (int)pot_position);
			write_to_log(buffer);
			jenny5_head_controller.head_arduino_controller.send_get_potentiometer_position(HEAD_POTENTIOMETER_FACE_INDEX); // request potentiometer position
		}
		*/
	}
}
//------------------------------------------------------------------------
void MainFrame::on_show_head_camera_click(wxCommandEvent &event)
{
	char error_string[1000];
	if (jenny5_head_controller.head_cam.isOpened()) {
		sprintf(error_string, "Head video camera already open!\n");
		write_to_log(error_string);
		return;
	}
	if (!jenny5_head_controller.head_cam.open(HEAD_CAMERA_INDEX)){	// link it to the device [0 = default cam] (USBcam is default 'cause I disabled the onbord one IRRELEVANT!)
		sprintf(error_string, "Couldn't open head's video camera!\n");
		write_to_log(error_string);
		return;
	}

	Mat cam_frame; // images used in the proces

	namedWindow("Head camera", WINDOW_AUTOSIZE); // window to display the results

	bool active = true;
	while (active) {        // starting infinit loop
		jenny5_head_controller.head_cam >> cam_frame; // put captured-image frame in frame

		imshow("Head camera", cam_frame); // display the result

		int key = waitKey(1);
		if (key == VK_ESCAPE)  // break the loop
			active = false;
	}

	destroyWindow("Head camera");
	jenny5_head_controller.head_cam.release();
}
//------------------------------------------------------------------------
void MainFrame::on_disable_all_head_motors_clicked(wxCommandEvent &event)
{
	jenny5_head_controller.send_disable_motors();
}
//------------------------------------------------------------------------