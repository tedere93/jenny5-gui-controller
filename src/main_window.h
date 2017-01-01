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
	wxButton *b_head_face_following;


	t_jenny5_arduino_controller head_controller;
	cv::VideoCapture head_cam;
	cv::CascadeClassifier face_classifier;
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void BuildInterface(void);
	void OnMainWindowClose(wxCloseEvent& WXUNUSED(event));

	void on_head_face_follow_click(wxCommandEvent &event);
};
//------------------------------------------------------------------------

extern MainFrame *f_main;

#endif