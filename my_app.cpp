#include <wx/wx.h>

#include "my_app.h"
#include "my_frame.h"

bool MyApp::OnInit()
{
	_frame = new MyFrame();
	_frame->Show();
	return true;
}

IMPLEMENT_APP(MyApp)