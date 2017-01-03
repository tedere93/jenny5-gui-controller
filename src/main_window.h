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

	wxPanel *p_predefined_tasks;
	wxPanel *p_head;
	wxPanel *p_left_arm;
	wxPanel *p_right_arm;
	wxPanel *p_lidar;
	wxPanel *p_platform;

	wxStaticText *st_head;
	wxStaticText *st_head_com_port;
	wxTextCtrl *tc_head_com_port;
	wxButton *b_connect_to_head;

	wxStaticText *st_head_neck_motor_position;
	wxTextCtrl *tc_head_neck_motor_position;
	wxSlider *s_head_neck_motor_position;
	wxButton *b_head_neck_home;
	void on_head_neck_home_click(wxCommandEvent &event);
	wxButton *b_head_neck_move;
	void on_head_neck_move_click(wxCommandEvent &event);

	wxStaticText *st_head_face_motor_position;
	wxTextCtrl *tc_head_face_motor_position;
	wxSlider *s_head_face_motor_position;
	wxButton *b_head_face_home;
	void on_head_face_home_click(wxCommandEvent &event);
	wxButton *b_head_face_move;
	void on_head_face_move_click(wxCommandEvent &event);
	
	wxStaticText *st_head_ultrasonic;
	wxTextCtrl *tc_head_ultrasonic;
	
	wxButton *b_head_refresh;
	wxButton *b_head_home_all;

	wxStaticText *st_left_arm;
	wxStaticText *st_left_arm_com_port;
	wxTextCtrl *tc_left_arm_com_port;
	wxButton *b_connect_to_left_arm;

	wxButton *b_left_arm_refresh;

	wxStaticText *st_right_arm;
	wxStaticText *st_right_arm_com_port;
	wxTextCtrl *tc_right_arm_com_port;
	wxButton *b_connect_to_right_arm;

	wxStaticText *st_lidar;
	wxStaticText *st_lidar_com_port;
	wxTextCtrl *tc_lidar_com_port;
	wxButton *b_connect_to_lidar;

	wxStaticText *st_platform;
	wxStaticText *st_platform_com_port;
	wxTextCtrl *tc_platform_com_port;
	wxButton *b_connect_to_platform;

	wxStaticText *st_predefined_tasks;
	wxButton *b_head_face_following;
	wxButton *b_lidar_map;

	t_jenny5_arduino_controller head_controller;
	t_jenny5_arduino_controller left_arm_controller;
	t_jenny5_arduino_controller right_arm_controller;
	t_jenny5_arduino_controller lidar_controller;
	t_roboclaw_controller platform_controller;

	cv::VideoCapture head_cam;
	cv::VideoCapture left_arm_cam;
	cv::VideoCapture right_arm_cam;

	cv::CascadeClassifier face_classifier;

	void BuildInterface(void);
	void OnMainWindowClose(wxCloseEvent& WXUNUSED(event));

	void on_head_face_follow_click(wxCommandEvent &event);
	void on_lidar_map_click(wxCommandEvent &event);
	
	void on_connect_to_head_click(wxCommandEvent &event);
	void on_head_refresh_data_click(wxCommandEvent &event);
	void on_head_home_all_click(wxCommandEvent &event);

	void on_connect_to_lidar_click(wxCommandEvent &event);
	void on_connect_to_left_arm_click(wxCommandEvent &event);
	void on_connect_to_right_arm_click(wxCommandEvent &event);
	void on_connect_to_platform_click(wxCommandEvent &event);

	wxTimer *t_timer;

	void on_timer(wxTimerEvent& event);

public:

	wxTextCtrl *tc_log;
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

};
//------------------------------------------------------------------------

extern MainFrame *f_main;

#endif