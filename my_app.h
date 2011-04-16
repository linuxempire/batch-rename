#ifndef MY_APP_H
#define MY_APP_H
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	wxFrame* _frame;
};
DECLARE_APP(MyApp)
#endif