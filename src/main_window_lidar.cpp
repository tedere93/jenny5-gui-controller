#include "main_window.h"
#include "lidar_controller.h"
#include "jenny5_defs.h"


//------------------------------------------------------------------------
void MainFrame::build_lidar_interface(void)
{
	p_lidar = new wxPanel(p_commands_panel);
	wxBoxSizer* sizer_lidar = new wxBoxSizer(wxVERTICAL);
	st_lidar = new wxStaticText(p_lidar, wxID_ANY, "LIDAR");
	st_lidar_com_port = new wxStaticText(p_lidar, wxID_ANY, "COM port");
	tc_lidar_com_port = new wxTextCtrl(p_lidar, wxID_ANY, "22");
	
	b_connect_to_lidar = new wxButton(p_lidar, -1, "Connect");
	b_connect_to_lidar->Bind(wxEVT_BUTTON, &MainFrame::on_connect_to_lidar_click, this);

	sizer_lidar->Add(st_lidar, 0, wxTOP, 10);
	sizer_lidar->Add(st_lidar_com_port, 0, wxTOP, 10);
	sizer_lidar->Add(tc_lidar_com_port);
	sizer_lidar->Add(b_connect_to_lidar, 0, wxTOP, 10);

	p_lidar->SetSizer(sizer_lidar);
}
//------------------------------------------------------------------------
void MainFrame::on_connect_to_lidar_click(wxCommandEvent &event)
{
	char error_string[1000];
	long lidar_com_port;
	tc_lidar_com_port->GetValue().ToLong(&lidar_com_port); // real port number

	if (!LIDAR_controller.is_connected()) {
		int error_index = LIDAR_controller.connect(lidar_com_port);
		write_to_log(LIDAR_controller.error_to_string(error_index));
		if (error_index == E_OK) {
			b_connect_to_lidar->SetLabel("Disconnect");
			// show the firmware version number
			//LIDAR_controller.send_get_arduino_firmware_version();

			if (!LIDAR_controller.setup(error_string)) {
				write_to_log(error_string);
			}
			else {
				//jenny5_head_controller.send_get_sensors_value();

				//head_set_enable_all(true);
			}
		}
		else {
			write_to_log(LIDAR_controller.error_to_string(error_index));
		}
	}// is open, so just disconect
	else {
		write_to_log("Disconnected from LIDAR\n");
		LIDAR_controller.disconnect();
		b_connect_to_lidar->SetLabel("Connect");
		//head_set_enable_all(false);
	}

}
//------------------------------------------------------------------------
