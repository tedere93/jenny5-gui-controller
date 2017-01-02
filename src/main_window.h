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
//------------------------------------------------------------------------
class MainFrame : public wxFrame
{
private:

	wxSplitterWindow * splitter_commands_log;

	wxPanel *p_predefined_tasks;
	wxPanel *p_com_ports;
	wxPanel *p_free_moves;

	wxStaticText *st_head_com_port;
	wxTextCtrl *tc_head_com_port;
	wxStaticText *st_left_arm_com_port;
	wxTextCtrl *tc_left_arm_com_port;
	wxStaticText *st_right_arm_com_port;
	wxTextCtrl *tc_right_arm_com_port;
	wxStaticText *st_lidar_com_port;
	wxTextCtrl *tc_lidar_com_port;
	wxStaticText *st_platform_com_port;
	wxTextCtrl *tc_platform_com_port;

	wxButton *b_head_face_following;
	wxButton *b_lidar_map;

	
	t_jenny5_arduino_controller head_controller;
	t_jenny5_arduino_controller left_arm_controller;
	t_jenny5_arduino_controller right_arm_controller;
	t_jenny5_arduino_controller lidar_controller;

	cv::VideoCapture head_cam;
	cv::VideoCapture left_arm_cam;
	cv::VideoCapture right_arm_cam;

	cv::CascadeClassifier face_classifier;

public:

	wxTextCtrl *tc_log;

	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void BuildInterface(void);
	void OnMainWindowClose(wxCloseEvent& WXUNUSED(event));

	void on_head_face_follow_click(wxCommandEvent &event);
	void on_lidar_map_click(wxCommandEvent &event);
};
//------------------------------------------------------------------------

extern MainFrame *f_main;

#endif