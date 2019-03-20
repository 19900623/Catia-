// InstallToV5.cpp : �������̨Ӧ�ó������ڵ㡣
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

	CString strCatiaInstallPath=_T("");      //Catia�İ�װĿ¼

	//strCatiaInstallPath=ReadSaveValue("CATIA","InstallDir");



	//�õ�Catiaע�����д���䰲װ·���ı��
	CString strSubKey=GetCatiaSubKeyString(strVersion);

	//ͨ��Catiaע��������İ�װ·��
	strCatiaInstallPath.Format(_T("%s"),FindPath_Catia(strSubKey,"DEST_FOLDER"));

	strCatiaInstallPath+="\\win_b64\\code\\bin";
	return strCatiaInstallPath;
}

CString GetExePath(void)  
{  
	char szFilePath[MAX_PATH + 1]={0};  
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
	(strrchr(szFilePath, '\\'))[0] = 0; // ɾ���ļ�����ֻ���·���ִ�  
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
	bi.ulFlags = BIF_RETURNONLYFSDIRS;    //Ҫ�󷵻��ļ�ϵͳ��Ŀ  

	bi.ulFlags = BIF_NEWDIALOGSTYLE;        //���ڿ��Ե�����С�����½��ļ��а�ť  

	bi.pszDisplayName = Buffer;           //�˲�����ΪNULL������ʾ�Ի���   
	bi.lpszTitle = _T("��ѡ���ļ���");
	bi.lpfn = NULL;


	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���  
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//ȡ���ļ���·����Buffer��  

		strpath.Format(_T("%s"), Buffer);
	}
	else
	{
		strpath= _T("");  // �û�����ȡ��  
	}

	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc)))
		strpath = _T("");


	//�ͷ��ڴ�  
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
	si.lpParameters =cmd;//����
	si.nShow = SW_SHOWNORMAL;
	if (ShellExecuteEx(&si))//ִ�гɹ� 
	{
		if (si.hProcess)//ָ�� SEE_MASK_NOCLOSEPROCESS ����ɹ�ִ�У��� hProcess ���᷵��ִ�гɹ��Ľ��̾�� 
			WaitForSingleObject(si.hProcess, INFINITE);//�ȴ�ִ����� 
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
	//1.��ȡ��װ·��
	CString installPath=GetExePath()+"\\";

	//2.��ȡv5·��
	CString V5Path=GetCatiaIntallPath("v5r19");

	//3.�ƶ�exe
	RemoveFileToOtherPath(installPath+"DirToCatalog.exe",V5Path+"\\DirToCatalog.exe");
	RemoveFileToOtherPath(installPath+"CataModule.dll",V5Path+"\\CataModule.dll");

	//4.�����Ի���
	CString selectPath=GetSelectPath();
							  
	//��תivp����תcatapart
	RunExe(installPath+"lib3dx\\win_b64\\code\\bin\\CADConverter.exe",selectPath);
	RunExe(V5Path+"\\DirToCatalog.exe",selectPath);

	
	return 0;
}

