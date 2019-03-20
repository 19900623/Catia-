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
	// 先得到要转换为字符的长度
	const size_t strsize=(str.GetLength()+1)*2; // 宽字符的长度;
	char * pstr= new char[strsize]; //分配空间;
	size_t sz=0;
	wcstombs_s(&sz,pstr,strsize,str,_TRUNCATE);
	return pstr;

}

//cLibPath:需要遍历的库文件所在的路径
//cOutfile:输出的文件所在的位置及文件名
BOOL  LibToCatalog(char* cLibPath,char* cOutFile)
{
	//转换到V5的运行环境
	string file="C:\\ProgramData\\DassaultSystemes\\CATEnv\\CATIA.V5R19.B19.txt";
	ifstream infile; 
	infile.open(file.data());   //将文件流对象与文件连接起来 
	if(infile.is_open())
	{

	string s;
	while(getline(infile,s))
	{
		if(s.find('=')!=-1)
		 CATLibStatus rs=CATPutEnv(s.c_str());
	}
	infile.close();             //关闭文件输入流 
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



	HRESULT bRet=PathToCatalog(libpath,outpath,outfile);//零件路径，输出路径，输出文件名（无后缀）

	//生成CAADLCInputV5Documents.txt文件，用于批量导入
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