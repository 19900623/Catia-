// COPYRIGHT DASSAULT SYSTEMES  2002
//==========================================================================
//
//   Abstract: This function shows how to create a catalog which has an
//             end chapter which contains links with Part document. 
//             These Part documents are without Design Table (DT).
//                
//             The name of the document created is CAAScrew.catalog. Its 
//             structure is the following:
//             
//             Screws ( Root chapter)
//                ScrewsFamily ( End Chapter of Family )
//                   CAAScrew.CATPart 
//                   CAAGroovedScrew.CATPart
//
//             The Screws and the ScrewsFamily chapter have only one keyword:
//             ToolType and Material respectively. These keywords have a
//             default value, "Screw" and "Iron" respectively.
//
//   Steps :
//    1-  Creating the new document 
//    2-  Filling the document
//      2-1 Creating the Screws chapter, the root chapter
//         2-1-1 Creating the chapter
//         2-1-2 Creating the ToolType keyword
//         2-1-3 Setting the default value for the ToolType keyword
//      2-2 Creating the ScrewsFamily chapter, a end chapter
//         2-2-1 Creating the chapter
//         2-2-2 Associating the ScrewsFamily chapter to the Screws chapter 
//            2-2-2-1 Creating the new description
//            2-2-2-1 Associating a preview image from a filename to the family
//         2-2-3 Creating the Material keyword
//         2-2-3 Setting the default value for the Material keyword
//      2-3 Adding the CAAScrew Part document as component
//         2-3-1 Opening the Part document
//         2-3-2 Associating the Part document to the ScrewsFamily end chapter
//      2-4 Adding the CAAGroovedScrew Part document as component
//         2-4-1 Opening the Part document
//         2-4-2 Associating the Part document to the ScrewsFamily end chapter
//      2-5 Releasing the pointers
//    3-  Saving and closing the document
//
//==========================================================================
// Local Framework
#include "CAACciCatalogDocumentServices.h" // To create, save the new catalog document

// ObjectModelerBase
#include "CATDocumentServices.h"         // To open the Part document
#include "CATDocument.h"                 // 
#include "CATILinkableObject.h"          // To link an object with a chapter
                                         
// ComponentsCatalogsInterfaces
#include "CATICatalogChapterFactory.h"
#include "CATICatalogChapter.h"
#include "CATICatalogKeyword.h" 
#include "CATICatalogDescription.h"

// System 
#include "CATUnicodeString.h"

// Standard C++ library
#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

HRESULT CAAScrewCatalogCreation(CATUnicodeString & iInputPath, CATUnicodeString & iOutputPath ) 
{
    HRESULT rc = E_FAIL ;

    cout <<"Beginning of the CAAScrew.catalog creation" << endl;

    // ----------------------------------
    // 1- Creating a new catalog document
    // ----------------------------------
    CATDocument * pDocument = NULL ;
    CATICatalogChapterFactory * pICatalogChapterFactory = NULL ;

    rc = ::CAACreateCatalogDocument(&pDocument,&pICatalogChapterFactory);

    // ------------------------
    // 2- Filling the document
    // ------------------------
    if ( SUCCEEDED(rc) && ( NULL != pICatalogChapterFactory) )
    {
       // 2-1 Creating the Screws chapter, the root chapter
       // -------------------------------------------------
       CATICatalogChapter * piScrewsChapter = NULL ;

       // 2-1-1 Creating the chapter
       CATUnicodeString ChapterName = "Screws" ;
       CATBoolean IsEndChapter = FALSE ;
       rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piScrewsChapter);
       if ( SUCCEEDED(rc) )
       {    
          cout <<"   The Screws chapter has been created" << endl;
       }

       // 2-1-2 Creating the ToolType keyword 
       if ( SUCCEEDED(rc) && (NULL != piScrewsChapter))
       {
          CATICatalogKeyword * piKeyword = NULL ;
          rc = piScrewsChapter->AddKeyword("ToolType","String",piKeyword);
          if ( SUCCEEDED(rc) )
          {
             piKeyword->Release();
             piKeyword = NULL ;
          }
       }

       // 2-1-3 Setting the default value for the ToolType keyword
       if ( SUCCEEDED(rc) && (NULL != piScrewsChapter))
       {
          CATUnicodeString Value = "Screw" ;
          rc = piScrewsChapter->SetDefaultValue("ToolType",Value);
       }

       // 2-2 Creating the ScrewsFamily chapter, a end chapter
       // ----------------------------------------------------
       CATICatalogChapter * piScrewsFamily = NULL ;

       // 2-2-1 Creating the chapter
       if ( SUCCEEDED(rc) )
       {
          CATUnicodeString     ChapterName = "ScrewsFamily" ;
          CATBoolean           IsEndChapter = TRUE ;
          rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piScrewsFamily);
          if ( SUCCEEDED(rc) )
          {
             cout <<"   The Screws Family has been created" << endl;
          }
       }

       // 2-2-2 Associating the ScrewsFamily chapter to the Screws chapter 
       if (SUCCEEDED(rc) && (NULL != piScrewsFamily) && (NULL != piScrewsChapter) )
       {
          CATILinkableObject * pLinkOnScrewsFamily = NULL ;
          rc = piScrewsFamily->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnScrewsFamily);     
          if ( SUCCEEDED(rc) )
          {
             // 2-2-2-1 Creating the new description
             CATICatalogDescription * piDescription = NULL ;
             rc = piScrewsChapter->AddDescription(piDescription,pLinkOnScrewsFamily);
             if ( SUCCEEDED(rc) && (NULL != piDescription) )
             {
                // 2-2-2-2 Associating with an image from a file for the preview
                CATUnicodeString PreviewFileName="CAAScrewFamilyPreview.jpg" ;     
                PreviewFileName = iInputPath + Slash + PreviewFileName ;
                
                rc = piDescription->SetPreviewName(PreviewFileName);
                if ( SUCCEEDED(rc) )
                {
                    cout <<"      The Screws Family has a preview from a file" << endl;
                }
                piDescription->Release();
                piDescription = NULL ;
             }

             pLinkOnScrewsFamily->Release();
             pLinkOnScrewsFamily = NULL ;
          }
       }

       // 2-2-3 Creating the Material keyword
       if ( SUCCEEDED(rc) && (NULL != piScrewsFamily) )
       {
          CATICatalogKeyword * piKeyword = NULL ;
          rc = piScrewsFamily->AddKeyword("Material","String",piKeyword);
          if ( SUCCEEDED(rc) )
          {
             piKeyword->Release();
             piKeyword = NULL ;
          }
       }
       // 2-2-4 Setting the default value for the Material keyword
       if ( SUCCEEDED(rc) && (NULL != piScrewsFamily) )
       {
          CATUnicodeString Value = "Iron" ;
          rc = piScrewsFamily->SetDefaultValue("Material",Value);
       }

       // 2-3 Adding the CAAScrew Part document as component
       // --------------------------------------------------  
       
       // 2-3-1 Opening the Part document
       CATDocument * pScrewDocument = NULL ;
       if ( SUCCEEDED(rc) )
       {             
          
          CATUnicodeString ModelDocName = "CAAScrew.CATPart" ;
          ModelDocName = iInputPath + Slash + "CAAScrew.CATPart" ;
 
          rc = CATDocumentServices::OpenDocument(ModelDocName.CastToCharPtr(), pScrewDocument);
       }

       // 2-3-2 Associating the Part document to the ScrewsFamily end chapter
       if ( SUCCEEDED(rc) && (NULL != pScrewDocument) && (NULL != piScrewsFamily) )
       {
          CATILinkableObject * pLinkOnScrewPart = NULL ;
          rc = pScrewDocument->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnScrewPart);  
          if ( SUCCEEDED(rc ) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piScrewsFamily->AddDescription(piDescription,pLinkOnScrewPart);       
             if ( SUCCEEDED(rc ) && (NULL != piDescription) )
             {
                cout <<"   The CAAScrew.CATPart document is a description " ;
                cout << "of the CAAScrews family " << endl;

                piDescription->Release();
                piDescription = NULL ;
             }

             pLinkOnScrewPart->Release();
             pLinkOnScrewPart = NULL ;
          }
       } 
       
       // 2-4 Adding the CAAGroovedScrew Part document as component
       // ---------------------------------------------------------  
       
       if ( SUCCEEDED(rc) && (NULL != piScrewsFamily) )
       {       
          CATICatalogDescription * piDescription = NULL ;
          rc = piScrewsFamily->AddDescription(piDescription);
          if ( SUCCEEDED(rc) && (NULL != piDescription) )
          {
             CATUnicodeString ModelDocName ;
             ModelDocName = iInputPath + Slash + "CAAGroovedScrew.CATPart" ;
 
             rc = piDescription->SetDocumentName(ModelDocName);
             if ( SUCCEEDED(rc) )
             {
                cout <<"   The CAAGroovedScrew.CATPart document is a description " ;
                cout << "of the CAAScrews family " << endl;
             }

             piDescription->Release();
             piDescription = NULL ;
          }
       }   
       
       // 2-5 Releasing pointers
       // -----------------------
       if ( NULL != piScrewsFamily )
       {
          piScrewsFamily->Release();
          piScrewsFamily = NULL ;
       }
       if ( NULL != piScrewsChapter )
       {
          piScrewsChapter->Release();
          piScrewsChapter = NULL ;
       }
 
       pICatalogChapterFactory->Release();
       pICatalogChapterFactory = NULL ;

    }

    // ----------------------------------
    // 3- Saving and closing the document
    // ----------------------------------
    if ( SUCCEEDED(rc) && (NULL != pDocument) )
    {
        CATUnicodeString DocumentName = "CAAScrew" ;
        rc = ::CAACloseCatalogDocument(DocumentName,*pDocument,iOutputPath);
        pDocument = NULL ;
    }

    cout <<"Ending of the CAAScrew.catalog creation" << endl << endl;

    return rc ;
}

