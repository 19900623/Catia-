#ifndef CAAAdpCreateCloseSession_H
#define CAAAdpCreateCloseSession_H

//COPYRIGHT DASSAULT SYSTEMES 2001



#include <CATBaseUnknown.h> 
#include <CATSysBoolean.h>
/**
 * Creates a session and connects to a repository.
 * @param iRepository
 *  The repository name.
 * @param iServer
 *  The server name and port number of the repository
 * @param iUser
 *  The user name.
 * @param iPassword
 *  The password associated with the user.
 * @param iRole
 *  The role associated with the user.
 * @return
 *  <ul>
 *    <li><tt>S_OK</tt>: the connection is successful, and the session is opened </li>
 *    <li><tt>E_FAIL</tt>: internal error</li>
 *    <li><tt>E_INVALIDARG</tt>: <tt>iRepository</tt> is NULL</li>
 *   </ul>
 */
HRESULT  CAAAdpCreateSession(const char *  iRepository, 
				              const char *  iServer, 
							  const char *  iUser,
				              const char * iPassword,
							  const char * iRole,
							  CATBoolean iTrace = FALSE) ;

/**
 * Closes a session.
 * @return
 *  <ul>
 *    <li><tt>S_OK</tt>: the disconnection is successful  </li>
 *    <li><tt>E_FAIL</tt>: internal error</li>
 *   </ul>
 */
HRESULT CAAAdpCloseSession() ;

#endif
