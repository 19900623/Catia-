// COPYRIGHT DASSAULT SYSTEMES  2002

// ObjectModelerBase Framework
#include "CATDocumentServices.h"         // Open/remove/new document
#include "CATDocument.h"                 // to handle the CATDocument
#include "CATInit.h"                     // To retrieve the root container

// ObjectSpecsBase Framework
#include "CATLISTV_CATISpecObject.h"     // To retrieve the list of design table
#include "CATIContainer.h"               // for the root container of the document

// ComponentsCatalogsInterfaces Framework
#include "CATICatalogChapterFactory.h"      
#include "CATICatalogChapter.h"

//MecModInterfaces Framework
#include "CATIPrtContainer.h"            // The Part root container

//LiteralFeatures
#include "CATIParmPublisher.h"
#include "CATIDesignTable.h"

// Standard C++ library
#include <iostream.h>

// System Framework
#include "CATUnicodeString.h"
#include "CATICatalogChapter.h"
// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif
//HRESULT CreateChaper(CATUnicodeString charperName)
//{
//	CATICatalogChapter *pCatiCatalogChapter=NULL;
//	CATBoolean isEndcharper=FALSE;
//	CATICatalogChapterFactory* opCatalogChapterFactory=NULL;
//    opCatalogChapterFactory->CreateChaper()
//}
#include "CataLog.h"
#include "stdafx.h"
#include "CATUnicodeString.h"

#include "CAACciCatalogDocumentServices.h"
#include "CATICatalogChapterFactory.h"

//virtual HRESULT CreateChapter ( const CATUnicodeString& iName, 
//							   CATBoolean iKindIsEndChapter,
//							   CATICatalogChapter*& oNewChapter) = 0 ;

/*Language="VBSCRIPT"

Sub CATMain()

Set documents1 = CATIA.Documents

Set catalogDocument1 = documents1.Add("CatalogDocument")

Set catalogDocument1 = CATIA.ActiveDocument

catalogDocument1.SaveAs "F:\Catia19-32\testcatia\tt\CatalogDocument1.catalog"

End Sub*/


HRESULT CAACreateCatalogDocument(CATDocument ** opDocument, 
                                 CATICatalogChapterFactory ** opCatalogChapterFactory) 
{
    HRESULT rc = E_FAIL ;

    if ( NULL == opDocument ) return rc ;
    *opDocument = NULL ;
    if ( NULL == opCatalogChapterFactory ) return rc ;
    * opCatalogChapterFactory = NULL ;

    // 1- Creating a new document
    rc = CATDocumentServices::New("catalog",*opDocument);
    if ( SUCCEEDED(rc) )
    {
        CATInit *pInitOnDoc = NULL ;
        rc = (*opDocument)->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
        if ( FAILED(rc) )
        {
           cout << "Error in retrieving the CATInit interface"<< endl;
        }else
        {
           //  2- Retrieving the root container
           CATIContainer *pIRootCont = NULL ;
           pIRootCont = (CATIContainer*)pInitOnDoc->GetRootContainer("CATIContainer");

           if ( NULL == pIRootCont )
           {
              cout << "The root container is NULL"<< endl;
              rc = E_FAIL ;
           }else
           {
              // 3- Retrieving the CATICatalogChapterFactory pointer on the root container
              rc = pIRootCont->QueryInterface(IID_CATICatalogChapterFactory,
                                              (void **) opCatalogChapterFactory);
              if ( FAILED(rc) )
              {
                  cout << "Error in retrieving the CATICatalogChapterFactory interface"<< endl;
              }
              pIRootCont->Release();
              pIRootCont = NULL ;
           }
           pInitOnDoc->Release();
           pInitOnDoc = NULL ;
        }
    }

	
    return rc ;
}
                                 
HRESULT CAACloseCatalogDocument(CATUnicodeString & iDocumentName, 
                                CATDocument      & iDocument, 
                                CATUnicodeString & iOutputPath)
{
   HRESULT rc = E_FAIL ;

   //1- Saving the document 
   // ----------------------
   CATUnicodeString DocumentSaveAsName = iDocumentName + ".catalog";
   CATUnicodeString EmptyString ="" ;
   if ( EmptyString != iOutputPath )
   {
      DocumentSaveAsName = iOutputPath + Slash + DocumentSaveAsName ;
   }
 
   rc = CATDocumentServices::SaveAs (iDocument,DocumentSaveAsName.CastToCharPtr());
   if (FAILED(rc))
   {
      cout << "Error in saving document "<< DocumentSaveAsName.CastToCharPtr() << endl;
   }

   //2- Removing the document from the session
   // ------------------------------------------
   rc = CATDocumentServices::Remove(iDocument);
   if (FAILED(rc) )
   {
      cout << "Error in closing document "<< DocumentSaveAsName.CastToCharPtr() << endl;
   }

   return rc ;
}


HRESULT CAAFindChapterInCatalog(CATUnicodeString & iDocumentName,
                             CATUnicodeString & iDocumentPath,
                             CATUnicodeString & iChapterName, 
                             const IID & iInterfaceIdentifier,
                             void ** opInterface)
{
    HRESULT rc = E_FAIL ;
    if (NULL == opInterface) return rc ;
    *opInterface = NULL ;
     
    // 1-Building the storage name of the document
    // --------------------------------------------------
    CATDocument * pDocument = NULL ;
    CATUnicodeString EmptyString ="" ;
    CATUnicodeString ModelDocName = iDocumentName + ".catalog" ;
    if ( EmptyString != iDocumentPath )
    {
       ModelDocName = iDocumentPath + Slash + ModelDocName ;
    }
 
    // 2-Opening the document
    // ----------------------
    // Note: In this batch this method is only called to retrieve a chapter 
    // (a family or not) to add it in a description of a chapter of the 
    // CAATool catalog document. So pDocument will be closed when the
    // CAATool document will be closed.
    //
    CATDocumentServices::OpenDocument(ModelDocName.CastToCharPtr(), pDocument);
    if ( NULL == pDocument ) 
    {
       return rc ;
    }

    // 3-Retrieving the root container
    // --------------------------------
    CATInit *pInitOnDoc = NULL ;
    rc = pDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
    if ( FAILED(rc) )
    {
       cout << "Error in retrieving the CATInit interface"<< endl;
    }else
    {
       CATIContainer *pIRootCont = NULL ;
       pIRootCont = (CATIContainer*)pInitOnDoc->GetRootContainer("CATIContainer");

       if ( NULL == pIRootCont )
       {
          cout << "The root container is NULL"<< endl;
          rc = E_FAIL ;
       }else
       {
          // 4-Retrieving its CATICatalogChapterFactory interface pointer
          // -----------------------------------------------------------
          CATICatalogChapterFactory * pICatalogChapterFactory = NULL ;
          rc = pIRootCont->QueryInterface(IID_CATICatalogChapterFactory,
                                              (void **) &pICatalogChapterFactory);
          if ( FAILED(rc) )
          {
             cout << "Error in retrieving the CATICatalogChapterFactory interface"<< endl;
          }else
          {
              // 5- Researching the chapter 
              // ---------------------------
              CATICatalogChapter *pICatalogChapter = NULL ;
              rc = pICatalogChapterFactory->FindChapter(iChapterName,pICatalogChapter);

              if ( SUCCEEDED(rc) )
              {
                 rc = pICatalogChapter->QueryInterface(iInterfaceIdentifier,
                                              (void **) opInterface);
                
                 pICatalogChapter->Release();
                 pICatalogChapter = NULL ;
              }
              pICatalogChapterFactory->Release() ;
              pICatalogChapterFactory = NULL ;
          }
          pIRootCont->Release();
          pIRootCont = NULL ;
       }
       pInitOnDoc->Release();
       pInitOnDoc = NULL ;
    }

    if ( (NULL != pDocument) && ( NULL == opInterface ) )
    {
        // the chapter has not been found
        // the document must be closed here
        // otherwise it will be closed when the catalog which will pointed
        // on this document will be closed itself. 
        // See the specic usage of this method: retrieve a chapter to set in
        // an another catalog
        rc = CATDocumentServices::Remove(*pDocument);
        if (FAILED(rc) )
        {
           cout << "Error in closing document "<< ModelDocName.CastToCharPtr() << endl;
        }
    }
    return rc ;
}

HRESULT CAARetrieveDTInPartDocument(CATUnicodeString & iDocumentName,
                                 CATIDesignTable  ** opDesignTable) 
{
    HRESULT rc = E_FAIL ;

    if ( NULL == opDesignTable ) return rc ;
    *opDesignTable = NULL ;

    // 1- Opening the document
    CATDocument * pDocument = NULL ;
    rc = CATDocumentServices::OpenDocument(iDocumentName.CastToCharPtr(),pDocument);

    if ( SUCCEEDED(rc) )
    {
        CATInit *pInitOnDoc = NULL ;
        rc = pDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
        if ( FAILED(rc) )
        {
           cout << "Error in retrieving the CATInit interface"<< endl;
        }else
        {
           //  2- Retrieving the root container
           CATIPrtContainer *pIPrtCont = NULL ;
           pIPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

           if ( NULL == pIPrtCont )
           {
              cout << "The root container is NULL"<< endl;
              rc = E_FAIL ;
           }else
           {
              // 3- Retrieving the MechanicalPart feature
              CATISpecObject_var spSpecObjectPart = pIPrtCont->GetPart();
              if ( NULL_var == spSpecObjectPart )
              {
                 cout << "The MechanicalPart is NULL"<< endl;
                 rc = E_FAIL ;
              }else
              {
                  // 4-Retrieving the list of design table
                  CATIParmPublisher * pIParmPublisher = NULL ;
                  rc = spSpecObjectPart->QueryInterface(IID_CATIParmPublisher,
                                                         (void **) &pIParmPublisher);
                  if ( SUCCEEDED(rc) )
                  {
                     CATLISTV (CATISpecObject_var) DesignTableList ;
                     pIParmPublisher->GetAllChildren("CATIDesignTable",DesignTableList);
                     int NbDesignTable = DesignTableList.Size();
                     if ( NbDesignTable >= 1 )
                     {
                        CATISpecObject_var specObj = DesignTableList[1] ;
                        rc = specObj->QueryInterface(IID_CATIDesignTable,(void**) opDesignTable);
                     }       
                 
                     pIParmPublisher->Release();
                     pIParmPublisher = NULL ;
                  }
              }

              pIPrtCont->Release();
              pIPrtCont = NULL ;
           }
           pInitOnDoc->Release();
           pInitOnDoc = NULL ;
        }
    }

    return rc ;
}
