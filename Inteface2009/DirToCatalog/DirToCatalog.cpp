// DirToCatalog.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "DirToCatalog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL  LibToCatalog(char* cFileName,char* cOutPath);
// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	if(argc!=2) return 0;
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	}
    LibToCatalog(argv[1],argv[1]);
	//LibToCatalog("E:\\projects10\\IPDEforCATIA\\InputData\\IPDE_20180926Send","E:\\projects10\\IPDEforCATIA\\InputData\\IPDE_20180926Send");
	return nRetCode;
}
