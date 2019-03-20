// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAACciToolCatalogCreation_H
#define CAACciToolCatalogCreation_H

// System Framework
#include "CATErrorDef.h" 
#include "CATUnicodeString.h"

// This method creates the CAATool.catalog document in the iOutputPath directory
// in using data (Part document) stored in the iInputPath directory and also 
// stored in the iOutputPath directory. In this last case, it is the previous 
// catalog document created by the CAAScrewCatalogCreation and the
// CAANuts6SidesCatalogCreation functions
//


#ifndef _WINDOWS_
	#include "afx.h"
	#include <afxwin.h>
	#include <afxext.h>         // MFC extensions
	#include <afxdisp.h>        // MFC Automation classes
	#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
	#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>			// MFC support for Windows Common Controls
	#endif // _AFX_NO_AFXCMN_SUPPORT
#else
	#undef  _WINDOWS_
	#include <afxwin.h>
	#include <afxext.h>         // MFC extensions
	#include <afxdisp.h>        // MFC Automation classes
	#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
	#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>			// MFC support for Windows Common Controls
	#endif // _AFX_NO_AFXCMN_SUPPORT
	#define  _WINDOWS_
#endif

HRESULT PathToCatalog(CATUnicodeString &libPath, CATUnicodeString & outputPath,CATUnicodeString &outputFile) ;
BOOL IsHasChildDirectory(CATUnicodeString strPath);


#endif

