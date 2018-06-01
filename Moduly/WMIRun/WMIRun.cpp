#include "WMIRun.h"

CWMIRun::CWMIRun()
{

	CRED_MAX_USERNAME_LENGTH = 513;
	CRED_MAX_CREDENTIAL_BLOB_SIZE = 512;
	CREDUI_MAX_USERNAME_LENGTH = CRED_MAX_USERNAME_LENGTH;
	CREDUI_MAX_PASSWORD_LENGTH = (CRED_MAX_CREDENTIAL_BLOB_SIZE / 2);

	pszName = new wchar_t[CREDUI_MAX_USERNAME_LENGTH+1];
	pszPwd = new wchar_t[CREDUI_MAX_PASSWORD_LENGTH+1];

	pSvc = nullptr;
	pLoc = nullptr;
	Log = nullptr;
	pClass = nullptr;
	pInParamsDefinition = nullptr;
	pClassInstance = nullptr;
	pOutParams = nullptr;
	pUnsecApp = nullptr;
	pSink = nullptr;
	pStubUnk = nullptr;
	pStubSink = nullptr;

	BConnected = false;
}

CWMIRun::~CWMIRun()
{
	delete[] pszName;
	delete[] pszPwd;
	Free();
}

void CWMIRun::InsertLog(CLog *Tlog)
{
	Log = Tlog;
}

int CWMIRun::ConnectWMI( string SComp,string SUser , string SPass)
{
	//local user logon check
	if(SUser == "")
	{
		//swprintf(pszName,5, L"%s","user"); //copying c_string to table w_char

		//swprintf(pszPwd,9, L"%s","password"); //copying c_string to table w_char

	}
	else
	{
		swprintf(pszName,SUser.length()+1, L"%s",SUser.c_str());

		swprintf(pszName,SPass.length()+1, L"%s",SPass.c_str());
	}

    BSTR strNetworkResource;

    //To use a WMI remote connection set localconn to false and configure the values of the pszName, pszPwd and the name of the remote machine in strNetworkResource
    //connection rules
	bool localconn = false;

	if(SUser == "")   localconn = true; //user who runs application
	if(SComp == "local")  strNetworkResource =  L"\\\\.\\root\\CIMV2";
	else 
	{		
		wchar_t Remote[20];
		string SRemote = "\\\\" + SComp +  "\\root\\CIMV2";
		swprintf(Remote,SRemote.length()+1, L"%s",SRemote.c_str());
		strNetworkResource = Remote;
	}

	//LOG
	{
		stringstream Mystream;
		Mystream.clear();
		Mystream << "Connecting to: " << strNetworkResource << endl;
		Log->WriteTxt(Mystream.str());
	}
	
    COAUTHIDENTITY *userAcct = NULL ;
    COAUTHIDENTITY authIdent;

	// Initialize COM. -----------------------------------------

	 hres =  CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();
        Mystream << "Failed to initialize COM library. Error code = 0x" << hex << hres << endl;
        Mystream << _com_error(hres).ErrorMessage() << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());
   
        return 1;                  // Program has failed.
    }

    // Set general COM security levels --------------------------

    if (localconn)
        hres =  CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities
            NULL                         // Reserved
            );
    else
        hres =  CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
            RPC_C_IMP_LEVEL_IDENTIFY,    // Default Impersonation
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities
            NULL                         // Reserved
            );

    if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();
        Mystream << "Failed to initialize security. Error code = 0x" << hex << hres << endl;
        Mystream << _com_error(hres).ErrorMessage() << endl;			
		Log->WriteTxt(Mystream.str());

        CoUninitialize();
  
        return 1;                    // Program has failed.
    }

	 // Obtain the initial locator to WMI -------------------------

    pLoc = NULL;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pLoc);

    if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();
        Mystream << "Failed to create IWbemLocator object." << " Err code = 0x" << hex << hres << endl;
        Mystream << _com_error(hres).ErrorMessage() << endl;
		Log->WriteTxt(Mystream.str());

        CoUninitialize();       
 
        return 1;                 // Program has failed.
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method

    pSvc = NULL;

    if (localconn)  
        hres = pLoc->ConnectServer(
             _bstr_t(strNetworkResource),      // Object path of WMI namespace
             NULL,                    // User name. NULL = current user
             NULL,                    // User password. NULL = current
             0,                       // Locale. NULL indicates current
             NULL,                    // Security flags.
             0,                       // Authority (e.g. Kerberos)
             0,                       // Context object
             &pSvc                    // pointer to IWbemServices proxy
             );
    else
        hres = pLoc->ConnectServer(
            _bstr_t(strNetworkResource),  // Object path of WMI namespace
            _bstr_t(pszName),             // User name
            _bstr_t(pszPwd),              // User password
            NULL,                // Locale
            NULL,                // Security flags
            NULL,                // Authority
            NULL,                // Context object
            &pSvc                // IWbemServices proxy
            );

    if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();		
        Mystream << "Could not connect. Error code = 0x" << hex << hres << endl;    
        Mystream << _com_error(hres).ErrorMessage() << endl;
		Log->WriteTxt(Mystream.str());

        pLoc->Release();
        CoUninitialize();
          
        return 1;                // Program has failed.
    }

	Log->WriteTxt("Connected to root\\CIMV2 WMI namespace\n");

    // Set security levels on the proxy -------------------------
    if (localconn)
        hres = CoSetProxyBlanket(
           pSvc,                        // Indicates the proxy to set
           RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
           RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
           NULL,                        // Server principal name
           RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
           RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
           NULL,                        // client identity
           EOAC_NONE                    // proxy capabilities
        );
    else
    {
        // Create COAUTHIDENTITY that can be used for setting security on proxy
        memset(&authIdent, 0, sizeof(COAUTHIDENTITY));
        authIdent.PasswordLength = wcslen (pszPwd);
        authIdent.Password = (USHORT*)pszPwd;
        authIdent.User = (USHORT*)pszName;
        authIdent.UserLength = wcslen(pszName);
        authIdent.Domain = 0;
        authIdent.DomainLength = 0;
        authIdent.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
        userAcct = &authIdent;

        hres = CoSetProxyBlanket(
           pSvc,                           // Indicates the proxy to set
           RPC_C_AUTHN_DEFAULT,            // RPC_C_AUTHN_xxx
           RPC_C_AUTHZ_DEFAULT,            // RPC_C_AUTHZ_xxx
           COLE_DEFAULT_PRINCIPAL,         // Server principal name
           RPC_C_AUTHN_LEVEL_PKT_PRIVACY,  // RPC_C_AUTHN_LEVEL_xxx
           RPC_C_IMP_LEVEL_IMPERSONATE,    // RPC_C_IMP_LEVEL_xxx
           userAcct,                       // client identity
           EOAC_NONE                       // proxy capabilities
        );
    }

    if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();		
        Mystream << "Could not set proxy blanket. Error code = 0x" << hex << hres << endl;
        Mystream << _com_error(hres).ErrorMessage() << endl;
		Log->WriteTxt(Mystream.str());

        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
     
        return 1;               // Program has failed.
    }

	BConnected = true;
	localization = SComp;

	//LOG
	{
		stringstream Mystream;
		Mystream.clear();
		Mystream << "Connected to: " << SComp << endl;
		Log->WriteTxt(Mystream.str());
	}

	return 0;
}

int CWMIRun::ExecMethod(string SMeth)
{
	if(!BConnected) return 2; //not connected

	 // Use the IWbemServices pointer to make requests of WMI ----

	BSTR MethodName = SysAllocString(L"Create");

    BSTR ClassName = SysAllocString(L"Win32_Process");


    pClass = NULL;

    hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL);

    pInParamsDefinition = NULL;

    hres = pClass->GetMethod(MethodName, 0, &pInParamsDefinition, NULL);

    pClassInstance = NULL;

    hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance);

	VARIANT varCommand;

	VariantInit(&varCommand);

    varCommand.vt = VT_BSTR;

	char buffer[512];

	for(int i = 0; i < SMeth.size(); ++i)
	{
		buffer[i] = SMeth[i];
	}

	buffer[SMeth.size()] = NULL;

	bstr_t t = buffer;
	
	varCommand.bstrVal = t.GetBSTR();//execute command

    hres = pClassInstance->Put(L"CommandLine", 0, &varCommand, 0); //instance of coomand

	varCommand.vt = NULL;

    VariantClear(&varCommand);

	IWbemCallResult *res = NULL;
	
	
	// Execute Method
	Log->WriteTxt("Executing: " + SMeth + "\n");
	  
	pOutParams = NULL;

	hres = pSvc->ExecMethod(ClassName, MethodName, 0,

	NULL, pClassInstance, &pOutParams, &res);

	Sleep(10);

	if (FAILED(hres))

	{

		stringstream Mystream;
		Mystream.clear();
		Mystream << "Could not execute method. Error code = 0x" << hex << hres << endl;
		Mystream << _com_error(hres).ErrorMessage() << endl;
		Log->WriteTxt(Mystream.str());

		SysFreeString(ClassName);

		SysFreeString(MethodName);

		if (pClass)			

		pClass->Release();

		if (pInParamsDefinition)			

		pInParamsDefinition->Release();

		if (pOutParams)			

		pOutParams->Release();

		if (pSvc)			

		pSvc->Release();

		if (pLoc)			

		pLoc->Release();     

		CoUninitialize();	

		return 1;               // Program has failed.

	}
	Log->WriteTxt(SMeth + " executed properly\n");
	//getting info about running process
    VARIANT varReturnValue;
	pOutParams->Get(L"ProcessId", 0, &varReturnValue, NULL, 0);

    if (!FAILED(hres))

    {

      if ((varReturnValue.vt==VT_NULL) || (varReturnValue.vt==VT_EMPTY))
	  {
		  //Dont have any PID
		  stringstream Mystream;
		  Mystream.clear();
		  Mystream << "ProcessId : " << ((varReturnValue.vt==VT_NULL) ? "NULL" : "EMPTY") << endl;
		  Mystream << _com_error(hres).ErrorMessage() << endl;
		  Log->WriteTxt(Mystream.str());
		  PID = NULL;
	  }
      else		
	  {
		 if ((varReturnValue.vt & VT_ARRAY))
		{
			//ID in Array?
			 stringstream Mystream;
			 Mystream.clear();
			 Mystream << "ProcessId : " << "Array types not supported (yet)" << endl;
		     Mystream << _com_error(hres).ErrorMessage() << endl;
			 Log->WriteTxt(Mystream.str());
			 PID = NULL;
		}
		 else
		 {
			 //everything OK
			 stringstream Mystream;
			 Mystream.clear();
			 Mystream << "ProcessId : " << varReturnValue.uintVal << endl;
			 Log->WriteTxt(Mystream.str());
			 PID = varReturnValue.uintVal;
		 }
		
	  }
      
	   VariantClear(&varReturnValue);
    }  

	// return value of running process

    hres = pOutParams->Get(L"ReturnValue", 0, &varReturnValue, NULL, 0);

    if (!FAILED(hres))

    {

      if ((varReturnValue.vt==VT_NULL) || (varReturnValue.vt==VT_EMPTY))
	  {
		  //Dont have any value
		  stringstream Mystream;
		  Mystream.clear();
		  Mystream << "ReturnValue : " << ((varReturnValue.vt==VT_NULL) ? "NULL" : "EMPTY") << endl;
		  Mystream << _com_error(hres).ErrorMessage() << endl;
		  Log->WriteTxt(Mystream.str());
		  ReturnVal = NULL;
	  }
      else		
	  {
		 if ((varReturnValue.vt & VT_ARRAY))
		{
			//Value in Array?
			 stringstream Mystream;
			 Mystream.clear();
			 Mystream << "ReturnValue : " << "Array types not supported (yet)" << endl;
		     Mystream << _com_error(hres).ErrorMessage() << endl;
			 Log->WriteTxt(Mystream.str());
			 ReturnVal = NULL;
		}
		 else
		 {
			 //everything OK
			 stringstream Mystream;
			 Mystream.clear();
			 Mystream << "ReturnValue : " << varReturnValue.uintVal << endl;
			 Log->WriteTxt(Mystream.str());
			 ReturnVal = varReturnValue.uintVal;
		 }
		
	  }
      
	   VariantClear(&varReturnValue);

	}

	 hres = pOutParams->Get(L"Name", 0, &varReturnValue, NULL, 0);

    if (!FAILED(hres))

    {

      if ((varReturnValue.vt==VT_NULL) || (varReturnValue.vt==VT_EMPTY))
	  {
		  //Dont have any value
		  stringstream Mystream;
		  Mystream.clear();
		  Mystream << "Name : " << ((varReturnValue.vt==VT_NULL) ? "NULL" : "EMPTY") << endl;
		  Mystream << _com_error(hres).ErrorMessage() << endl;
		  Log->WriteTxt(Mystream.str());
		  Name = "";
	  }
      else		
	  {
		 if ((varReturnValue.vt & VT_ARRAY))
		{
			//Value in Array?
			 stringstream Mystream;
			 Mystream.clear();
			 Mystream << "Name : " << "Array types not supported (yet)" << endl;
		     Mystream << _com_error(hres).ErrorMessage() << endl;
			 Log->WriteTxt(Mystream.str());
			 Name = "";
		}
		 else
		 {
			 //everything OK
			 stringstream Mystream;
			 Mystream.clear();
			 Mystream << "Name : " << varReturnValue.bstrVal << endl;
			 Log->WriteTxt(Mystream.str());
			 Name = _com_util::ConvertBSTRToString(varReturnValue.bstrVal);
		 }
		
	  }
      
	   VariantClear(&varReturnValue);	

	}

	//clrear memory
	SysFreeString(ClassName);

    SysFreeString(MethodName);


	return hres;
}
	
int CWMIRun::Terminate(UINT ID)
{
	if(!BConnected) return 2; //not connected

		 // Set up to call the Win32_Process::Create method
    BSTR ClassName = SysAllocString(L"Win32_Process");

	//PID what contains path to application that be terminated
	stringstream Mystream;
	Mystream.clear();
	Mystream << "Win32_Process.Handle=\"" << ID << "\"";
	string Tempstring = Mystream.str();
	Mystream.clear();
	bstr_t temp = Tempstring.c_str();


    BSTR ClassNameInstance = SysAllocString(temp);

    _bstr_t MethodName = (L"Terminate");
    BSTR ParameterName = SysAllocString(L"Reason");

    IWbemClassObject* pClass = NULL;
    hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL);

    IWbemClassObject* pInParamsDefinition = NULL;
    IWbemClassObject* pOutMethod = NULL;
    hres = pClass->GetMethod(MethodName, 0, 
        &pInParamsDefinition, &pOutMethod);

    if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();		
        Mystream << "Could not get the method. Error code = 0x" 
             << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());
    }

    IWbemClassObject* pClassInstance = NULL;
    hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance);

    // Create the values for the in parameters
    VARIANT pcVal;
    VariantInit(&pcVal);
    V_VT(&pcVal) = VT_I4;

    // Store the value for the in parameters
    hres = pClassInstance->Put(L"Reason", 0,
        &pcVal, 0);

	//LOG
	{
	stringstream Mystream;
	Mystream.clear();
	Mystream << "Terminate process: " << ID << endl;
	Log->WriteTxt(Mystream.str());
	}

    // Execute Method
    hres = pSvc->ExecMethod(ClassNameInstance, MethodName, 0,
    NULL, pClassInstance, NULL, NULL);

    if (FAILED(hres))
    {

		stringstream Mystream;
		Mystream.clear();		
        Mystream << "Could not execute method. Error code = 0x" 
             << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());   

        VariantClear(&pcVal);
        SysFreeString(ClassName);
        SysFreeString(MethodName);
        pClass->Release();
        pInParamsDefinition->Release();
        pSvc->Release();
        pLoc->Release();     
        CoUninitialize();
        return 1;           // Program has failed.
    }
	//LOG
	{
	stringstream Mystream;
	Mystream.clear();
	Mystream << "Terminate process: " << ID << " ended succesfully" << endl;
	Log->WriteTxt(Mystream.str());
	}
}

int CWMIRun::Terminate(string Name)
{
	if(!BConnected) return 2; //not connected

	CheckProcess();
	for(int i = 0; i < ProcessInfo.size(); ++i)
	{
		if(ProcessInfo[i].Name == Name) Terminate(ProcessInfo[i].PID);
	}
	return 0;
}

int CWMIRun::WaitExeEnd(UINT ID)
{
	if(!BConnected) return 2; //not connected

	pUnsecApp = NULL;

	hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL, CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, (void**)&pUnsecApp);
 
	pSink = new EventSink;
	pSink->AddRef();
	pSink->InsterLog(Log);

	pStubUnk = NULL; 
	pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

	pStubSink = NULL;
	pStubUnk->QueryInterface(IID_IWbemObjectSink,
	(void **) &pStubSink);

	char buffer[512];	// WQL command
	
	std::stringstream Mystream; // stream for conversion ProcessId variable
	Mystream.clear();

	std::string TempCommand; //temporary string for command 
	Mystream.clear();
	Mystream << "SELECT * FROM __InstanceDeletionEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process' AND TargetInstance.ProcessID = " << ID;
	TempCommand ="";
	TempCommand.clear();

	TempCommand = Mystream.str();
	for(int i = 0; i < TempCommand.size(); ++i)
	{
		buffer[i] = TempCommand[i];
	}

	buffer[TempCommand.size()] = NULL;
	
	hres = pSvc->ExecNotificationQueryAsync(_bstr_t("WQL"), 
		_bstr_t(buffer), 
		WBEM_FLAG_SEND_STATUS, 
		NULL,pStubSink);
	if (FAILED(hres)) 
	{
		stringstream Mystream;
		Mystream.clear();		
        Mystream << "ExecNotificationQueryAsync failed with = 0x" << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());   
        //throw std::exception("CreationEvent initialization failed");
    }

	return 0;
}

int CWMIRun::WaitExeEnd(string Name)
{
	if(!BConnected) return 2; //not connected

	pUnsecApp = NULL;

	hres = CoCreateInstance(CLSID_UnsecuredApartment, NULL, CLSCTX_LOCAL_SERVER, IID_IUnsecuredApartment, (void**)&pUnsecApp);
 
	pSink = new EventSink;
	pSink->AddRef();

	pStubUnk = NULL; 
	pUnsecApp->CreateObjectStub(pSink, &pStubUnk);

	pStubSink = NULL;
	pStubUnk->QueryInterface(IID_IWbemObjectSink,
	(void **) &pStubSink);

	char buffer[512];	// WQL command
	
	std::stringstream Mystream; // stream for conversion ProcessId variable
	Mystream.clear();

	std::string TempCommand; //temporary string for command 
	Mystream.clear();
	Mystream << "SELECT * FROM __InstanceDeletionEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process' AND TargetInstance.Name = " << Name;
	TempCommand ="";
	TempCommand.clear();

	TempCommand = Mystream.str();
	for(int i = 0; i < TempCommand.size(); ++i)
	{
		buffer[i] = TempCommand[i];
	}

	buffer[TempCommand.size()] = NULL;
	
	hres = pSvc->ExecNotificationQueryAsync(_bstr_t("WQL"), 
		_bstr_t(buffer), 
		WBEM_FLAG_SEND_STATUS, 
		NULL,pStubSink);
	if (FAILED(hres)) 
	{
		stringstream Mystream;
		Mystream.clear();		
        Mystream << "ExecNotificationQueryAsync failed with = 0x" << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());   
       // throw std::exception("CreationEvent initialization failed");
    }

	return 0;
}

bool CWMIRun::IsProcessDead()
{
	if(!BConnected) return false; //not connected
	return pSink ->DeadSink();
}

std::vector<SDiskInfo> CWMIRun::GetDiskInfo()
{
	if(!BConnected) ; //not connected
	else CheckDiskinfo();
	return DiskInfo;
}

SSysInfo CWMIRun::GetSysInfo()
{
	if(!BConnected); //not connected
	else CheckSys();
	return SysInfo;
}

std::vector<SProcessInfo> CWMIRun::GetProcessInfo()
{
	if(!BConnected); //not connected
	else CheckProcess();
	return ProcessInfo;
}

void CWMIRun::EndWait()
{
	if(BConnected) hres = pSvc->CancelAsyncCall(pSink);
}

void CWMIRun::Free()
{
	  // Clean up    
	if(!BConnected) ; //not connected
	else
	{

		if((pClass != NULL) && (pClass != nullptr) ) pClass->Release();

		if((pInParamsDefinition != NULL) && (pInParamsDefinition != nullptr) ) pInParamsDefinition->Release();

		if((pOutParams != NULL) && (pOutParams != nullptr) ) pOutParams->Release();

		if((pLoc != NULL) && (pLoc != nullptr) ) pLoc->Release();

		if((pSvc != NULL) && (pSvc != nullptr) ) pSvc->Release();

		if((pUnsecApp != NULL) && (pUnsecApp != nullptr) ) pUnsecApp->Release();

		if((pStubUnk != NULL) && (pStubUnk != nullptr) ) pStubUnk->Release();

		if((pSink != NULL) && (pSink != nullptr) ) pSink->Release();

		if((pStubSink != NULL) && (pStubSink != nullptr) ) pStubSink->Release();

		CoUninitialize(); 

		if(!DiskInfo.empty()) DiskInfo.clear();
		if(!ProcessInfo.empty()) ProcessInfo.clear();
		Log->WriteTxt("Disconected succesfully from: " + localization);
		localization = "";
		localization.clear();
	}
}

int CWMIRun::CheckProcess()
{
	if(!BConnected) return 2; //not connected

	Log->WriteTxt("Processes checking");

	// For example, get the name of the system process
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Process"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
    {
		stringstream Mystream;
		Mystream.clear();		
        Mystream << "Query for Processes failed." << " Error code = 0x"  << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());   

        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }

	IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
   
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
            &pclsObj, &uReturn);

        if(0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

		SProcessInfo TempProcessInfo;

        // Get the value of the Name property
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if(!hr)TempProcessInfo.Name = _com_util::ConvertBSTRToString(vtProp.bstrVal); //convetrs BSTR to char*

        // Get the value of the ProcessID property
        hr = pclsObj->Get(L"ProcessID", 0, &vtProp, 0, 0);
		if(!hr)TempProcessInfo.PID = vtProp.uintVal;

		//Get the value of the SessionID property
		 hr = pclsObj->Get(L"SessionID", 0, &vtProp, 0, 0);
		if(!hr)TempProcessInfo.SID = (vtProp.uintVal);

        VariantClear(&vtProp);

		ProcessInfo.push_back(TempProcessInfo);

        pclsObj->Release();
        pclsObj = NULL;
    }

	pEnumerator->Release();

	return 0;
}

int CWMIRun::CheckSys()
{
	if(!BConnected) return 2; //not connected

	Log->WriteTxt("System checking");

	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_OperatingSystem"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
    {
       stringstream Mystream;
		Mystream.clear();		
        Mystream << "Query for operating system name failed." << " Error code = 0x"  << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());   

        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }

	IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
   
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
            &pclsObj, &uReturn);

        if(0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        // Get the value of the Caption property, there is space after System Caption
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		if(!hr)SysInfo.Name = _com_util::ConvertBSTRToString(vtProp.bstrVal);
		
		// Get the value of the CSDVersion property | service pack
		hr = pclsObj->Get(L"CSDVersion", 0, &vtProp, 0, 0);
		if(!hr)SysInfo.SP = _com_util::ConvertBSTRToString(vtProp.bstrVal);

        // Get the value of the FreePhysicalMemory property
		hr = pclsObj->Get(L"FreePhysicalMemory", 0, &vtProp, 0, 0);
		if(!hr)SysInfo.FreeMem = vtProp.uintVal;

		// Get the value of the OSArchitecture property
		hr = pclsObj->Get(L"OSArchitecture", 0, &vtProp, 0, 0);
		if(!hr)SysInfo.OSArch =  _com_util::ConvertBSTRToString(vtProp.bstrVal);

		// Get the value of the OSLanguage property
		hr = pclsObj->Get(L"OSLanguage", 0, &vtProp, 0, 0);
		if(!hr)SysInfo.Lang = vtProp.uintVal;

		// Get the value of the OSType property | 18 is WinNT
		hr = pclsObj->Get(L"OSType", 0, &vtProp, 0, 0);
		if(!hr)SysInfo.Type = vtProp.uintVal;


        VariantClear(&vtProp);

        pclsObj->Release();
        pclsObj = NULL;
    }

	pEnumerator->Release();

	return 0;
}

int CWMIRun::CheckDiskinfo()
{
	if(!BConnected) return 2; //not connected

	Log->WriteTxt("Disk checking\n");

	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_LogicalDisk"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
    {
        stringstream Mystream;
		Mystream.clear();		
        Mystream << "Query for Disk Info failed." << " Error code = 0x"  << hex << hres << endl;
		Mystream.clear();
		Log->WriteTxt(Mystream.str());   
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }

	IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
   
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
            &pclsObj, &uReturn);

        if(0 == uReturn)
        {
            break;
        }

		SDiskInfo TempDiskInfo;

        VARIANT vtProp;

        // Get the value of the Caption property
        hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
        if(!hr)TempDiskInfo.Caption =  _com_util::ConvertBSTRToString(vtProp.bstrVal);

		// Get the value of the DriveType property
		hr = pclsObj->Get(L"DriveType", 0, &vtProp, 0, 0);
		if(!hr)TempDiskInfo.DriveType = vtProp.uintVal;

        // Get the value of the ErrorCleaned property
		//hr = pclsObj->Get(L"ErrorCleaned", 0, &vtProp, 0, 0);
      //  wcout << "ErrorCleaned : " << vtProp.boolVal << endl;

		// Get the value of the LastErrorCode property
		hr = pclsObj->Get(L"LastErrorCode", 0, &vtProp, 0, 0);
        if(!hr)TempDiskInfo.LastError = vtProp.uintVal;

		// Get the value of the FreeSpace property
		hr = pclsObj->Get(L"FreeSpace", 0, &vtProp, 0, 0);
        if(!hr)TempDiskInfo.FreeSpace = vtProp.uintVal;

		// Get the value of the Name property
		hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if(!hr)TempDiskInfo.Name = _com_util::ConvertBSTRToString(vtProp.bstrVal);

        VariantClear(&vtProp);

		DiskInfo.push_back(TempDiskInfo);

        pclsObj->Release();
        pclsObj = NULL;
    }

	pEnumerator->Release();

	return 0;
}