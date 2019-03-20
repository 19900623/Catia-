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
	//����װ������ļ����ƣ���һ����Ϊ��װ�����ϵ���ʾ����
	void SetFile(const char *filename,const char *cDisplayName);
	void SetFile(const char *filename,const char *cDisplayName,const char *cActiveConfig);
	void WritePropSet(const char *cPropSetName,const char *cPropSetDisplayName,CStringList &title, CStringList &titleDispaly,CStringList &value); //����������� vc2005�½��е���
	void WritePropSet(const char *cPropSetName,const char *cPropSetDisplayName,const char *cPropName,const char *cTitle,const char *cValue);   //��������������������뻷���еĶ�̬��ʹ�ã���catia�ȣ�
	//void WriteNode(int type, long state, BOOL bFixed, const char* name,	const char* filename,
	//	int childCount, double *rotation, double *translation, double *color);
	void WriteChild(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL );
	//�����������������occ������handle;
	void WriteChild_V2(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,const char *cHandle=NULL);
	//д����������Ϣ����Ҫ�����hoops�е������壬����װ��ģ�����޸����ӽڵ�任����
	void WriteFlexChild_V2(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		const char *cFlexChildlst,const char *cFlexChildMatrix,const char *cHandle=NULL);

	//����ģ����װ��ʵ������
	void WriteConfigChild(const char *cAsmConfig,const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL );
	void WriteConfigChild_V2(const char *cAsmConfig,const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,const char *CHandle=NULL);


	//д������ӽڵ�
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


	//��װ������д�����
	void WritePartInAsm(const char *cDisplayName,const char *cPartFile);


	void WriteAsmRootInfo();


	//д������ӽڵ㣬ÿ���ӽڵ���б任������WriteDeformChild��ͬ��������
	void WriteDeformChildWithMatrix(const char *cType,const char *cDisplayName,
		const char *cFullName,const char *cParentFullName,long state,BOOL bFixed,
		double *dMatrix,double *color,	
		BOOL bConfiged=FALSE ,const char *cConfigName=NULL,
		BOOL bDeformed=FALSE,
		const char *cDeformNames=NULL,const char *cDeformFiles=NULL,
		const char *cDeformMatrix=NULL);


public:
	//��Լ��Ԫ�ط���
	//��Ҫ
	//void WriteConstraint(long lType,BOOL bFlage,double dValue,
	//	long lE1Type,long lE1ID,char *cE1Path,long lE2Type,long lE2ID,char *cE2Path,BOOL bReversed1,BOOL bReversed2);
	////��Ҫ
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
	//FILE*		m_pFile; //����������Ҫȥ��
	//int			m_size; //����������ҲҪȥ��
	CIvNameManager m_nameMgr;
	char m_cFileName[1000]; //�ļ����ƣ�
};

#endif // !defined(AFX_IVCONVERTASM_H__0FCFFA08_ADC4_4F92_83E3_2AC03ED349C1__INCLUDED_)
