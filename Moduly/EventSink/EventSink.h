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

   void InsterLog(CLog *TLog);

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();        
    virtual HRESULT 
        STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);

    virtual HRESULT STDMETHODCALLTYPE Indicate( 
            LONG lObjectCount,
            IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray
            );
        
    virtual HRESULT STDMETHODCALLTYPE SetStatus( 
            /* [in] */ LONG lFlags,
            /* [in] */ HRESULT hResult,
            /* [in] */ BSTR strParam,
            /* [in] */ IWbemClassObject __RPC_FAR *pObjParam
            );

	bool DeadSink();

	private:
	CLog *Log;

	//Q_OBJECT
    LONG m_lRef;
    bool bDone;

};

#endif