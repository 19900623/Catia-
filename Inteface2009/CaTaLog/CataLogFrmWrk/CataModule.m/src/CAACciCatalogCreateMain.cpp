// COPYRIGHT DASSAULT SYSTEMES  2002
//==========================================================================
//
//      Abstract: This use case illustrates how to use the interface of 
//                the ComponentsCatalogInterfaces framework to create a catalog.
//
//                Three catalog documents are created:
//                   - CAAScrew.catalog - See CAACciScrewCatalogCreation.cpp
//                   - CAANuts6Sides.catalog - See CAACciCAANuts6SidesCreation.cpp
//                   - CAATool.catalog - See CAACciCAAToolCreation.cpp
//   
//                Refer to the cpp files to have the caracteristics of these
//                catalogs.
//
//   Steps :
//    1-    Checking input arguments
//    2-    Creating the session
//    3-    Retrieving the output and the input paths
//    4-    Creating the CAAScrew.catalog document
//    5-    Creating the CAANuts6Sides.catalog document
//    6-    Creating the CAATool.catalog document
//    7-    Checking the document's closure
//    8-    Deleting the session
//
//
//==========================================================================
// How to execute :
//
//   mkrun -c "CAACciCatalogCreate InputPath [OutputPath]"
//
//   with      InputPath   : directory which contains the Part documents included 
//                           in the created catalog documents
//                           example : $WSROOT/CAAComponentsCatalogs.edu/InputData
//             OutputPath  : directory to save the created documents
//           
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================


// Local Framework
#include "CAACciScrewCatalogCreation.h"      // To create the CAAScrew catalog
#include "CAACciNuts6SidesCatalogCreation.h" // To create the CAANuts6Sides catalog
#include "CAACciToolCatalogCreation.h"       // To create the CAATool catalog
 
// ObjectModelerBase Framework
#include "CATSessionServices.h"              // To Open and close the session
#include "CATDocument.h"                     // To check that any document is opened
#include "CATIDocId.h"                       // at this end of the batch

// System Framework
#include "CATUnicodeString.h"

// Standard C++ library
#include "iostream.h"

int main(int iArgc, char *iArgv[])

{
  cout << "The CAACciCatalogCreate main program begins ...."<< endl << endl;

  //----------------------------
  // 1- Checking input arguments
  //----------------------------
  if ((3 != iArgc) && ( 2 != iArgc) )
  {
     cout << endl;
     cout << "CAACciCatalogCreate InputPath  [OutputPath]"<< endl;
     cout << "with : InputPath : $WSROOT/CAAComponentsCatalogs.edu/InputData"<< endl;
     cout <<"        OutputPath: Directory to save as the created documents"<<endl;
     cout << endl;
     return 1;
  }

  //------------------------------------------------------------------
  // 2- Creating the session
  // A session must always be created in a batch
  // environment.  Deleting the session at the end of the program is
  // also necessary.
  //------------------------------------------------------------------
  char * pSessionName = "CAA_CreationSample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);

  if (FAILED(rc) )
  {
      cout << "Error in creating session" << endl ;
      return 1;
  }

  //----------------------------------------------
  // 3- Retrieving the output and the input paths
  //----------------------------------------------
  CATUnicodeString InputPath = iArgv[1] ;
  CATUnicodeString OutputPath = "";
  if ( iArgc == 3 )
  {
     OutputPath = iArgv[2] ;
  }

  //----------------------------------
  // 4- Creating the CAAScrew catalog 
  //----------------------------------
  rc = ::CAAScrewCatalogCreation(InputPath,OutputPath);
  if ( FAILED(rc) )
  {
      cout <<" Error in Creating the CAAScrew document" << endl;
      return 1;
  }

  //---------------------------------------
  // 5- Creating the CAANuts6Sides catalog 
  //---------------------------------------
  rc = ::CAANuts6SidesCatalogCreation(InputPath, OutputPath);
  if ( FAILED(rc) )
  {
      cout <<" Error in Creating the CAANuts6Sides document" << endl;
      return 1;
  }

  //----------------------------------
  // 6- Creating the CAATool catalog 
  //----------------------------------
//  rc = ::CAAToolCatalogCreation(InputPath, OutputPath);
  if ( FAILED(rc) )
  {
      cout <<" Error in Creating the CAATool document" << endl;
      return 1;
  }

  //-----------------------------------
  // 7- Checking the document's closure
  //-----------------------------------
  const CATLISTP(CATDocument) * pList = NULL ;
  pList = ::ListDocuments();
  int nbdocument = 0 ;
  if ( NULL != pList)
  {
     for ( int i=1 ; i <= pList->Size() ; i++ )
     {
        CATDocument * pDocument = (*pList)[i] ;
        if ( NULL != pDocument )
        {
           CATIDocId  * pIDocId = NULL ;
           rc = pDocument->GetDocId(&pIDocId);
           if ( SUCCEEDED(rc) )
           {
              CATUnicodeString type ;
              pIDocId->GetType(type) ;
              if ( CATUnicodeString("feat") != type )
              {
                 nbdocument ++ ;
                 CATUnicodeString StorageName ;
                 StorageName = pDocument->StorageName();
                 cout <<" StorageName=" << StorageName.CastToCharPtr() << endl;
              }
              pIDocId->Release();
              pIDocId = NULL ;
           }
        }
     }
     if ( 0 != nbdocument )
     {
        cout << " Some documents are already opened" << endl;
        return 1 ;
     }
  }

  //-------------------------
  // 8- Deleting the session
  //-------------------------
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc))
  {
     cout << "Error in deleting session" << endl ;
     return 1;
  }

  cout << endl;
  cout << "The CAACciCatalogCreate main program is ended."<< endl << endl;

  return 0;
}
