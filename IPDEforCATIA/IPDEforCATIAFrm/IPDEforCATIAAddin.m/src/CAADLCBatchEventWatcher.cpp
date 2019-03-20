//------------------------------------------------------------------  
//  COPYRIGHT  DASSAULT  SYSTEMES  2006     
    
/**  
*    
*/  
#include  "CAADLCBatchEventWatcher.h"  
#include  "CATBatchAccessCAA.h"  
#include  "CATBatchEndNotifCAA.h"  
#include  "CATBatchNotif.h"  
#include  "CATBatClientMonitorCAA.h"

 CATImplementClass(  CAADLCBatchEventWatcher,  Implementation,  CATBaseUnknown,  CATNull  );  

 ///////////////////////////////////CDTORS///////////////////////////////  
 CAADLCBatchEventWatcher::CAADLCBatchEventWatcher(int*  cond)  :  _cond(cond),  _rc(99) 
 {  
    CATBaseUnknown*  pub  =  GetBatchPublisherCAA();  
            
   memset(_uuid,  '\0',  SIZE_T_ID);  
       
             
   ::AddCallback(this,  pub,  CATBatchEndNotifCAA::ClassName(),    
                             (CATSubscriberMethod)&CAADLCBatchEventWatcher::OnBatchEnd,  NULL);  
 }

 //////////////////////////////////DTOR////////////////////////////////////  
 CAADLCBatchEventWatcher::~CAADLCBatchEventWatcher  ()    
 {         
    _cond  =  NULL;           
  }  
 ///////////////////////////////////////////////////////////////////////////  
 void  CAADLCBatchEventWatcher::SetUUID(char*  uuid)  
 {  
     if  (uuid)  
    {  
       strncpy(_uuid,  uuid,  SIZE_T_ID);  
    }  
            
 }  
  ///////////////////////////////////////////////////////////////////////////  
 void    CAADLCBatchEventWatcher::OnBatchEnd(CATCallbackEvent  iEvt,  void  *iAlarme,  
                                          CATNotification    *iNotif,  CATSubscriberData  iDonnees,  
                                                               CATCallback iIdCbk)  
 {  
       
   CATBatchNotif*  batch_notif  =  (CATBatchNotif*)iNotif;  
   if  (!batch_notif)        return;  
   
   char*  uuid  =  batch_notif->GetBatchUUID();  
             
   if  (!strncmp(uuid,  _uuid,  SIZE_T_ID))  
   {    
     CATBatClientMonitorCAA*  cm    =  CATBatClientMonitorCAA::GetTheClientMonitorCAA();  
     if  (!cm)        return;  
                                    
     CATBatchStatus  status;  
     HRESULT  hr  =  cm->GetBatchStatus(uuid,  status);  
     if  (FAILED(hr))        return;  
                             
     hr  =  cm->GetBatchRC(uuid,  _rc);  
                             
     if  (FAILED(hr))        return;  
                             
     *_cond  =  1;  
   }  
              
}  
    




