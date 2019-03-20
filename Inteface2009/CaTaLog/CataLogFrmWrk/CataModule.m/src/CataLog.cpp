#include "CataLog.h"
#include "stdafx.h"
#include "CATUnicodeString.h"
#include "CATICatalogChapter.h"
#include "CAACciCatalogDocumentServices.h"
#include "CATICatalogChapterFactory.h"
#include "CAACciToolCatalogCreation.h"
#include "CATLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include "shlwapi.h"
#pragma comment (lib,"shlwapi.lib")
using namespace std;


const char* CString2Char(CString str)
{
	// �ȵõ�Ҫת��Ϊ�ַ��ĳ���
	const size_t strsize=(str.GetLength()+1)*2; // ���ַ��ĳ���;
	char * pstr= new char[strsize]; //����ռ�;
	size_t sz=0;
	wcstombs_s(&sz,pstr,strsize,str,_TRUNCATE);
	return pstr;

}

//cLibPath:��Ҫ�����Ŀ��ļ����ڵ�·��
//cOutfile:������ļ����ڵ�λ�ü��ļ���
BOOL  LibToCatalog(char* cLibPath,char* cOutFile)
{
	//ת����V5�����л���
	string file="C:\\ProgramData\\DassaultSystemes\\CATEnv\\CATIA.V5R19.B19.txt";
	ifstream infile; 
	infile.open(file.data());   //���ļ����������ļ��������� 
	if(infile.is_open())
	{

	string s;
	while(getline(infile,s))
	{
		if(s.find('=')!=-1)
		 CATLibStatus rs=CATPutEnv(s.c_str());
	}
	infile.close();             //�ر��ļ������� 
	}

 






	CString strLibPath=cLibPath;
	CString strFullPath=cOutFile;
	CString strOutPath;
	CString strOutFile;
	
	strOutFile=PathFindFileName(strFullPath);
	strOutPath=cOutFile;
	strOutPath=strOutPath.Left(strOutPath.GetLength()-strOutFile.GetLength());


	CATUnicodeString libpath;
	libpath.BuildFromWChar(strLibPath.AllocSysString());

	CATUnicodeString outpath;
	outpath.BuildFromWChar(strOutPath.AllocSysString());

	CATUnicodeString outfile;
	outfile.BuildFromWChar(strOutFile.AllocSysString());



	HRESULT bRet=PathToCatalog(libpath,outpath,outfile);//���·�������·��������ļ������޺�׺��

	//����CAADLCInputV5Documents.txt�ļ���������������
	strOutPath+="CAADLCInputV5Documents.txt";
	strOutFile="\\"+strOutFile+".catalog";
	FILE*fp=NULL;
	fp=fopen(CString2Char(strOutPath),"w"); 
	if(NULL==fp) return FALSE;
	fputs(CString2Char(strOutFile),fp);
	fclose(fp);
	fp=NULL;
	if(bRet==S_OK)
		return TRUE;
	else
		return FALSE;
}