// IvNameManager.h: interface for the CIvNameManager class.
/************************************************************

  版权所有 (C),  武汉天喻软件有限责任公司.
  文件名:       IvNameManager.h
  作者:         王小刚
  完成日期:     2004.3.4
  描述:         名字管理类
  版本:         1.0
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

	void  AppendCount(int nameCount);                             ///增加存储空间
	char* AddName(const char* name, NameOption option = Append);  ///添加名字内容
	char* FindNamePtr(const char* name);                          ///查找名字
	void  UndoLast();                                             ///撤销最后一次添加
	void  Optimize();                                             ///内存优化

protected:
	long m_nameCount;             
	long m_logicalSize;           ///内存逻辑大小
	long m_lastSize;              ///最后一次操作前的逻辑大小
	CArray<char, char> m_array;   ///数据数组
};

#endif // !defined(AFX_IVNAMEMANAGER_H__C951069A_D814_49AB_9341_2FB668D1233D__INCLUDED_)
