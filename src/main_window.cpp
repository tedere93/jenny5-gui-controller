#include <opencv2\imgproc\imgproc.hpp>

#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"
#include "head_face_follow.h"

MainFrame *f_main;

//------------------------------------------------------------------------
void MainFrame::BuildInterface(void)
{
	wxButton *b_head_face_following = new wxButton(this, wxID_ANY, "Head follow face");
	b_head_face_following->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_follow_click, this);

}
//------------------------------------------------------------------------
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	BuildInterface();
}
//------------------------------------------------------------------------
void MainFrame::OnMainWindowClose(wxCloseEvent& WXUNUSED(event))
{

	Destroy();
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_follow_click(wxCommandEvent &event)
{
	char error_string[1000];
	if (head_face_follow(error_string) == -1) {
		wxMessageBox(error_string, "Error");
	}
}
//------------------------------------------------------------------------
