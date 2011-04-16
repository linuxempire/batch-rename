#ifndef MY_FRAME_H
#define MY_FRAME_H
#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
	MyFrame();

	/**
	 *	�˳�
	 */
	void OnQuit(wxCommandEvent& event);
	/**
	 *	���ڶԻ���
	 */
	void OnAbout(wxCommandEvent& event);
	/**
	 *	ѡ��Դ·��
	 */
	void OnSelectSourceDir(wxCommandEvent & WXUNUSED(event));
	/**
	 *	ѡ��Դ·��
	 */
	void OnSelectDestDir(wxCommandEvent & WXUNUSED(event));
	/**
	 *	Ԥ��
	 */
	void OnPreView(wxCommandEvent & WXUNUSED(event));
	/**
	 *	��ʼ����
	 */
	void OnBegin(wxCommandEvent & WXUNUSED(event));
	/**
	 *	Ԥ���ʹ����ʵ�ֺ���
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