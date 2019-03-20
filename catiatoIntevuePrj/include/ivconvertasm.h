// IvConvertAsm.h: interface for the CIvConvertAsm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVCONVERTASM_H__0FCFFA08_ADC4_4F92_83E3_2AC03ED349C1__INCLUDED_)
#define AFX_IVCONVERTASM_H__0FCFFA08_ADC4_4F92_83E3_2AC03ED349C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#define IvConv_Class __declspec(dllexport)
#include "IvNameManager.h"





class IVCONVERTER_EXPORTS CIvConvertAsm
{
public:
	CIvConvertAsm();
	virtual ~CIvConvertAsm();
	//设置装配体的文件名称，后一参数为在装配体上的显示名称
	void SetFile(const char *filename,const char *cDisplayName);
	void SetFile(const char *filename,const char *cDisplayName,const char *cActiveConfig);
	void WritePropSet(const char *cPropSetName,const char *cPropSetDisplayName,CStringList &title, CStringList &titleDispaly,CStringList &value); //这个函数用于 vc2005下进行调用
	void WritePropSet(const char *cPropSetName,const char *cPropSetDisplayName,const char *cPropName,const char *cTitle,const char *cValue);   //这个函数用于在其它编译环境中的动态库使用，如catia等；
	//void WriteNode(int type, long state, BOOL bFixed, const char* name,	const char* filename,
	//	int childCount, double *rotation, double *translation, double *color);
	void WriteChild(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL );
	//在这个函数中增加了occ的永久handle;
	void WriteChild_V2(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,const char *cHandle=NULL);
	//写入柔性体信息，主要是针对hoops中的柔性体，（在装配模型中修改了子节点变换矩阵）
	void WriteFlexChild_V2(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		const char *cFlexChildlst,const char *cFlexChildMatrix,const char *cHandle=NULL);

	//配置模型用装配实例函数
	void WriteConfigChild(const char *cAsmConfig,const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL );
	void WriteConfigChild_V2(const char *cAsmConfig,const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,const char *CHandle=NULL);


	//写入变型子节点
	void WriteDeformChild(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,	
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,
		BOOL bDeformed=FALSE,
		const char *cDeformNames=NULL,const char *cDeformFiles=NULL);

	void WriteDeformChild_V2(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,	
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,
		BOOL bDeformed=FALSE,
		const char *cDeformNames=NULL,const char *cDeformFiles=NULL,const char *cHandle=NULL);


	//在装配体下写入零件
	void WritePartInAsm(const char *cDisplayName,const char *cPartFile);


	void WriteAsmRootInfo();


	//写入变型子节点，每个子节点带有变换矩阵，与WriteDeformChild不同在于这里
	void WriteDeformChildWithMatrix(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,	
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,
		BOOL bDeformed=FALSE,
		const char *cDeformNames=NULL,const char *cDeformFiles=NULL,
		const char *cDeformMatrix=NULL);


public:
	//有约束元素反向
	//不要
	//void WriteConstraint(long lType,BOOL bFlage,double dValue,
	//	long lE1Type,long lE1ID,char *cE1Path,long lE2Type,long lE2ID,char *cE2Path,BOOL bReversed1,BOOL bReversed2);
	////不要
	//void WriteConstraint(long lType,BOOL bFlage,double dValue,
	//	long lE1Type,long lE1ID,char *cE1Path,long lE2Type,long lE2ID,char *cE2Path);
	//void SetFile(FILE *fp);
	//
	//void WriteVersion(int ver);
	//void WriteInfo(int type,char *cBuffer,int iLength);
	//void WriteNode(int type, long state, BOOL bFixed, const char* name,	const char* filename,
	//	int childCount, double *rotation, double *translation, double *color,char *outputname);
	
	//void WriteExplosionTransform(const char* name,const char *ExplosionName, double *rotation, double *translation);
protected:
	//FILE*		m_pFile; //这个参数最后要去掉
	//int			m_size; //这个参数最后也要去掉
	CIvNameManager m_nameMgr;
	char m_cFileName[1000]; //文件名称；
};

#endif // !defined(AFX_IVCONVERTASM_H__0FCFFA08_ADC4_4F92_83E3_2AC03ED349C1__INCLUDED_)
