#pragma once

#ifdef IS_IvgIODll
#define IvgIODll_Exp             __declspec( dllexport )
#else
#define IvgIODll_Exp             __declspec( dllimport )
#endif


// =============================================================================
//
// 【类    名】:CIvgFile
// 【功    能】:对Ivg文件的读写操作

// 【适用范围】:
// 【注意事项】:
//
// 【设    计】:潘隽永
// 【建立时间】:2010年11月30日 
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

//创建CIvgFile对象，并返回指向对象的指针
extern "C" CIvgFile * ClassCreate_CIvgFile();

//释放CIvgFile对象，并将指针清零
extern "C" void ClassRelease_CIvgFile(CIvgFile* &pIvgFile);