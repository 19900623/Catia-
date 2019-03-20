// COPYRIGHT DASSAULT SYSTEMES 2001

//Local Framework
#include "CAAAdpCreateCloseSession.h"

//CATPLMComponentInterfaces Framework
#include "CATPLMSessionServices.h"

// System Framework
#include "CATUnicodeString.h"

//standard C++ library
#include "iostream.h"

HRESULT CAAAdpCreateSession(const char *  iRepository, 
				              const char *  iServer, 
							  const char *  iUser,
				              const char * iPassword,
							  const char * iSecurityCtx,
							  CATBoolean iTrace) 
{
  cout <<" CAAAdpCreateSession" << endl;
  if ( TRUE == iTrace )
  {
	  cout <<"   Repository=" << iRepository << endl;
	  cout <<"   Server    =" << iServer << endl;
	  cout <<"   User      =" << iUser << endl;
	  cout <<"   Password  =" << iPassword << endl;
	  cout <<"   SecurityCtx      =" << iSecurityCtx << endl;
  }
  HRESULT rc = CATPLMSessionServices::SetPLMSessionParameter("Repository", iRepository);
  if (FAILED(rc)) { return 1;}
  rc = CATPLMSessionServices::SetPLMSessionParameter("Server", iServer);
  if (FAILED(rc)) { return 1;}
  rc = CATPLMSessionServices::SetPLMSessionParameter("UserID", iUser);
  if (FAILED(rc)) { return 1;}
  rc = CATPLMSessionServices::SetPLMSessionParameter("UserPasswd", iPassword);
  if (FAILED(rc)) { return 1;}
  rc = CATPLMSessionServices::SetPLMSessionParameter("SecurityCtx",iSecurityCtx);
  if (FAILED(rc)) { return 1;}
  //------------------------------------------------------------------

  rc = CATPLMSessionServices::InitPLMSession();
  return rc ;
}

HRESULT CAAAdpCloseSession() 
{
  HRESULT rc = CATPLMSessionServices::ClosePLMSession();
  return rc ;
}
