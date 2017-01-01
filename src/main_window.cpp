#include <opencv2\imgproc\imgproc.hpp>

#include "main_window.h"
#include "setup_functions.h"
#include "home.h"
#include "jenny5_gui_defs.h"
#include  "utils.h"
#include "head_face_follow.h"

MainFrame *f_main;

#include <vld.h>

//------------------------------------------------------------------------
void MainFrame::BuildInterface(void)
{
	b_head_face_following = new wxButton(this, wxID_ANY, "Head follow face");
	b_head_face_following->Bind(wxEVT_BUTTON, &MainFrame::on_head_face_follow_click, this);

	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnMainWindowClose, this);

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
	delete b_head_face_following;

	Destroy();
}
//------------------------------------------------------------------------
void MainFrame::on_head_face_follow_click(wxCommandEvent &event)
{
	int head_com_port = 9; // real port number

	char error_string[1000];
	if (head_face_follow(head_controller, head_com_port, head_cam, face_classifier, error_string) == -1) {
		wxMessageBox(error_string, "Error");
	}
}
//------------------------------------------------------------------------
