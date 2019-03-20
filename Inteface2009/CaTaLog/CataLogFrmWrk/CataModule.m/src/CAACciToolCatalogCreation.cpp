
//
//==========================================================================
// Local Framework
#include "CAACciCatalogDocumentServices.h" // To create, save the new catalog document

// ObjectModelerBase
#include "CATDocumentServices.h"         // Open document
#include "CATDocument.h"

// ComponentsCatalogsInterfaces
#include "CATICatalogChapterFactory.h"
#include "CATICatalogChapter.h"
#include "CATICatalogKeyword.h" 
#include "CATICkeType.h"
#include "CATICatalogDescription.h"
#include "CATICatalogPersistentQuery.h"
#include "CATICatalogQueryResult.h"
#include "CATListValCATICatalogDescription_var.h"

// ObjectSpecsModeler
#include "CATLISTV_CATISpecObject.h"

//LiteralFeatures
#include "CATIDesignTable.h"

// System 
#include "CATUnicodeString.h"
#include "CATApplicationFrame.h"
#include "CATIAApplication.h"
#include "CATIADocuments.h"
#include "CATIADocument.h"
#include "CATICatalogKeyword.h"

// Standard C++ library
#include <iostream.h>
#include "Shlwapi.h"

#include "CAACciToolCatalogCreation.h"

#include "tinystr.h"   
#include "tinyxml.h"
#include "CONVERT.h"

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif
//��step�ļ�ת��Ϊcatia�ļ�
BOOL ConvertStepToCatpart(CATUnicodeString strStepFile)
{
	CATUnicodeString PartFile=strStepFile;
	CATUnicodeString Ext;
	Ext.BuildFromWChar(PathFindExtension(strStepFile));
	PartFile=PartFile.SubString(0,PartFile.GetLengthInChar()-Ext.GetLengthInChar());
	CATUnicodeString PartFile1=PartFile;
	PartFile.Append(".CATPart");
	PartFile1.Append(".CATProduct");
	//CATUnicodeString PartName=PartFile.SubString(PartFile. SearchSubString("\\",0,CATUnicodeString::CATSearchModeBackward),PartFile.GetLengthInChar());
	CFileFind finderPart;
	if(finderPart.FindFile(PartFile))
	{
	   cout<<"step->catpart : "<<PartFile+"�Ѵ���,û������"<<endl;
	   return TRUE;
	}
	else if(finderPart.FindFile(PartFile1))
	{
		cout<<"step->catproduct : "<<PartFile1+"�Ѵ���,û������"<<endl;
		return TRUE;

	}

	cout<<"step->catpart : "<<PartFile+"���ɳɹ�"<<endl;
	 CATDocument * pStepDocument = NULL ;
	HRESULT rc;		 
	rc = CATDocumentServices::OpenDocument(strStepFile.CastToCharPtr(), pStepDocument);
	if(pStepDocument)
	{	
		CATUnicodeString strExt;
		strExt.BuildFromWChar(PathFindExtension(strStepFile));
		CATUnicodeString strPartFile=strStepFile;
		strPartFile=strPartFile.SubString(0,strPartFile.GetLengthInChar()-strExt.GetLengthInChar());
		//CATUnicodeString strType;
		//strType=pStepDocument->GetType();
		CATUnicodeString strType="CATPart";
		CATDocumentServices::SaveAs(*pStepDocument,strPartFile,strType);
		CATDocumentServices::Remove(*pStepDocument);
		pStepDocument->Release();		

	}
	
	return TRUE;
}
//�����·���µ�����step�ļ�ת��Ϊcatia��part�ļ�
BOOL PathToCatiaPart(CATUnicodeString strPath)
{
	if(PathIsDirectory(strPath)==FALSE)
		return FALSE;
	CFileFind finder;	
	CATUnicodeString strWildcard(strPath);
	CATUnicodeString strWild;
	strWild.BuildFromWChar(_T("\\*.*"));
	strWildcard.Append(strWild);

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			CATUnicodeString str;
			str.BuildFromWChar( finder.GetFilePath());
			PathToCatiaPart(str);
		}
		else
		{
			CATUnicodeString strFileName;
			strFileName.BuildFromWChar(finder.GetFilePath());
			CATUnicodeString strExt;
			strExt.BuildFromWChar(PathFindExtension(strFileName));
			if(strExt.Compare(CATUnicodeString(".step"))>0) 
			{//������ļ�����chapter��
				ConvertStepToCatpart(strFileName);
			}
		}
	}

	finder.Close();

	return TRUE;

}

void ThrowLastErrorMessage(HRESULT RC)
{
	CATUnicodeString ErrorMessageKey ("") ;
	CATError * pError = CATError::CATGetLastError(RC) ;
	if ( NULL != pError )
	{        
		ErrorMessageKey = pError->GetNLSMessage() ;		
		cout << "   Complete Error message key is : " <<  ErrorMessageKey.ConvertToChar() << endl ;
		int IdErr = pError->GetId() ;
		cout << "   Error ID : " << IdErr << endl  ;
		cout << endl;
		pError->Release() ;
		pError = NULL ;
	}

}

//�ݹ���ö�xml����
void ReadElememt(TiXmlElement* InputElement,CATICatalogChapter * pChapter)
{	
	if(pChapter==NULL) return; 
	//����ǰ�ڵ������
	if (InputElement)
	{
		TiXmlAttribute* attr=InputElement->FirstAttribute();
		CString eleName=InputElement->Value();
		while (attr)
		{
			CString name=eleName+"."+attr->Name();
			CString value=W(attr->Value());
			CString type="String";

			CATUnicodeString catName;
			catName.BuildFromWChar(name);

			CATUnicodeString catValue;
			catValue.BuildFromWChar(value);

			CATUnicodeString catType;
			catType.BuildFromWChar(type);

			CATICatalogKeyword *keyWord=NULL;
			
			pChapter->AddKeyword(catName,catType,keyWord);
			pChapter-> SetDefaultValue(catName,catValue);
			//if(FAILED(rc)) ThrowLastErrorMessage(rc);
			attr=attr->Next();
			
		}
	}
	
	TiXmlElement* tmpElement = InputElement;
	//���ӽڵ�
	if (tmpElement->FirstChildElement())
	{
		   ReadElememt(tmpElement->FirstChildElement(),pChapter);
	}
	//���ֵܽڵ�
	if (tmpElement->NextSiblingElement())
	{
	
		
			ReadElememt(tmpElement->NextSiblingElement(),pChapter);
		
	}
	
}



//������ڵݹ����
BOOL PathToCatalog(CATUnicodeString strPath,CATICatalogChapterFactory *pFactory,CATICatalogChapter *pParent)
{
	if(PathIsDirectory(strPath)==FALSE)
		return FALSE;
	if(pFactory==NULL)
		return FALSE;
	//�������Ŀ¼������һ���½�
       CATICatalogChapter * pChapter = NULL ;

       CString strPathName=strPath.ConvertToChar();
	   strPathName=PathFindFileName(strPathName);
       CATUnicodeString ChapterName;
	   ChapterName.BuildFromWChar( strPathName) ;

       CATBoolean IsEndChapter = FALSE ; //�����Ҫ�������Ƿ����¼�Ŀ¼
		
	   if (strPath.SearchSubString("IVNote", 0, CATUnicodeString::CATSearchModeForward)!=-1)
	   {
		   return TRUE;//   IVNote��д����Ϊ�½�
	   }

	   if(IsHasChildDirectory(strPath)) 
		   IsEndChapter=FALSE;
	   else 
		   IsEndChapter=TRUE;


	   HRESULT rc;
       rc = pFactory->CreateChapter(ChapterName,IsEndChapter,pChapter);
       if ( SUCCEEDED(rc) && pChapter )
       {    
          cout <<"Chapter�� "<<strPath << endl;
       }
	
	   if(pParent!=NULL) //�����chapter���ڸ��ڵ���
	   {

		   CATILinkableObject * pLinkOnChapter = NULL ;
          rc = pChapter->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnChapter);     
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = pParent->AddDescription(piDescription,pLinkOnChapter);
		  }
	   }
    //�ڴ�Ŀ¼��Ѱ����chapterͬ����xml�����ҵ���д��
	CString xmlPath=strPath.ConvertToChar();
	xmlPath.Append(xmlPath.Right(xmlPath.GetLength()-xmlPath.ReverseFind('\\'))); 
	CATUnicodeString strXmlPath;
	strXmlPath.BuildFromWChar(xmlPath) ;
	CATUnicodeString strExt;
	strExt.BuildFromWChar(_T(".xml"));
	strXmlPath.Append(strExt);
    TiXmlDocument doc(strXmlPath);    // ����XML�ļ�
    if(doc.LoadFile())
	{
    TiXmlHandle hDoc(&doc);         // hDoc��&docָ��Ķ���
    TiXmlElement* pRoot= hDoc.FirstChildElement().Element(); //ָ����ڵ�
	ReadElememt(pRoot,pChapter);
	}

	CFileFind finder;	
	CATUnicodeString strWildcard(strPath);
	CATUnicodeString strWild;
	strWild.BuildFromWChar(_T("\\*.*"));
	strWildcard.Append(strWild);

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			CATUnicodeString str;
			str.BuildFromWChar( finder.GetFilePath());
			PathToCatalog(str,pFactory,pChapter);
		}
		else
		{
			CATUnicodeString strFileName;
			strFileName.BuildFromWChar(finder.GetFilePath());
			CATUnicodeString strExt;
			strExt.BuildFromWChar(PathFindExtension(strFileName));
			if(strExt.Compare(CATUnicodeString(".catpart"))>0) 
			{//������ļ�����chapter��
				CATDocument *pChildDoc=NULL;
				rc = CATDocumentServices::OpenDocument(strFileName.CastToCharPtr(), pChildDoc);
				CATILinkableObject * pLinkOn = NULL ;
				rc = pChildDoc->QueryInterface(IID_CATILinkableObject,
					(void **) &pLinkOn); 

				CATICatalogDescription * piDescription = NULL ;
				rc = pChapter->AddDescription(piDescription,pLinkOn); 				
			}
		}
	}

	finder.Close();

	return TRUE;
}

BOOL IsHasChildDirectory(CATUnicodeString strPath)
{
	if(PathIsDirectory(strPath)==FALSE)
		return FALSE;
	CFileFind finder;	
	CATUnicodeString strWildcard(strPath);
	CATUnicodeString strWild;
	strWild.BuildFromWChar(_T("\\*.*"));
	strWildcard.Append(strWild);

	BOOL bFind=FALSE;

	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			bFind=TRUE;
			break;
		}
		else
		{
			continue;
		}
	}

	finder.Close();

	return bFind;

}

//�õ�һ��·���µ�������·��
BOOL GetAllDir(CATUnicodeString strPath,CStringList &lstDir)
{
	if(PathIsDirectory(strPath)==FALSE)
		return FALSE;
	CFileFind finder;	
	CATUnicodeString strWildcard(strPath);
	CATUnicodeString strWild;
	strWild.BuildFromWChar(_T("\\*.*"));
	strWildcard.Append(strWild);

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			lstDir.AddTail(finder.GetFilePath());
			
		}
		else
		{
			continue;
		}
	}

	finder.Close();

	return TRUE;

}

HRESULT PathToCatalog(CATUnicodeString &libPath, CATUnicodeString & outputPath,CATUnicodeString &outputFile) 
{	

    HRESULT rc = E_FAIL ;

	//�����·���µ����е�step�ļ�ת��Ϊcatpart�ļ�
	cout<<"ת��step��catiapart."<<endl;
	PathToCatiaPart(libPath);
	


    cout<<"��ʼ���ɿ��ļ�"<<endl;    
 
    CATDocument * pDocument = NULL ;
    CATICatalogChapterFactory * pFactory = NULL ;

	printf("����factory \n");
    rc = ::CAACreateCatalogDocument(&pDocument,&pFactory);

	if(pFactory==NULL)
	{
		printf("Create Factory Error!\n");
		return FALSE;
	}

	CStringList lstDir;
	GetAllDir(libPath,lstDir);//�õ�libPath�µ�һ����Ŀ¼
	
	POSITION pos;
	pos=lstDir.GetHeadPosition();
	while(pos) //���������Ŀ¼�����½�
	{
		CString strPathTemp=lstDir.GetNext(pos);

		PathToCatalog(libPath,pFactory,NULL);
	}
	//�������Ŀ¼���еݹ���ã�
	

    // ----------------------------------
    // 3- Saving and closing the document
    // ----------------------------------
    if ( SUCCEEDED(rc) && (NULL != pDocument) )
    {
       
	   cout<<"�����ļ� "<<outputPath<<outputFile<<endl;
       rc = ::CAACloseCatalogDocument(outputFile,*pDocument,outputPath);
       pDocument = NULL ;
    }

    cout <<"���ɽ���" << endl << endl;

    return rc ;
}
