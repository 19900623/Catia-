#include "stdafx.h"

#include "IvFile.h"
#include "shlwapi.h"

#define FILEBUFFERSIZE 20480   //每次文件压缩的大小为20K左右

CIvFile::CIvFile(void)
{
}

CIvFile::~CIvFile(void)
{
}

//保存XMLDoc中的信息文件到压缩文件中；
//BOOL CIvFile::SaveXMLDocToZipFile(const char *cFileName,CComPtr<IXMLDOMDocument> pDoc)
//{
//	//从XML中读取xml字符串；
//	if(pDoc==NULL)
//		return FALSE;
//	BSTR bstrXml;
//	pDoc->get_xml(&bstrXml);
//
//#ifdef _DEBUG
//	CString strXmlTempFile;
//	strXmlTempFile=cFileName;
//	strXmlTempFile=strXmlTempFile+".xml";
//	pDoc->save(CComVariant(strXmlTempFile));
//#endif
//
//
//	//然后将字符串进行压缩
//	return WriteStringToZipFile(cFileName,bstrXml);	
//}
////将字符串中的内容写到压缩文件中，分段压缩方法
//BOOL CIvFile::WriteStringToZipFile(const char *cFileName,BSTR bstrString)
//{
//
//	FILE *fp ;
//	//fopen( cFileName, "wb" );
//	//FILE* pFile;
//
//	fopen_s(&fp, cFileName, "wb");  //warning 修改 by lc
//
//	if(fp==NULL) 
//	{
//		AfxMessageBox("Create File Error! File Name ：" + CString(cFileName));
//		return FALSE;
//	}
//	fclose(fp);
//
//	USES_CONVERSION;
//	//FILE *fp;
//#ifdef _UNICODE
//	CFile hFile(CA2W(cFileName),CFile::modeCreate|CFile::modeWrite | CFile::typeBinary );
//#else
//	CFile hFile(cFileName,CFile::modeCreate|CFile::modeWrite | CFile::typeBinary );
//#endif
//	if(hFile.m_hFile==NULL)
//		
//	//fopen_s(&fp,cFileName,"w");
//	//if(fp==NULL)
//	{
//		AfxMessageBox(CString("创建文件") +CString(cFileName)+CString("失败！"));
//		return FALSE;
//	}
//	char cFileHead[80];
//	SecureZeroMemory(cFileHead,80);
//	strcpy_s(cFileHead,"inte3d;type=i3d;ver=1.0;");
//	hFile.Write(cFileHead,sizeof(char)*80);
//	//fwrite(cFileHead,sizeof(char),80,fp);
//	//得到字符串的长度
//	CString strBuffer;
//	strBuffer=bstrString;
//
//	uLongf inputLlength;// =(uLongf)_tcslen(CW2A(bstrString));  //输入的字符串长度
//	inputLlength=strBuffer.GetLength();
//
//	char *cInput;
//	cInput= new char[inputLlength+1];
//	strcpy_s(cInput,inputLlength+1,LPCSTR(strBuffer));//warning 修改 by lc
//	//strcpy(cInput,LPCSTR(strBuffer));
//	Bytef cTemp[FILEBUFFERSIZE+1];
//	cTemp[FILEBUFFERSIZE]=0;
//	if(inputLlength>FILEBUFFERSIZE) //大于两万个字符
//	{
//		uLongf i=0;		
//		for(i=0;i<=inputLlength/FILEBUFFERSIZE;i++)
//		{
//			uLongf outputLength;
//			uLongf CurLength=FILEBUFFERSIZE;
//			if((i+1)*FILEBUFFERSIZE>inputLlength)
//			{
//				CurLength=inputLlength-i*FILEBUFFERSIZE;
//			}
//			int iResult;
//			outputLength=FILEBUFFERSIZE;
//
//			iResult=compress((Bytef *)cTemp,&outputLength,(const Bytef*)(cInput+FILEBUFFERSIZE*i),CurLength);
//			if(outputLength<0 || outputLength>FILEBUFFERSIZE)//数据压缩错误!
//			{
//				AfxMessageBox("数据压缩错误！");
//				//fclose(fp);
//				delete cInput;
//				return FALSE;
//			}
//			hFile.Write(&outputLength,sizeof(uLongf));
//			//fwrite(&outputLength,sizeof(uLongf),1,fp); //写入数据的长度
//			//fwrite(cTemp,sizeof(Bytef),outputLength,fp);							
//			hFile.Write(cTemp,sizeof(Bytef)*outputLength);
//		}
//		//AfxMessageBox("超过两万个字符的数据还没有处理过！");
//		//fclose(fp);
//		hFile.Flush();
//		hFile.Close();
//		delete cInput;
//		return TRUE;
//	}
//	else  //少于20000个字符
//	{
//		uLongf outputLength=FILEBUFFERSIZE;
//		
//		inputLlength=inputLlength;
//
//		compress((Bytef *)cTemp,&outputLength,(const Bytef*)CW2A(bstrString).m_psz,inputLlength);
//		if(outputLength<0 || outputLength>FILEBUFFERSIZE)//数据压缩错误!
//		{
//			AfxMessageBox("数据压缩错误！");
//			//fclose(fp);
//			delete cInput;
//		}
//
//		//char cTemp2[FILEBUFFERSIZE+1];
//		//uLongf outputlen2;
//		//int iResult;
//		//iResult=uncompress((Bytef *)cTemp2,&outputlen2,cTemp,outputLength);
//
//		hFile.Write(&outputLength,sizeof(uLongf));
//		//fwrite(&outputLength,sizeof(uLongf),1,fp); //写入数据的长度
//		hFile.Write(cTemp,sizeof(Bytef)*outputLength);
//		//fwrite(cTemp,sizeof(Bytef),outputLength,fp);
//		//fclose(fp);
//		hFile.Flush();
//		hFile.Close();
//		delete cInput;
//		return TRUE;
//	}
//	hFile.Flush();
//		
//	hFile.Close();
//	return TRUE;
//}
//long CIvFile::SaveFile(const char *cFileName,const char *cXmlFile,long lFileSize)
//{
//	return 1;
//}
//读取文件,读取文件将分配内存，然后需要通过FreeMemory释放内存
//long CIvFile::LoadFile(const char *cFileName,char *&cXmlFile,long lFileSize)
//{
//	return 1;
//}

//未发现有其他地方使用，将其注释_liuk
// void CIvFile::FreeMemory(void * pPoint)
// {
// 
// }
//从CFile中读取Xml文件；hInputDoc 可以是CFile，也可以是CMemFile
//CComPtr<IXMLDOMDocument> CIvFile::LoadXmlDocFromCFile(CFile *hInputDoc)
//{
//	if(hInputDoc==NULL || hInputDoc->m_hFile==NULL)
//		return NULL;
//	//文件解压
//	CMemFile hMemFile;
//	if(UnzipFileFromCFile(hInputDoc,hMemFile)<=0)
//		return NULL;
//	//读取内存文件中的所有信息；
//	ULONGLONG lFileLen;
//	hMemFile.SeekToBegin();
//	lFileLen=hMemFile.GetLength(); //若文件太大，我们可能也没有办法了。
//	
//	unsigned int iFileLen = (unsigned int)lFileLen;
//	
//	char *cTemp;
//	cTemp=new char[iFileLen+1];
//	hMemFile.Read(cTemp,iFileLen);
//	if(lFileLen>3)
//	{
//		cTemp[lFileLen]=0;
//		if(cTemp[lFileLen-1]==10 || cTemp[lFileLen-1]==13 )
//			cTemp[lFileLen-1]=0;
//		if(cTemp[lFileLen-2]==10 || cTemp[lFileLen-2]==13 )
//			cTemp[lFileLen-2]=0;
//
//	}
//	CComPtr<IXMLDOMDocument> pXmlDoc;
//	pXmlDoc=LoadXMLFileFromString(cTemp);
//	delete cTemp;  // 释放内存。
//#ifdef _DEBUG
//	if(pXmlDoc)
//	{
//		CString strXmlTempFile;
//		//strXmlTempFile=cFileName;
//		strXmlTempFile=hInputDoc->GetFilePath();
//		strXmlTempFile=strXmlTempFile+".xml";
//		pXmlDoc->save(CComVariant(strXmlTempFile));
//	}
//#endif
//
//	return pXmlDoc;
//
//
//}
////从CFile中读取信息，将文件解压之后放在内存文件中
//long CIvFile::UnzipFileFromCFile(CFile *hInputFile,CMemFile &hMemFile)
//{
//	if(hInputFile==NULL||hInputFile->m_hFile==NULL)
//		return -1; //没有文件被打开；
//	//hInputFile.SeekToBegin(); //重新将文件设置到最开始的地方；
//	//跳过80个用于描述文件头的信息；
//	ULONGLONG  uFilePos;
//	uFilePos=hInputFile->Seek(80,CFile::begin );
//	//依次读取文件并解压将所有的信息写到memfile中
//	Bytef cInput[FILEBUFFERSIZE];
//	Bytef cOutput[FILEBUFFERSIZE+1];
//	while(uFilePos!=CFile::end)
//	{
//		uLongf uZipedLength=0,uOutput,uInput;		
//		hInputFile->Read(&uZipedLength,sizeof(uLongf));
//		if(uZipedLength<=0)
//			break;
//		uInput=hInputFile->Read(cInput,uZipedLength);
//		if(uInput!=uZipedLength) //两个不相等，可能文件出现了错误！
//		{
//			break;
//		}
//		//解压数据
//		uOutput=FILEBUFFERSIZE;
//		int iResult=0;
//		iResult=uncompress(cOutput,&uOutput,cInput,uInput);
//		if(uOutput<=0) //可能出现了问题
//			break;
//		//hMemFile.Attach(cOutput,uOutput); //将信息写入到内存文件中
//		hMemFile.Write(cOutput,uOutput);
//		uFilePos=hInputFile->GetPosition();
//	}
//	
//	
//	return 1;
//}
//读取文件返回xmldoc；
CComPtr<IXMLDOMDocument> CIvFile::LoadXMLFile(const char *cFileName)
{
	CComPtr<IXMLDOMDocument> pXmlDoc;
	pXmlDoc=CreateXmlDoc();
	VARIANT_BOOL vResult;
	pXmlDoc->load(CComVariant(cFileName),&vResult);
	return pXmlDoc;
}
CComPtr<IXMLDOMDocument> CIvFile::LoadXMLFileFromString(const char *cXmlFile)
{
	CComPtr<IXMLDOMDocument> pXmlDoc;
	pXmlDoc=CreateXmlDoc();
	VARIANT_BOOL vResult;
	HRESULT hr;
	hr=pXmlDoc->loadXML(CComBSTR(cXmlFile),&vResult);
	if(hr==S_OK &&	vResult==VARIANT_TRUE)		
		return pXmlDoc;
	return NULL;
}

CComPtr<IXMLDOMDocument> CIvFile::CreateXmlDoc()
{
	CComPtr<IXMLDOMDocument> pDoc;
	HRESULT hr;
	CoInitialize(NULL);
	hr=pDoc.CoCreateInstance(CComBSTR("Msxml2.DOMDocument"));
	if(hr!=S_OK)
		return NULL;
	return pDoc;
}
//在xml文件中增加一个节点	
CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName)
{
	CComPtr<IXMLDOMElement> pElement;
	CComPtr<IXMLDOMNode> pNode;
	pDoc->createElement(CComBSTR(strChildName),&pElement);
	if(pParent==NULL) //父节点为空
	{
		pDoc->appendChild(pElement,&pNode);
	}
	else
	{
		pParent->appendChild(pElement,&pNode);
	}
	return pElement;
}
//设置节点的属性值
void CIvFile::XmlSetAttribute(CComPtr<IXMLDOMElement> pElement,CString strName,CString strValue)
{
	pElement->setAttribute(CComBSTR(strName),CComVariant(strValue));
}

CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,CString strText)
{
	CComPtr<IXMLDOMElement> pElement;
	pElement=XmlAddChild(pDoc,pParent,strChildName);
	pElement->put_text(CComBSTR(strText));
	return pElement;
}
CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,double dText)
{
	HRESULT hr;
	CComPtr<IXMLDOMElement> pElement;
	pElement=XmlAddChild(pDoc,pParent,strChildName);
	CString strTemp;
	strTemp.Format(_T("%f"),dText);
	hr=pElement->put_text(CComBSTR(strTemp));
	return pElement;

}
CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,float dText)
{
	CComPtr<IXMLDOMElement> pElement;
	pElement=XmlAddChild(pDoc,pParent,strChildName);
	CString strTemp;
	strTemp.Format(_T("%f"),dText);
	pElement->put_text(CComBSTR(strTemp));
	return pElement;

}
CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,long lText)
{
	CComPtr<IXMLDOMElement> pElement;
	pElement=XmlAddChild(pDoc,pParent,strChildName);
	CString strTemp;
	strTemp.Format(_T("%d"),lText);
	pElement->put_text(CComBSTR(strTemp));
	return pElement;

}
CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,int iText)
{
	CComPtr<IXMLDOMElement> pElement;
	pElement=XmlAddChild(pDoc,pParent,strChildName);
	CString strTemp;
	strTemp.Format(_T("%d"),iText);
	pElement->put_text(CComBSTR(strTemp));
	return pElement;
}
//比较两个文件完整的路径Path＋fileName，返回两个文件的相对路径
CString CIvFile::GetRelatePath(CString strFrom,CString strTo)
{
	BOOL bResult;
	TCHAR szOut[MAX_PATH] = _T("");
	//PathCanonicalize(szOut,strFrom);
	//strFrom=szOut;
	//PathCanonicalize(szOut,strTo);
	//strTo=szOut;
	strFrom.Replace(_T("\\\\\\"),_T("\\"));
	strFrom.Replace(_T("\\\\"),_T("\\"));
	strTo.Replace(_T("\\\\\\"),_T("\\"));
	strTo.Replace(_T("\\\\"),_T("\\"));
	bResult=PathRelativePathTo(szOut,strFrom,FILE_ATTRIBUTE_NORMAL,strTo,FILE_ATTRIBUTE_NORMAL);
	if(bResult)
		return szOut;
	return "";
}
//根据相对路径得到文件的完整的路径
CString CIvFile::GetPathByRelate(CString strFileName,CString strRelation)
{
	return "";

}

CComPtr<IXMLDOMElement> CIvFile::XmlGetFirstChild(CComPtr<IXMLDOMDocument> pElement)
{
	if(pElement==NULL)
		return NULL;
	CComPtr<IXMLDOMElement> pNode;
	pElement->get_documentElement(&pNode);
	//>get_firstChild(&pNode);
	//CComQIPtr<IXMLDOMElement> pElementTemp;
	//pElementTemp=pNode;

	//if(pElementTemp==NULL) //第一个节点不是element
	//{
	//	while(TRUE)
	//	{
	//		CComPtr<IXMLDOMNode> pNodeNext;
	//		pNode->get_nextSibling(&pNodeNext);
	//		if(pNodeNext==NULL)
	//		{
	//			break;
	//		}
	//		pElementTemp=pNodeNext;
	//		pNode=pNodeNext;
	//		if(pElementTemp!=NULL)
	//		{
	//			break;
	//		}
	//	}
	//}

	return pNode;
}

CComPtr<IXMLDOMElement> CIvFile::XmlGetFirstChild(CComPtr<IXMLDOMElement> pElement)
{
	CComPtr<IXMLDOMNode> pNode;
	pElement->get_firstChild(&pNode);
	CComQIPtr<IXMLDOMElement> pElementTemp;
	pElementTemp=pNode;
	return pElementTemp;
}
CComPtr<IXMLDOMElement> CIvFile::XmlGetNextNode(CComPtr<IXMLDOMElement> pElement)
{
	CComPtr<IXMLDOMNode> pNode;
	pElement->get_nextSibling(&pNode);
	CComQIPtr<IXMLDOMElement> pElementTemp;
	pElementTemp=pNode;
	return pElementTemp;
}

CString CIvFile::XmlGetElementName(CComPtr<IXMLDOMElement> pElement)
{
	BSTR bstrName;
	HRESULT rs;
	rs=pElement->get_nodeName(&bstrName);
	CString strTemp;
	if(rs==S_OK)
	{
		strTemp=bstrName;
	}
	else
	{
		strTemp=_T("");
	}
	return strTemp;
}
CString CIvFile::XmlGetElementText(CComPtr<IXMLDOMElement> pElement)
{
	BSTR bstrName;
	pElement->get_text(&bstrName);
	CString strTemp;
	strTemp=bstrName;
	return strTemp;
}
CString CIvFile::XmlGetElementAttribute(CComPtr<IXMLDOMElement> pElement,CString strName)
{
	CComVariant vValue;
	pElement->getAttribute(CComBSTR(strName),&vValue);
	CString strTemp;
	if(vValue.vt==VT_BSTR)
	{
		strTemp=vValue.bstrVal;
		return strTemp;
	}
	return "";
}

BOOL CIvFile::IsNewAsmFile(CString strFileName)
{
	////需要先打开文件，然后读取文件
	// CString strExt;
	////读取前面80个字符，
	// FILE *fp=NULL;
	// fopen_s(&fp,strFileName,"r");
	// if(fp==NULL)
	//	 return FALSE;
	// char cHead[81];
	// fread(cHead,sizeof(char),80,fp);
	// CString strHead;
	// strHead=cHead;
	// if(strHead.Find("InteVue;type=iva;ver=")>=0)
	//	 return TRUE;
	return FALSE;
}