#include "stdafx.h"

#include "IvFile.h"
#include "shlwapi.h"

#define FILEBUFFERSIZE 20480   //ÿ���ļ�ѹ���Ĵ�СΪ20K����

CIvFile::CIvFile(void)
{
}

CIvFile::~CIvFile(void)
{
}

//����XMLDoc�е���Ϣ�ļ���ѹ���ļ��У�
//BOOL CIvFile::SaveXMLDocToZipFile(const char *cFileName,CComPtr<IXMLDOMDocument> pDoc)
//{
//	//��XML�ж�ȡxml�ַ�����
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
//	//Ȼ���ַ�������ѹ��
//	return WriteStringToZipFile(cFileName,bstrXml);	
//}
////���ַ����е�����д��ѹ���ļ��У��ֶ�ѹ������
//BOOL CIvFile::WriteStringToZipFile(const char *cFileName,BSTR bstrString)
//{
//
//	FILE *fp ;
//	//fopen( cFileName, "wb" );
//	//FILE* pFile;
//
//	fopen_s(&fp, cFileName, "wb");  //warning �޸� by lc
//
//	if(fp==NULL) 
//	{
//		AfxMessageBox("Create File Error! File Name ��" + CString(cFileName));
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
//		AfxMessageBox(CString("�����ļ�") +CString(cFileName)+CString("ʧ�ܣ�"));
//		return FALSE;
//	}
//	char cFileHead[80];
//	SecureZeroMemory(cFileHead,80);
//	strcpy_s(cFileHead,"inte3d;type=i3d;ver=1.0;");
//	hFile.Write(cFileHead,sizeof(char)*80);
//	//fwrite(cFileHead,sizeof(char),80,fp);
//	//�õ��ַ����ĳ���
//	CString strBuffer;
//	strBuffer=bstrString;
//
//	uLongf inputLlength;// =(uLongf)_tcslen(CW2A(bstrString));  //������ַ�������
//	inputLlength=strBuffer.GetLength();
//
//	char *cInput;
//	cInput= new char[inputLlength+1];
//	strcpy_s(cInput,inputLlength+1,LPCSTR(strBuffer));//warning �޸� by lc
//	//strcpy(cInput,LPCSTR(strBuffer));
//	Bytef cTemp[FILEBUFFERSIZE+1];
//	cTemp[FILEBUFFERSIZE]=0;
//	if(inputLlength>FILEBUFFERSIZE) //����������ַ�
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
//			if(outputLength<0 || outputLength>FILEBUFFERSIZE)//����ѹ������!
//			{
//				AfxMessageBox("����ѹ������");
//				//fclose(fp);
//				delete cInput;
//				return FALSE;
//			}
//			hFile.Write(&outputLength,sizeof(uLongf));
//			//fwrite(&outputLength,sizeof(uLongf),1,fp); //д�����ݵĳ���
//			//fwrite(cTemp,sizeof(Bytef),outputLength,fp);							
//			hFile.Write(cTemp,sizeof(Bytef)*outputLength);
//		}
//		//AfxMessageBox("����������ַ������ݻ�û�д������");
//		//fclose(fp);
//		hFile.Flush();
//		hFile.Close();
//		delete cInput;
//		return TRUE;
//	}
//	else  //����20000���ַ�
//	{
//		uLongf outputLength=FILEBUFFERSIZE;
//		
//		inputLlength=inputLlength;
//
//		compress((Bytef *)cTemp,&outputLength,(const Bytef*)CW2A(bstrString).m_psz,inputLlength);
//		if(outputLength<0 || outputLength>FILEBUFFERSIZE)//����ѹ������!
//		{
//			AfxMessageBox("����ѹ������");
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
//		//fwrite(&outputLength,sizeof(uLongf),1,fp); //д�����ݵĳ���
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
//��ȡ�ļ�,��ȡ�ļ��������ڴ棬Ȼ����Ҫͨ��FreeMemory�ͷ��ڴ�
//long CIvFile::LoadFile(const char *cFileName,char *&cXmlFile,long lFileSize)
//{
//	return 1;
//}

//δ�����������ط�ʹ�ã�����ע��_liuk
// void CIvFile::FreeMemory(void * pPoint)
// {
// 
// }
//��CFile�ж�ȡXml�ļ���hInputDoc ������CFile��Ҳ������CMemFile
//CComPtr<IXMLDOMDocument> CIvFile::LoadXmlDocFromCFile(CFile *hInputDoc)
//{
//	if(hInputDoc==NULL || hInputDoc->m_hFile==NULL)
//		return NULL;
//	//�ļ���ѹ
//	CMemFile hMemFile;
//	if(UnzipFileFromCFile(hInputDoc,hMemFile)<=0)
//		return NULL;
//	//��ȡ�ڴ��ļ��е�������Ϣ��
//	ULONGLONG lFileLen;
//	hMemFile.SeekToBegin();
//	lFileLen=hMemFile.GetLength(); //���ļ�̫�����ǿ���Ҳû�а취�ˡ�
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
//	delete cTemp;  // �ͷ��ڴ档
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
////��CFile�ж�ȡ��Ϣ�����ļ���ѹ֮������ڴ��ļ���
//long CIvFile::UnzipFileFromCFile(CFile *hInputFile,CMemFile &hMemFile)
//{
//	if(hInputFile==NULL||hInputFile->m_hFile==NULL)
//		return -1; //û���ļ����򿪣�
//	//hInputFile.SeekToBegin(); //���½��ļ����õ��ʼ�ĵط���
//	//����80�����������ļ�ͷ����Ϣ��
//	ULONGLONG  uFilePos;
//	uFilePos=hInputFile->Seek(80,CFile::begin );
//	//���ζ�ȡ�ļ�����ѹ�����е���Ϣд��memfile��
//	Bytef cInput[FILEBUFFERSIZE];
//	Bytef cOutput[FILEBUFFERSIZE+1];
//	while(uFilePos!=CFile::end)
//	{
//		uLongf uZipedLength=0,uOutput,uInput;		
//		hInputFile->Read(&uZipedLength,sizeof(uLongf));
//		if(uZipedLength<=0)
//			break;
//		uInput=hInputFile->Read(cInput,uZipedLength);
//		if(uInput!=uZipedLength) //��������ȣ������ļ������˴���
//		{
//			break;
//		}
//		//��ѹ����
//		uOutput=FILEBUFFERSIZE;
//		int iResult=0;
//		iResult=uncompress(cOutput,&uOutput,cInput,uInput);
//		if(uOutput<=0) //���ܳ���������
//			break;
//		//hMemFile.Attach(cOutput,uOutput); //����Ϣд�뵽�ڴ��ļ���
//		hMemFile.Write(cOutput,uOutput);
//		uFilePos=hInputFile->GetPosition();
//	}
//	
//	
//	return 1;
//}
//��ȡ�ļ�����xmldoc��
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
//��xml�ļ�������һ���ڵ�	
CComPtr<IXMLDOMElement> CIvFile::XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName)
{
	CComPtr<IXMLDOMElement> pElement;
	CComPtr<IXMLDOMNode> pNode;
	pDoc->createElement(CComBSTR(strChildName),&pElement);
	if(pParent==NULL) //���ڵ�Ϊ��
	{
		pDoc->appendChild(pElement,&pNode);
	}
	else
	{
		pParent->appendChild(pElement,&pNode);
	}
	return pElement;
}
//���ýڵ������ֵ
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
//�Ƚ������ļ�������·��Path��fileName�����������ļ������·��
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
//�������·���õ��ļ���������·��
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

	//if(pElementTemp==NULL) //��һ���ڵ㲻��element
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
	////��Ҫ�ȴ��ļ���Ȼ���ȡ�ļ�
	// CString strExt;
	////��ȡǰ��80���ַ���
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