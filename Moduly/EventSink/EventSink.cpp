#include "eventsink.h"

void EventSink::InsterLog(CLog *TLog)
{
	Log = TLog;
}

ULONG EventSink::AddRef()
{
	bDone = false;
    return InterlockedIncrement(&m_lRef);
}

ULONG EventSink::Release()
{
    LONG lRef = InterlockedDecrement(&m_lRef);
    if(lRef == 0)
       delete this;
    return lRef;
}

HRESULT EventSink::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown || riid == IID_IWbemObjectSink)
    {
        *ppv = (IWbemObjectSink *) this;
        AddRef();
        return WBEM_S_NO_ERROR;
    }
    else return E_NOINTERFACE;
}


HRESULT EventSink::Indicate(long lObjectCount,
    IWbemClassObject **apObjArray)
{
  HRESULT hr = S_OK;
    _variant_t vtProp;

    for (int i = 0; i < lObjectCount; i++)
    {
        bool CreateorDel = false;
        _variant_t cn;
        hr = apObjArray[i]->Get(_bstr_t(L"__Class"), 0, &cn, 0, 0);
        if (SUCCEEDED(hr))
        {
            wstring LClassStr(cn.bstrVal);
            if (0 == LClassStr.compare(L"__InstanceDeletionEvent") )
            {
				VARIANT varReturnValue;
                // "Deletion"
				Log->WriteTxt("Process Deletion:");
                CreateorDel = true;
				
            }
            else if (0 == LClassStr.compare(L"__InstanceCreationEvent"))
            {
                // "Creation" 
				Log->WriteTxt("Process Creation:");
                CreateorDel = true;
            }
            else
            {
                CreateorDel = false;
                //"Modification "             
            }
        }
        VariantClear(&cn);  

        if (CreateorDel)
        {
            hr = apObjArray[i]->Get(_bstr_t(L"TargetInstance"), 0, &vtProp, 0, 0);
            if (!FAILED(hr))
            {
                IUnknown* str = vtProp;
                hr = str->QueryInterface( IID_IWbemClassObject, reinterpret_cast< void** >( &apObjArray[i] ) );
                if ( SUCCEEDED( hr ) )
                {
                    _variant_t cn;
                    hr = apObjArray[i]->Get( L"Name", 0, &cn, NULL, NULL );
                    if ( SUCCEEDED( hr ) )
                    {

                        if ((cn.vt==VT_NULL) || (cn.vt==VT_EMPTY))
							Log->WriteTxt("Unknown Name process");
                        else
						{
							stringstream Mystream;
							Mystream.clear();
                            Mystream << "Name : " << cn.bstrVal << " ";
							
						}
                    }
                    VariantClear(&cn);              

                    hr = apObjArray[i]->Get( L"Handle", 0, &cn, NULL, NULL );
                    if ( SUCCEEDED( hr ) )
                    {
                        if ((cn.vt==VT_NULL) || (cn.vt==VT_EMPTY))
							Log->WriteTxt("Unknown PID process\n");
                        else
						{
							stringstream Mystream;
							Mystream.clear();
                            Mystream << "With ID : " << cn.bstrVal << endl;
							Log->WriteTxt(Mystream.str());
						}
                    }
                    VariantClear(&cn);

					bDone = true;
						
                }
            }
            VariantClear(&vtProp);
        }

    }

    return WBEM_S_NO_ERROR;
}

HRESULT EventSink::SetStatus(
            /* [in] */ LONG lFlags,
            /* [in] */ HRESULT hResult,
            /* [in] */ BSTR strParam,
            /* [in] */ IWbemClassObject __RPC_FAR *pObjParam
        )
{
    if(lFlags == WBEM_STATUS_COMPLETE)
    {
		stringstream Mystream;
		Mystream.clear();
        Mystream << "Call complete. hResult = 0x"  << hex << hResult << endl ;
		Log->WriteTxt(Mystream.str());
    }
    else if(lFlags == WBEM_STATUS_PROGRESS)
    {	
		Log->WriteTxt("Call in progress.\n");
    }

    return WBEM_S_NO_ERROR;
}   

bool EventSink::DeadSink()
{
	return bDone;
}