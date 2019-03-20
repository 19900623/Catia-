// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAACciNuts6SidesCatalogCreation_H
#define CAACciNuts6SidesCatalogCreation_H

// System Framework
#include "IUnknown.h"
#include "CATUnicodeString.h"

// This method creates the CAANuts6Sides.catalog document in the iOutputPath directory
// in using data (Part document) stored in the iInputPath directory.
//
HRESULT CAANuts6SidesCatalogCreation(CATUnicodeString & iInputPath, CATUnicodeString & iOutputPath) ;

#endif

