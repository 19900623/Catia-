// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAACciScrewCatalogCreation_H
#define CAACciScrewCatalogCreation_H

// System Framework
#include "IUnknown.h" 
#include "CATUnicodeString.h"

// This method creates the CAAScrew.catalog document in the iOutputPath directory
// in using data (Part document) stored in the iInputPath directory.
//
HRESULT CAAScrewCatalogCreation(CATUnicodeString & iInputPath , CATUnicodeString & iOutputPath) ;

#endif

