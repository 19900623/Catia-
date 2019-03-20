//#pragma once

#ifndef _WINDOWS_
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



//#ifndef CATIAV5Precompiled_H
//
//#define CATIAV5Precompiled_H
//
//#ifdef _WINDOWS_SOURCE
//
//#if _MSC_VER > 1000
//
//	#pragma once
//
//#endif // _MSC_VER > 1000
//
//#ifndef WIN32_LEAN_AND_MEAN
//
//#define WIN32_LEAN_AND_MEAN
//
//#endif
//
//#include <stdio.h>
//
//#include <stdlib.h>
//
//#include <stddef.h>
//
//#include <string.h>
//#if (defined(_MFC_VER) && _MFC_VER>=0x0800) && ( defined PLATEFORME_DS64 )
//
//#pragma warning(push)
//
//#pragma warning(disable:4530) 
//
//#ifndef _WINDOWS_
//
//	#include <wtypes.h>
//
//	#include <wchar.h>
//
//	#include <tchar.h>
//
//	#include <shellapi.h>
//
//#endif // _WINDOWS_
//
//#include <objbase.h>
//
//#pragma warning(pop)
//
//#else
//
//#ifndef _WINDOWS_
//	#include <afxwin.h>
//	#include <afxext.h>         // MFC extensions
//	#include <afxdisp.h>        // MFC Automation classes
//	#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//	#ifndef _AFX_NO_AFXCMN_SUPPORT
//	#include <afxcmn.h>			// MFC support for Windows Common Controls
//	#endif // _AFX_NO_AFXCMN_SUPPORT
//#else
//	#undef  _WINDOWS_
//	#include <afxwin.h>
//	#include <afxext.h>         // MFC extensions
//	#include <afxdisp.h>        // MFC Automation classes
//	#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//	#ifndef _AFX_NO_AFXCMN_SUPPORT
//	#include <afxcmn.h>			// MFC support for Windows Common Controls
//	#endif // _AFX_NO_AFXCMN_SUPPORT
//#define  _WINDOWS_
//#endif // _WINDOWS_



//#include <objbase.h>
//
//#endif
//
//#endif // _WINDOWS_SOURCE
//
//#endif

