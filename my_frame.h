#ifndef MY_FRAME_H
#define MY_FRAME_H
#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
	MyFrame();

	/**
	 *	退出
	 */
	void OnQuit(wxCommandEvent& event);
	/**
	 *	关于对话框
	 */
	void OnAbout(wxCommandEvent& event);
	/**
	 *	选择源路径
	 */
	void OnSelectSourceDir(wxCommandEvent & WXUNUSED(event));
	/**
	 *	选择源路径
	 */
	void OnSelectDestDir(wxCommandEvent & WXUNUSED(event));
	/**
	 *	预览
	 */
	void OnPreView(wxCommandEvent & WXUNUSED(event));
	/**
	 *	开始处理
	 */
	void OnBegin(wxCommandEvent & WXUNUSED(event));
	/**
	 *	预览和处理的实现函数
	 */
	void Do(bool isExecute);
private:
	DECLARE_EVENT_TABLE()
	wxTextCtrl *_textSourceDir;
	wxTextCtrl *_textDestDir;
	wxTextCtrl *_textInfo;
	wxCheckBox *_traverserCheckBox;
};

enum
{
	Quit = wxID_EXIT,
	About = wxID_ABORT
};

#endif