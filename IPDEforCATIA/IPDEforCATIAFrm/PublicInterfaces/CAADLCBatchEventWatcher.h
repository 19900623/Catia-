/*=======================================================================*/  
/*  COPYRIGHT  DASSAULT  SYSTEMES  2000                              */                                                   
/*=======================================================================*/  
/*                                                                                                                                                                                                                                          */  
/*                                                                                                                            
*    Usage  Notes:													*/
/*          
/*=======================================================================*/  
/*    Creation  Feb        2007                      uhe               */                             
/*=======================================================================*/  
#ifndef  _CAADLCBatchEventWatcher_H  
#define  _CAADLCBatchEventWatcher_H  
   
#include "CATBaseUnknown.h"
#include  "CATEventSubscriber.h"  
#include  "CATBatchPublicDefinitions.h"  

     
class CAADLCBatchEventWatcher  :  public  CATBaseUnknown  
{  
   
     CATDeclareClass;  
     
     public  :  
    
     CAADLCBatchEventWatcher  (int*  cond=NULL);  
     virtual ~CAADLCBatchEventWatcher  ()  ;  
          
     void  SetUUID(char*  uuid);  
           
     int  GetRC()  {return  _rc;}  
                 
   
     void    OnBatchEnd(CATCallbackEvent  iEvt,  void  *iAlarme,  
                        CATNotification    *iNotif,  CATSubscriberData  iData,  
                        CATCallback iIdCbk);  
     
                
     private  :  
           
     int*  _cond;  
     int  _rc;  
     char  _uuid[SIZE_T_ID];  
     
 };  
     
     
#endif  
