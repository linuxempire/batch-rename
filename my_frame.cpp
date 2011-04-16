#include "my_frame.h"
#include <wx/dir.h>
#include <wx/filename.h>
#include "chinese_to_pinyin.h"
#include "common.h"

/**
	注册事件
*/
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(Quit, MyFrame::OnQuit)
EVT_MENU(About, MyFrame::OnAbout)
END_EVENT_TABLE()

/**
	组件枚举
*/
const int ID_ST_LABLE1 = 101;
const int ID_ST_LABLE2 = 102;
const int ID_CB__TRAVERSER = 103;
const int ID_BTN_SOURCE_SELECT = 111;
const int ID_BTN_DEST_SELECT = 112;
const int ID_BTN_BEGIN = 113;
const int ID_BTN_PREVIEW = 114;

const int ID_TEXT_SOURCE_DIR = 124;
const int ID_TEXT_DEST_DIR = 125;
const int ID_TEXT_INFO = 126;

MyFrame::MyFrame()
:wxFrame(NULL, wxID_ANY, wxT("批量重命名"), wxPoint(50, 50),
		 wxSize(800, 600))
{
	SetIcon(wxIcon(wxT("web.xpm")));
#if wxUSE_MENUS
	wxMenu *fileMenu = new wxMenu;
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(About, _T("关于(&A)...\tF1"), _T("关于"));
	fileMenu->Append(Quit, _T("退出(&X)\tAlt-X"), _T("退出"));

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, _T("文件(&F)"));
	menuBar->Append(helpMenu, _T("关于(&H)"));

	SetMenuBar(menuBar);
#endif
#if wxUSE_STATUSBAR
	CreateStatusBar(2);
	SetStatusText(_T("欢迎使用"));
#endif

	wxPanel* mainPane = new wxPanel(this);  
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mainPane->SetSizer(sizer);

	/**
	 * 源路径
	 */
	new wxStaticText(mainPane, ID_ST_LABLE1, wxString("  源路径："), 
		wxPoint(20, 20), wxSize(60,25));
	_textSourceDir = new wxTextCtrl(mainPane, ID_TEXT_SOURCE_DIR, wxGetCwd(), 
		wxPoint(80, 20), wxSize(500,25),  
    wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
	wxButton *selectButton = new wxButton(mainPane, ID_BTN_SOURCE_SELECT, wxT("..."), 
      wxPoint(580, 20), wxSize(21,25));
	Connect(ID_BTN_SOURCE_SELECT, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(MyFrame::OnSelectSourceDir));
	selectButton->SetFocus();

	/**
	 * 是否包含子目录
	 */
	_traverserCheckBox = new wxCheckBox(mainPane, ID_CB__TRAVERSER, wxString("包含子目录"),
		wxPoint(630, 20)); 

	/**
	 * 目标路径
	 */
	new wxStaticText(mainPane, ID_ST_LABLE2, wxString("目标路径："), 
		wxPoint(20, 50), wxSize(60,25));
	_textDestDir = new wxTextCtrl(mainPane, ID_TEXT_DEST_DIR, wxGetCwd(), 
		wxPoint(80, 50), wxSize(500,25),  
		wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
	new wxButton(mainPane, ID_BTN_DEST_SELECT, wxT("..."), 
		wxPoint(580, 50), wxSize(21,25));
	Connect(ID_BTN_DEST_SELECT, wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(MyFrame::OnSelectDestDir));

	/**
	 * 预览
	 */
	wxButton *previewButton = new wxButton(mainPane, ID_BTN_PREVIEW, wxT("预览"), 
      wxPoint(630, 50), wxSize(40,23));
	Connect(ID_BTN_PREVIEW, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(MyFrame::OnPreView));

	/**
	 * 开始
	 */
	wxButton *beginButton = new wxButton(mainPane, ID_BTN_BEGIN, wxT("开始"), 
      wxPoint(700, 50), wxSize(40,23));
	Connect(ID_BTN_BEGIN, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(MyFrame::OnBegin));

	/**
	 * 信息显示
	 */
	_textInfo = new wxTextCtrl(mainPane, ID_TEXT_INFO, "", wxPoint(20, 100), wxSize(740,400),  
    wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
}

void MyFrame::OnSelectSourceDir(wxCommandEvent & WXUNUSED(event))
{
    wxString selection = wxDirSelector("选择一个文件夹", wxGetCwd());
	if ( ! selection.empty() )
	{
	   _textSourceDir->Clear();
	   _textDestDir->Clear();
	   _textSourceDir->WriteText(selection);
	   _textDestDir->WriteText(selection);
	}
}

void MyFrame::OnSelectDestDir(wxCommandEvent & WXUNUSED(event))
{
	wxString selection = wxDirSelector("选择一个文件夹", wxGetCwd());
	if ( ! selection.empty() )
	{
		_textDestDir->Clear();
		_textDestDir->WriteText(selection);
	}
}

void MyFrame::OnPreView(wxCommandEvent & WXUNUSED(event))
{	
	Do(false);
}

void MyFrame::OnBegin(wxCommandEvent & WXUNUSED(event))
{	
	Do(true);
}

void MyFrame::Do(bool isExecute)
{
	if(_traverserCheckBox->GetValue())
		wxMessageBox(wxString("6666666666"));
	wxString dirStr = _textSourceDir->GetValue();
	if(!dirStr.empty())
	{
		_textInfo->Clear();
		wxFileName dirFileName(dirStr);
		dirFileName.Normalize(wxPATH_NORM_ABSOLUTE);
		wxDir dir(dirStr);
		if(!dir.IsOpened())
		{
			return;
		}
		wxString filename;
		wxString filespec = wxT("*.*");
		int flags = wxDIR_FILES;
		bool cont = dir.GetFirst(&filename, filespec, flags);
		while(cont)
		{
			wxString newFileName = wxString(strlwr((char*)getLetter(filename.c_str()).c_str()));
			if(isExecute && filename!=newFileName)
			{
				wxRenameFile(dirFileName.GetFullPath()+wxFILE_SEP_PATH+filename, dirFileName.GetFullPath()+wxFILE_SEP_PATH+newFileName);
			}
			_textInfo->AppendText(wxString::Format(_T("%s\t-\t%s\n"), filename.c_str(), newFileName.c_str()));
			cont = dir.GetNext(&filename);
		}
	}
	else
	{
		wxMessageBox(wxString("请选择路径"),
		_T("About wxWidgets minimal sample"),
		wxOK | wxICON_ERROR,
		this);
	}
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxString::Format(
		_T("Batch Rename\n\n")
		_T("Version:\t%s\n")
		_T("Author:\tNile.Li\n")
		_T("Use:\t%s\n")
		_T("OS:\t%s.\n")
		_T("License:\tGPLv3"),
		BATCH_RENAME_VERSION,
		wxVERSION_STRING,
		wxGetOsDescription().c_str()
		),
		_T("About..."),
		wxOK | wxICON_INFORMATION,
		this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
	Close(true);
}