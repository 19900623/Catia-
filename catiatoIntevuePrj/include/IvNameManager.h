// IvNameManager.h: interface for the CIvNameManager class.
/************************************************************

  ��Ȩ���� (C),  �人��������������ι�˾.
  �ļ���:       IvNameManager.h
  ����:         ��С��
  �������:     2004.3.4
  ����:         ���ֹ�����
  �汾:         1.0
**************************************************************/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVNAMEMANAGER_H__C951069A_D814_49AB_9341_2FB668D1233D__INCLUDED_)
#define AFX_IVNAMEMANAGER_H__C951069A_D814_49AB_9341_2FB668D1233D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxtempl.h"
#include "ivconverterhead.h"

class IVCONVERTER_EXPORTS CIvNameManager  
{
public:
	CIvNameManager();
	virtual ~CIvNameManager();

	typedef enum{ Append, Share, Unique } NameOption;

	void  AppendCount(int nameCount);                             ///���Ӵ洢�ռ�
	char* AddName(const char* name, NameOption option = Append);  ///�����������
	char* FindNamePtr(const char* name);                          ///��������
	void  UndoLast();                                             ///�������һ�����
	void  Optimize();                                             ///�ڴ��Ż�

protected:
	long m_nameCount;             
	long m_logicalSize;           ///�ڴ��߼���С
	long m_lastSize;              ///���һ�β���ǰ���߼���С
	CArray<char, char> m_array;   ///��������
};

#endif // !defined(AFX_IVNAMEMANAGER_H__C951069A_D814_49AB_9341_2FB668D1233D__INCLUDED_)
