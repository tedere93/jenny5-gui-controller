// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#pragma once

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/grid.h>
#include <wx/tglbtn.h>
#include <wx/vscroll.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/splitter.h>

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "jenny5_arduino_controller.h"
#include "roboclaw_controller.h"
//------------------------------------------------------------------------
class MainFrame : public wxFrame
{
private:

	wxSplitterWindow * splitter_commands_log;

	wxPanel *p_commands_panel;
	wxPanel *p_log_panel;

	//----------------------------------------------
	wxPanel *p_predefined_tasks;
	wxStaticText *st_predefined_tasks;
	wxButton *b_head_face_following;
	void on_head_face_follow_click(wxCommandEvent &event);

	wxButton *b_lidar_map;
	void on_lidar_map_click(wxCommandEvent &event);
	wxButton *b_follow_person;
	void on_follow_person_click(wxCommandEvent &event);

	void build_predefined_task_interface(void);

	//----------------------------------------------

	
	wxPanel *p_head;
	
	wxStaticText *st_head;
	wxStaticText *st_head_com_port;
	wxTextCtrl *tc_head_com_port;
	wxButton *b_connect_to_head;
	void on_connect_to_head_click(wxCommandEvent &event);

	wxStaticText *st_head_neck_motor_position;
	wxTextCtrl *tc_head_neck_motor_position;
	wxSlider *s_head_neck_motor_position;
	wxButton *b_head_neck_home;
	void on_head_neck_home_click(wxCommandEvent &event);
	wxButton *b_head_neck_move;
	void on_head_neck_move_click(wxCommandEvent &event);
	void on_head_neck_slider_move(wxCommandEvent& event);

	wxStaticText *st_head_face_motor_position;
	wxTextCtrl *tc_head_face_motor_position;
	wxSlider *s_head_face_motor_position;
	wxButton *b_head_face_home;
	void on_head_face_home_click(wxCommandEvent &event);
	wxButton *b_head_face_move;
	void on_head_face_move_click(wxCommandEvent &event);
	void on_head_face_slider_move(wxCommandEvent& event);
	
	wxStaticText *st_head_ultrasonic;
	wxTextCtrl *tc_head_ultrasonic;
	
	wxButton *b_head_refresh;
	void on_head_refresh_data_click(wxCommandEvent &event);
	wxButton *b_head_home_all;
	void on_head_home_all_click(wxCommandEvent &event);

	void head_set_enable_all(bool new_state);

	void handle_head_events(void);
	void build_head_interface(void);
	
	wxButton *b_show_head_camera;
	void on_show_head_camera_click(wxCommandEvent &event);

	wxButton *b_disable_all_head_motors;
	void on_disable_all_head_motors_clicked(wxCommandEvent &event);
	//--------------------------------------------------------------

	wxPanel *p_left_arm;
	wxStaticText *st_left_arm;
	wxStaticText *st_left_arm_com_port;
	wxTextCtrl *tc_left_arm_com_port;
	wxButton *b_connect_to_left_arm;

	wxStaticText *st_left_arm_body_motor_position;
	wxTextCtrl *tc_left_arm_body_motor_position;
	wxSlider *s_left_arm_body_motor_position;
	void on_left_arm_body_slider_move(wxCommandEvent& event);
	wxButton *b_left_arm_body_home;
	void on_left_arm_body_home_click(wxCommandEvent &event);
	wxButton *b_left_arm_body_move;
	void on_left_arm_body_move_click(wxCommandEvent &event);

	wxStaticText *st_left_arm_SHOULDER_UP_DOWN_motor_position;
	wxTextCtrl *tc_left_arm_SHOULDER_UP_DOWN_motor_position;
	wxSlider *s_left_arm_SHOULDER_UP_DOWN_motor_position;
	void on_left_arm_SHOULDER_UP_DOWN_slider_move(wxCommandEvent& event);
	wxButton *b_left_arm_SHOULDER_UP_DOWN_home;
	void on_left_arm_SHOULDER_UP_DOWN_home_click(wxCommandEvent &event);
	wxButton *b_left_arm_SHOULDER_UP_DOWN_move;
	void on_left_arm_SHOULDER_UP_DOWN_move_click(wxCommandEvent &event);

	wxStaticText *st_left_arm_SHOULDER_LEFT_RIGHT_motor_position;
	wxTextCtrl *tc_left_arm_SHOULDER_LEFT_RIGHT_motor_position;
	wxSlider *s_left_arm_SHOULDER_LEFT_RIGHT_motor_position;
	void on_left_arm_SHOULDER_LEFT_RIGHT_slider_move(wxCommandEvent& event);
	wxButton *b_left_arm_SHOULDER_LEFT_RIGHT_home;
	void on_left_arm_SHOULDER_LEFT_RIGHT_home_click(wxCommandEvent &event);
	wxButton *b_left_arm_SHOULDER_LEFT_RIGHT_move;
	void on_left_arm_SHOULDER_LEFT_RIGHT_move_click(wxCommandEvent &event);

	wxStaticText *st_left_arm_ELBOW_motor_position;
	wxTextCtrl *tc_left_arm_ELBOW_motor_position;
	wxSlider *s_left_arm_ELBOW_motor_position;
	void on_left_arm_ELBOW_slider_move(wxCommandEvent& event);
	wxButton *b_left_arm_ELBOW_home;
	void on_left_arm_ELBOW_home_click(wxCommandEvent &event);
	wxButton *b_left_arm_ELBOW_move;
	void on_left_arm_ELBOW_move_click(wxCommandEvent &event);

	wxStaticText *st_left_arm_FOREARM_motor_position;
	wxTextCtrl *tc_left_arm_FOREARM_motor_position;
	wxSlider *s_left_arm_FOREARM_motor_position;
	void on_left_arm_FOREARM_slider_move(wxCommandEvent& event);
	wxButton *b_left_arm_FOREARM_home;
	void on_left_arm_FOREARM_home_click(wxCommandEvent &event);
	wxButton *b_left_arm_FOREARM_move;
	void on_left_arm_FOREARM_move_click(wxCommandEvent &event);

	wxStaticText *st_left_arm_gripper_IR_signal_strength;
	wxTextCtrl *tc_left_arm_gripper_IR_signal_strength;

	wxCheckBox* cb_left_arm_gripper_closed;

	wxButton *b_left_arm_close_gripper;
	void on_left_arm_close_gripper_click(wxCommandEvent &event);

	wxButton *b_left_arm_open_gripper;
	void on_left_arm_open_gripper_mouse_down(wxMouseEvent &event);
	void on_left_arm_open_gripper_mouse_up(wxMouseEvent &event);


	wxButton *b_left_arm_refresh;
	void on_left_arm_refresh_data_click(wxCommandEvent &event);
	wxButton *b_left_arm_home_all;
	void on_left_arm_home_all_click(wxCommandEvent &event);

	void handle_left_arm_events(void);
	void build_left_arm_interface(void);
	void on_connect_to_left_arm_click(wxCommandEvent &event);
	void left_arm_set_enable_all(bool new_state);

	wxButton *b_show_left_arm_camera;
	void on_show_left_arm_camera_click(wxCommandEvent &event);

	wxButton *b_disable_all_left_arm_motors;
	void on_disable_all_left_arm_motors_clicked(wxCommandEvent &event);
	//--------------------------------------------------------------
	t_jenny5_arduino_controller right_arm_controller;
	cv::VideoCapture right_arm_cam;

	wxPanel *p_right_arm;

	wxStaticText *st_right_arm;
	wxStaticText *st_right_arm_com_port;
	wxTextCtrl *tc_right_arm_com_port;
	wxButton *b_connect_to_right_arm;
	void build_right_arm_interface(void);
	void on_connect_to_right_arm_click(wxCommandEvent &event);

	//--------------------------------------------------------------
	
	wxPanel *p_lidar;
	wxStaticText *st_lidar;
	wxStaticText *st_lidar_com_port;
	wxTextCtrl *tc_lidar_com_port;
	wxButton *b_connect_to_lidar;
	void on_connect_to_lidar_click(wxCommandEvent &event);
	void build_lidar_interface(void);

	//--------------------------------------------------------------
	t_roboclaw_controller platform_controller;
	wxPanel *p_platform;
	wxStaticText *st_platform;
	wxStaticText *st_platform_com_port;
	wxTextCtrl *tc_platform_com_port;
	wxButton *b_connect_to_platform;
	void on_connect_to_platform_click(wxCommandEvent &event);

	wxStaticText *st_platform_left_motor_speed;
	wxSlider *s_platform_left_motor_speed;
	void on_platform_left_motor_slider_move(wxCommandEvent & event);
	wxTextCtrl *tc_platform_left_motor_speed;

	wxStaticText *st_platform_right_motor_speed;
	wxSlider *s_platform_right_motor_speed;
	void on_platform_right_motor_slider_move(wxCommandEvent & event);
	wxTextCtrl *tc_platform_right_motor_speed;

	wxStaticText *st_platform_battery_voltage;
	wxTextCtrl *tc_platform_battery_voltage;

	wxStaticText *st_platform_rotate_speed;
	wxSlider *s_platform_rotate_speed;
	void on_platform_rotate_speed_slider_move(wxCommandEvent & event);
	wxTextCtrl *tc_platform_rotate_speed;
	wxButton *b_rotate_platform;
	void on_platform_rotate_mouse_down(wxMouseEvent &event);
	void on_platform_rotate_mouse_up(wxMouseEvent &event);


	wxButton *b_run_platform_motors;
	void on_platform_run_motors_mouse_down(wxMouseEvent &event);
	void on_platform_run_motors_mouse_up(wxMouseEvent &event);

	wxPanel *p_platform_2d_slider;
	void on_platform_2d_mouse_move(wxMouseEvent& event);
	void on_platform_2d_mouse_down(wxMouseEvent& event);
	void on_platform_2d_mouse_up(wxMouseEvent& event);

	void build_platform_interface(void);

	//--------------------------------------------------------------
	t_roboclaw_controller leg_controller;
	wxPanel *p_leg;
	wxStaticText *st_leg;
	wxStaticText *st_leg_com_port;
	wxTextCtrl *tc_leg_com_port;
	wxButton *b_connect_to_leg;
	void on_connect_to_leg_click(wxCommandEvent &event);

	wxButton *b_expand_leg;
	void on_leg_expand_mouse_down(wxMouseEvent &event);
	void on_leg_expand_mouse_up(wxMouseEvent &event);

	wxButton *b_contract_leg;
	void on_leg_contract_mouse_down(wxMouseEvent &event);
	void on_leg_contract_mouse_up(wxMouseEvent &event);

	wxButton *b_expand_top_leg_motor;
	void on_leg_expand_top_motor_mouse_down(wxMouseEvent &event);
	void on_leg_expand_top_motor_mouse_up(wxMouseEvent &event);

	wxButton *b_contract_top_leg_motor;
	void on_leg_contract_top_motor_mouse_down(wxMouseEvent &event);
	void on_leg_contract_top_motor_mouse_up(wxMouseEvent &event);

	wxButton *b_expand_bottom_leg_motor;
	void on_leg_expand_bottom_motor_mouse_down(wxMouseEvent &event);
	void on_leg_expand_bottom_motor_mouse_up(wxMouseEvent &event);

	wxButton *b_contract_bottom_leg_motor;
	void on_leg_contract_bottom_motor_mouse_down(wxMouseEvent &event);
	void on_leg_contract_bottom_motor_mouse_up(wxMouseEvent &event);

	wxStaticText *st_leg_speed;
	wxSlider *s_leg_speed;
	void on_leg_speed_slider_move(wxCommandEvent & event);
	wxTextCtrl *tc_leg_speed;

	void leg_set_enable_all(bool new_state);

	void build_leg_interface(void);

	//--------------------------------------------------------------

	void build_interface(void);
	void OnMainWindowClose(wxCloseEvent& WXUNUSED(event));

	wxTimer *t_timer;

	void on_timer(wxTimerEvent& event);
public:

	wxTextCtrl *tc_log;
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};
//------------------------------------------------------------------------
void write_to_log(char* str);
extern MainFrame *f_main;
//------------------------------------------------------------------------

#endif