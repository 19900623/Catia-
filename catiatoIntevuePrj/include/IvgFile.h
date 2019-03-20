#pragma once

#ifdef IS_IvgIODll
#define IvgIODll_Exp             __declspec( dllexport )
#else
#define IvgIODll_Exp             __declspec( dllimport )
#endif


// =============================================================================
//
// ����    ����:CIvgFile
// ����    �ܡ�:��Ivg�ļ��Ķ�д����

// �����÷�Χ��:
// ��ע�����:
//
// ����    �ơ�:������
// ������ʱ�䡿:2010��11��30�� 
//
// ============================================================================

class IvgIODll_Exp CIvgFile
{
public:
	virtual bool MWriteFileA(LPCSTR cFileName, LPCSTR cRealFileName=NULL, LPCSTR cSystem=NULL,LPCSTR version=NULL)=0;
	virtual bool MWriteFileAttributeA(LPCSTR AttributeName,LPCSTR AttributeValue)=0;
	virtual bool MWritePageAttributeA(LPCSTR cPageName,LPCSTR AttributeName,LPCSTR AttributeValue)=0; 
	//virtual bool MwritePageA(LPCSTR cPageFileName, const int iPageCount,const int iPageNumber)=0;
	virtual bool saveIvgFile()=0;

};

//����CIvgFile���󣬲�����ָ������ָ��
extern "C" CIvgFile * ClassCreate_CIvgFile();

//�ͷ�CIvgFile���󣬲���ָ������
extern "C" void ClassRelease_CIvgFile(CIvgFile* &pIvgFile);