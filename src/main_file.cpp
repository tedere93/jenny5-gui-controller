#include "main_file.h"
#include "main_window.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//#include "about.h"


wxIMPLEMENT_APP(jenny5_gui_controller_app);


bool jenny5_gui_controller_app::OnInit()
{
	f_main = new MainFrame("Jenny 5 GUI controller", wxPoint(50, 50), wxSize(450, 340));

	f_main->Show(true);
	//f_main->Maximize();

	return true;
}
