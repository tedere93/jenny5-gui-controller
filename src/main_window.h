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



//------------------------------------------------------------------------
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void BuildInterface(void);
	void OnMainWindowClose(wxCloseEvent& WXUNUSED(event));

	void on_head_face_follow_click(wxCommandEvent &event);
};
//------------------------------------------------------------------------

extern MainFrame *f_main;

#endif