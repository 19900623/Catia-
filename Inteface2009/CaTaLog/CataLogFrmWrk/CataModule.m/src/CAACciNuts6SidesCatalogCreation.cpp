// COPYRIGHT DASSAULT SYSTEMES  2002
//==========================================================================
//
//   Abstract: This function shows how to create a catalog which has a
//             end chapter which contains a link with Part document with  
//             design table (DT)
//
//             The name of the document created is CAANuts6Sides.catalog. Its 
//             structure is the following:
//                
//             Nuts6Sides ( Root chapter)
//                Nuts6SidesFamily ( End Chapter of Family )
//                   CAANuts6Sides.CATPart 
//
//  Steps :
//    1-  Creating the new document 
//    2-  Filling the document
//      2-1 Creating the Nuts6Sides chapter, the root chapter
//      2-2 Creating the Nuts6SidesFamily chapter, a end chapter
//         2-2-1 Creating the chapter
//         2-2-2 Associating the Nuts6SidesFamily chapter to the Nuts6Sides 
//               chapter
//      2-3 Adding the CAANuts6Sides Part document which contains a DT
//         2-3-1 Verifying the keyword list of the Nuts6SidesFamily chapter before 
//         2-3-2 Retrieving the design table
//         2-3-3 Associating the design table to the piNuts6SidesFamily family 
//         2-3-4 Verifying the keyword list of the Nuts6SidesFamily chapter after 
//         2-3-5 Retrieving the descriptions
//         2-3-6 Displaying the value for each keyword
//         2-3-7 Resolving the Part configuration
//      2-4 Releasing the pointers
//    3-  Saving and closing the document
//
//
//==========================================================================
// Local Framework
#include "CAACciCatalogDocumentServices.h"   // To create, save the new catalog document

// ObjectModelerBase
#include "CATDocumentServices.h"         // New, Save document
#include "CATDocument.h"
#include "CATInit.h"
#include "CATIAlias.h"                  // To display the name of the Part Document

// ObjectSpecsModeler
#include "CATIContainer.h"

// ComponentsCatalogsInterfaces
#include "CATICatalogChapterFactory.h"
#include "CATICatalogChapter.h"
#include "CATICatalogDescription.h"
#include "CATListValCATICatalogKeyword_var.h"
#include "CATListValCATICatalogDescription_var.h"
#include "CATICatalogKeyword.h"

//LiteralFeatures
#include "CATIDesignTable.h"

// Standard C++ library
#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

HRESULT CAANuts6SidesCatalogCreation(CATUnicodeString & iInputPath, CATUnicodeString & iOutputPath) 
{
    HRESULT rc = E_FAIL ;

    cout <<"Beginning of the CAANuts6Sides.catalog creation" << endl;

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
       // 2-1 Creating the Nuts6Sides chapter, the root chapter
       // ----------------------------------------------------
       CATICatalogChapter * piNuts6SidesChapter = NULL ;

       CATUnicodeString ChapterName = "Nuts6Sides" ;
       CATBoolean IsEndChapter = FALSE ;
       rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piNuts6SidesChapter);
       if ( SUCCEEDED(rc) )
       {    
          cout <<"   The Nuts6Sides chapter has been created" << endl;
       }

       // 2-2 Creating the Nuts6SidesFamily chapter, a end chapter
       // --------------------------------------------------------
       CATICatalogChapter * piNuts6SidesFamily = NULL ;

       // 2-2-1 Creating the chapter
       if ( SUCCEEDED(rc) )
       {
          CATUnicodeString     ChapterName = "Nuts6SidesFamily" ;
          CATBoolean           IsEndChapter = TRUE ;
          rc = pICatalogChapterFactory->CreateChapter(ChapterName,IsEndChapter,piNuts6SidesFamily);

          if ( SUCCEEDED(rc) )
          {
             cout <<"   The Nuts6SidesFamily end chapter has been created" << endl;
          }
       }

       // 2-2-2 Associating the Nuts6SidesFamily chapter to the Nuts6Sides chapter
       if ( SUCCEEDED(rc) && (NULL != piNuts6SidesFamily) && (NULL != piNuts6SidesChapter) )
       {                    
          CATILinkableObject * pLinkOnFamily = NULL ;
          rc = piNuts6SidesFamily->QueryInterface(IID_CATILinkableObject,
                                              (void **) &pLinkOnFamily);     
          if ( SUCCEEDED(rc) )
          {
             CATICatalogDescription * piDescription = NULL ;
             rc = piNuts6SidesChapter->AddDescription(piDescription, pLinkOnFamily);
             if ( SUCCEEDED(rc) && (NULL != piDescription) )
             {
                piDescription->Release();
                piDescription = NULL ;
             }

             pLinkOnFamily->Release();
             pLinkOnFamily = NULL ;
          }
       }

       // 2-3 Adding the CAANuts6Sides Part document which contains a DT  
       // --------------------------------------------------------------
       if ( SUCCEEDED(rc) && (NULL != piNuts6SidesFamily) )
       {
          // 2-3-1 Verifying the keyword list of the Nuts6SidesFamily chapter before
          CATListValCATICatalogKeyword_var * pListKeyword = NULL ;
          rc = piNuts6SidesFamily->ListKeywords(pListKeyword);
 
          if ( SUCCEEDED(rc) && (NULL != pListKeyword) )
          {        
             cout <<"      Before, there is 0 keywords:" << endl;
             rc = S_OK ;
          }else rc = E_FAIL;

          // 2-3-2 Retrieving the design table
          CATDocument * pCAANuts6SidesDocument = NULL ;
          CATUnicodeString ModelDocName = "CAANuts6Sides.CATPart" ;
          ModelDocName = iInputPath + Slash + "CAANuts6Sides.CATPart" ;

          CATIDesignTable * pDesignTable = NULL ;

          if ( SUCCEEDED(rc) )
          {
             rc = ::CAARetrieveDTInPartDocument(ModelDocName,&pDesignTable);
          }

          // 2-3-3 Associating the design tables to the piNuts6SidesFamily family 
          if ( SUCCEEDED(rc) && ( NULL!=pDesignTable) )
          {
             rc = piNuts6SidesFamily->AddFamilyDescriptionsFromDesignTable(pDesignTable);
             if ( SUCCEEDED(rc) )
             {
                cout << "      A Design table has been added" << endl;
             }else cout <<" Error in creating the Part family" << endl;
             
             pDesignTable->Release();
             pDesignTable = NULL ;
          } 

          // 2-3-4 Verifying the keyword list of the Nuts6SidesFamily chapter after 
          int NbKeyword = 0 ;
          if ( SUCCEEDED(rc) )
          {
             rc = piNuts6SidesFamily->ListKeywords(pListKeyword);
             if ( SUCCEEDED(rc) && (NULL != pListKeyword) )
             {
                NbKeyword = pListKeyword->Size() ;
                cout <<"      Now, there are " << pListKeyword->Size() << " keywords:" << endl;
  
                for ( int i= 1 ; i<= NbKeyword; i++)
                {
                   CATICatalogKeyword_var spKeyword = (*pListKeyword)[i];
                   if ( NULL_var != spKeyword )
                   {              
                      cout <<"         " << spKeyword->GetKeywordName().CastToCharPtr() << endl;               
                   }
                   
                }
                cout << endl;
             }else rc = E_FAIL ;
          }

          // 2-3-5 Retrieving the descriptions 
          CATListValCATICatalogDescription_var * pListDesc = NULL ;
          int NbDesc = 0 ;
          if ( SUCCEEDED(rc) )
          {
             rc = piNuts6SidesFamily->ListDescriptions(pListDesc);
             if ( SUCCEEDED(rc) )
             {
                NbDesc = pListDesc->Size() ;
                cout <<"      There is " <<NbDesc << " descriptions:" << endl;
             }
          }

          // 2-3-6 Displaying the value for each keyword 
          if ( SUCCEEDED(rc) && ( NULL != pListKeyword) && ( NULL !=pListDesc))
          {
                 int i = 1 ;
                 while ( SUCCEEDED(rc) && (i <= NbDesc ))
                 {
                     CATUnicodeString KWName, KWValue;
                     CATICatalogDescription_var spDesc = (*pListDesc)[i] ;
    
                     if ( NULL_var != spDesc )
                     {
                        for ( int j= 1 ; j <= NbKeyword ; j++ )
                        {
                             const CATICatalogKeyword_var& Keyword_j = (*pListKeyword)[j];
                             if ( NULL_var !=  Keyword_j )
                             {
                                CATUnicodeString KWName = Keyword_j->GetKeywordName();
                                rc = spDesc->GetValue(KWName, KWValue) ;
                                if ( rc == S_OK ) 
                                {
                                    cout << "        " << KWName.CastToCharPtr();
                                    cout << " =" << KWValue.CastToCharPtr() << endl;
                                }
                             }
                        }
                     }
                     cout << endl;
                     i++ ;
                 }
          }

          // 2-3-7 Resolving Part Configuration  
          if ( SUCCEEDED(rc) && ( NULL!= pListDesc) )
          {
                 int i = 1 ;
                 while ( SUCCEEDED(rc) && (i <= NbDesc ))
                 {
                     CATICatalogDescription_var spDesc = (*pListDesc)[i] ;
                      
                     if ( NULL_var != spDesc )
                     {
                        rc = spDesc->ResolvedDocumentFromDesignTable();
                        if ( SUCCEEDED (rc) )
                        {
                            CATBaseUnknown * pObject = NULL ;
                            rc = spDesc->GetObject(pObject);
                            if ( SUCCEEDED(rc) && (NULL != pObject))
                            {
                               CATIAlias * pIAlias = NULL ;
                               rc = pObject->QueryInterface(IID_CATIAlias,
                                                        (void **) & pIAlias);

                               if ( SUCCEEDED(rc) )
                               {
                                   CATUnicodeString Identifier;
                                   Identifier = pIAlias->GetAlias() ;
                                   cout <<"      File= " ;
                                   cout <<Identifier.CastToCharPtr() << endl;

                                   pIAlias->Release();
                                   pIAlias = NULL ;
                               }

                               pObject->Release();
                               pObject = NULL ;
                            }
                        }
                     }
                     i++ ;
                 }
          }

          if ( NULL != pListKeyword )
          {
             delete pListKeyword ;
             pListKeyword = NULL ;
          }
          if ( NULL != pListDesc )
          {
             delete pListDesc ;
             pListDesc = NULL ;
          }
       }

       // 2-4 Releasing pointers
       // -----------------------
       if ( NULL != piNuts6SidesFamily )
       {
          piNuts6SidesFamily->Release();
          piNuts6SidesFamily = NULL ;
       }
       if ( NULL != piNuts6SidesChapter )
       {
          piNuts6SidesChapter->Release();
          piNuts6SidesChapter = NULL ;
       }
 
       pICatalogChapterFactory->Release();
       pICatalogChapterFactory = NULL ;
    }

    // ----------------------------------
    // 3- Saving and closing the document
    // ----------------------------------
    if ( SUCCEEDED(rc) && (NULL != pDocument) )
    {
       CATUnicodeString DocumentName = "CAANuts6Sides" ;
       rc = ::CAACloseCatalogDocument(DocumentName,*pDocument,iOutputPath);
       pDocument = NULL ;
    }

    cout <<"Ending of the CAANuts6Sides.catalog creation" << endl << endl;

    return rc ;
}


