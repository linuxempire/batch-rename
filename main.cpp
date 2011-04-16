//#include <iostream>
//#include "file.h"
//#include "chinese_to_pinyin.h"

/*#include <wx/wx.h>
#include "my_app.h"

using namespace std;

int main1(int argc, char* argv[])
{
    copyFile("1.txt", "2.txt");
    int     result;
    char*   oldFile   =   "2.txt";
    char*   newFile   =   "3.txt";
    result   =   rename(   oldFile,   newFile   );
    if(   result   !=   0   )
        printf(   "Could   not   rename   '%s '\n ",   oldFile   );
    else
        printf(   "File   '%s '   renamed   to   '%s '\n ",   oldFile,   newFile   );

    int count;
    char** r = enumFiles("宠物技能图标", &count);
    for(int i=0; i< count; i++)
    {
        printf("%s - %s\n", r[i], getLetter(r[i]).c_str());
    }
    return 0;

	MyApp* app = new MyApp();
	wxApp::SetInstance(app);

	return wxEntry(argc, argv);
}

#include <wx/wx.h>
#include "common.h"

#ifdef WINDOWS
#   include <Windows.h>
#endif

#include "my_app.h"

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) 
{
	MyApp* app=new MyApp();
	wxApp::SetInstance(app);

	return wxEntry(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
}
#else
int main(int argc,char* argv[])
{
	MyApp* app=new MyApp();
	wxApp::SetInstance(app);

	return wxEntry(argc,argv);
}
#endif*/