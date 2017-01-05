// copyright Mihai Oltean, mihai.oltean@gmail.com
// www.jenny5.org
// www.tcreate.org
// source code: https://github.com/jenny5-robot

// MIT License
// ---------------------------------------------------------------------------

#include "main_file.h"
#include "main_window.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//#include "about.h"

#include <vld.h>

wxIMPLEMENT_APP(jenny5_gui_controller_app);


bool jenny5_gui_controller_app::OnInit()
{
	f_main = new MainFrame("Jenny 5 GUI controller 2017.01.05.0", wxPoint(50, 50), wxSize(800, 830));

	f_main->Show(true);
	//f_main->Maximize();

	return true;
}
