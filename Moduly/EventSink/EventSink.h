#ifndef EventSink_h
#define EventSink_h

#define _WIN32_DCOM

# pragma comment(lib, "wbemuuid.lib")

#include <comdef.h>
#include <Wbemidl.h>
#include <sstream>
#include "Log.h"

using namespace std;

class EventSink : public IWbemObjectSink/*,public QWidget*/
{

public:
   
	EventSink() { m_lRef = 0; }
   ~EventSink() { bDone = true; }

   // insert log file
   void InsterLog(CLog *TLog);

   //gets reference to sink object
   virtual ULONG STDMETHODCALLTYPE AddRef();
   
   // release all objects
   virtual ULONG STDMETHODCALLTYPE Release();        
   
   // query interface
   virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

   // functions which takes place when program is running and check its status for take data from it
   virtual HRESULT STDMETHODCALLTYPE Indicate( 
            LONG lObjectCount,
            IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray
            );
        
   //sets program status and gives object
   virtual HRESULT STDMETHODCALLTYPE SetStatus( 
            /* [in] */ LONG lFlags,
            /* [in] */ HRESULT hResult,
            /* [in] */ BSTR strParam,
            /* [in] */ IWbemClassObject __RPC_FAR *pObjParam
            );

   // return true if program was ended
	bool DeadSink();

private:

	//Log file pointer
	CLog *Log;

	//Q_OBJECT
    LONG m_lRef;

	//when program finish its wiork
    bool bDone;

};

#endif