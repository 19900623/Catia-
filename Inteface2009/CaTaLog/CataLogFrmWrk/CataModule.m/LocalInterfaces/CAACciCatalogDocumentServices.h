// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAACciCatalogDocumentServices_H
#define CAACciCatalogDocumentServices_H

// System Framework
#include "IUnknown.h" // for IID and HRESULT
class CATUnicodeString ;

// ObjectModelerBase Framework
class CATDocument ;

// ComponentsCatalogsInterfaces Framework
class CATICatalogChapterFactory ;

// LiteralFeature Framework
class CATIDesignTable ;

// This method creates a new catalog document, and returns a CATICatalogChapterFactory
// interface pointer. This interface is implemented by the root container of the document. 
// 
HRESULT CAACreateCatalogDocument(CATDocument ** opDocument, 
                                 CATICatalogChapterFactory ** opCatalogChapterFactory) ;
                                 

// This method saves and closes the document created by the CAACreateCatalogDocument method.
// The catalog is stored in the iOutputPath directory as iDocumentName for the name.
//
HRESULT CAACloseCatalogDocument(CATUnicodeString & iDocumentName, 
                                CATDocument      & ipDocument, 
                                CATUnicodeString & iOutputPath) ;

// This method retrieves a pointer on a chapter included in the given document. 
// 
HRESULT CAAFindChapterInCatalog(CATUnicodeString & DocumentName,
                             CATUnicodeString & DocumentPath,
                             CATUnicodeString & ChapterName, 
                             const IID & iInterfaceIdentifier,
                             void ** piInterface) ;

// This method retrieves the liste of design table in the given Part document. 
// 
HRESULT CAARetrieveDTInPartDocument(CATUnicodeString & iDocumentName,
                                 CATIDesignTable ** pDesignTableList);

#endif

