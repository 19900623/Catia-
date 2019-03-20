// InstallToV5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <afx.h>
#include <Windows.h>
#include <shlobj.h>
#include<ShellAPI.h>
using namespace std;
CString FindPath_Catia(CString strSubKey,CString ReValueName)
{
	HKEY ReRootKey=HKEY_LOCAL_MACHINE; 
	HKEY hKey; 
	char content[256]; 
	sprintf(content,"");
	long lRet=RegOpenKeyEx(ReRootKey,strSubKey,0,KEY_WOW64_64KEY | KEY_READ ,&hKey);
	if(lRet==ERROR_SUCCESS)
	{
		DWORD dwtype;
		DWORD dwSize=256;
		RegQueryValueEx(hKey,ReValueName,0,&dwtype,(unsigned char *)content,&(dwSize));		
	}
	RegCloseKey(hKey);
	return content;
}

CString GetCatiaSubKeyString(CString strCatiaVersion)
{
	CString strResult=_T("SOFTWARE\\Dassault Systemes");
	CString strVersion=strCatiaVersion.Right(2);
	strResult=strResult+_T("\\B")+strVersion+_T("\\0");
	return strResult;
}


CString GetCatiaIntallPath(CString strVersion)
{
	if (strVersion.IsEmpty())
	{
		return "";
	}

	CString strCatiaInstallPath=_T("");      //Catia的安装目录

	//strCatiaInstallPath=ReadSaveValue("CATIA","InstallDir");



	//得到Catia注册表中写有其安装路径的表键
	CString strSubKey=GetCatiaSubKeyString(strVersion);

	//通过Catia注册表找它的安装路径
	strCatiaInstallPath.Format(_T("%s"),FindPath_Catia(strSubKey,"DEST_FOLDER"));

	strCatiaInstallPath+="\\win_b64\\code\\bin";
	return strCatiaInstallPath;
}

CString GetExePath(void)  
{  
	char szFilePath[MAX_PATH + 1]={0};  
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
	(strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串  
	CString path = szFilePath;  
	return path;  
} 

CString GetSelectPath()
{

	CString strpath;

	TCHAR Buffer[MAX_PATH];
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;    //要求返回文件系统的目  

	bi.ulFlags = BIF_NEWDIALOGSTYLE;        //窗口可以调整大小，有新建文件夹按钮  

	bi.pszDisplayName = Buffer;           //此参数如为NULL则不能显示对话框   
	bi.lpszTitle = _T("请选择文件夹");
	bi.lpfn = NULL;


	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框  
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//取得文件夹路径到Buffer里  

		strpath.Format(_T("%s"), Buffer);
	}
	else
	{
		strpath= _T("");  // 用户点了取消  
	}

	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc)))
		strpath = _T("");


	//释放内存  
	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	return strpath;
}


void RemoveFileToOtherPath(CString oldPath,CString newPath)
{
	CFileFind finder;  
	BOOL bWorking = finder.FindFile(oldPath);  
	while (bWorking)  
	{  
		bWorking = finder.FindNextFile(); 
		CString str = finder.GetFilePath();		
		MoveFile(str,newPath);	 
	}   
}

void RunExe(CString exe,CString strSelectPath)
{
	CString cmd="\""+strSelectPath+"\"";
	SHELLEXECUTEINFO si;
	ZeroMemory(&si, sizeof(SHELLEXECUTEINFO));
	si.cbSize = sizeof(SHELLEXECUTEINFO);
	si.fMask = SEE_MASK_NOCLOSEPROCESS;
	si.lpVerb = _T("runas");
	si.lpFile =exe;
	si.lpParameters =cmd;//参数
	si.nShow = SW_SHOWNORMAL;
	if (ShellExecuteEx(&si))//执行成功 
	{
		if (si.hProcess)//指定 SEE_MASK_NOCLOSEPROCESS 并其成功执行，则 hProcess 将会返回执行成功的进程句柄 
			WaitForSingleObject(si.hProcess, INFINITE);//等待执行完毕 
	} 
	else 
	{
		CString s; 
		s.Format(_T("ShellExecuteEx error,error code:%d"), GetLastError()); 
	}
	CloseHandle(si.hProcess); 
}

int _tmain(int argc, _TCHAR* argv[])
{
	//1.获取安装路径
	CString installPath=GetExePath()+"\\";

	//2.获取v5路径
	CString V5Path=GetCatiaIntallPath("v5r19");

	//3.移动exe
	RemoveFileToOtherPath(installPath+"DirToCatalog.exe",V5Path+"\\DirToCatalog.exe");
	RemoveFileToOtherPath(installPath+"CataModule.dll",V5Path+"\\CataModule.dll");

	//4.弹出对话框
	CString selectPath=GetSelectPath();
							  
	//先转ivp，再转catapart
	RunExe(installPath+"lib3dx\\win_b64\\code\\bin\\CADConverter.exe",selectPath);
	RunExe(V5Path+"\\DirToCatalog.exe",selectPath);

	
	return 0;
}

