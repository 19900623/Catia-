// DirToCatalog.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DirToCatalog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL  LibToCatalog(char* cFileName,char* cOutPath);
// 唯一的应用程序对象

CWinApp theApp;

using namespace std;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	if(argc!=2) return 0;
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: 在此处为应用程序的行为编写代码。
	}
    LibToCatalog(argv[1],argv[1]);
	//LibToCatalog("E:\\projects10\\IPDEforCATIA\\InputData\\IPDE_20180926Send","E:\\projects10\\IPDEforCATIA\\InputData\\IPDE_20180926Send");
	return nRetCode;
}
