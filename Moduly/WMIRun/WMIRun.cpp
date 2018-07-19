#include "WMIRun.h"

CWMIRun::CWMIRun()
{

	CRED_MAX_USERNAME_LENGTH = 513;
	CRED_MAX_CREDENTIAL_BLOB_SIZE = 512;
	CREDUI_MAX_USERNAME_LENGTH = CRED_MAX_USERNAME_LENGTH;
	CREDUI_MAX_PASSWORD_LENGTH = (CRED_MAX_CREDENTIAL_BLOB_SIZE / 2);

	pszName = new wchar_t[CREDUI_MAX_USERNAME_LENGTH+1]; //username
	pszPwd = new wchar_t[CREDUI_MAX_PASSWORD_LENGTH+1]; // password

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
	BSecAdded = false;
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

void CWMIRun::SecPrevAdded(bool Added)
{
	BSecAdded = Added;
}
	
bool CWMIRun::IsSecPrevAdded()
{
	return BSecAdded;
}

int CWMIRun::ConnectWMI( string SComp,string SUser , string SPass, bool Force64, std::string Namespace)
{
	//is not default user login
	if(SUser == "")
	{
		//swprintf(pszName,5, L"%s","user"); //copying c_string to table w_char

		//swprintf(pszPwd,9, L"%s","password"); //copying c_string to table w_char

	}
	else
	{
		swprintf(pszName,SUser.length()+1, L"%s",SUser.c_str()); //conver username to wstring

		swprintf(pszName,SPass.length()+1, L"%s",SPass.c_str()); //conver password to wstring
	}

    BSTR strNetworkResource;

    //To use a WMI remote connection set localconn to false and configure the values of the pszName, pszPwd and the name of the remote machine in strNetworkResource
    //connection rules
	bool localconn = false;

	if(SUser == "")   localconn = true; //is default user who runs application 
	if(SComp == "local")
	{
		wchar_t Local[64];
		for(int i = 0; i < 64; ++i)
		{
			Local[i] = NULL;
		}

		//set namespace
		string SLocal = "\\\\." + Namespace;

		for(int i = 0; i < SLocal.size(); ++i)
		{
			Local[i] = SLocal[i];
		}

		strNetworkResource = Local;
	}
	else 
	{		
		wchar_t Remote[64];
		for(int i = 0; i < 64; ++i)
		{
			Remote[i] = NULL;
		}

		//set computer address and namespace
		string SRemote = "\\\\" + SComp + Namespace;

		for(int i = 0; i < SRemote.size(); ++i)
		{
			Remote[i] = SRemote[i];
		}

		strNetworkResource = Remote;
	}

	//LOG
	{
		stringstream Mystream;
		Mystream.clear();
		Mystream << "Connecting to: " << SComp  << endl;
		Log->WriteTxt(Mystream.str());
	}
	
    COAUTHIDENTITY *userAcct = NULL ;
    COAUTHIDENTITY authIdent;

	// Initialize COM. -----------------------------------------

	 hres =  CoInitializeEx(0, COINIT_APARTMENTTHREADED);
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
	if(!BSecAdded)
	{
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
		BSecAdded = true;
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

	//////////// Connect in native application mode ( in my program it is 32bit app)
	if(!Force64)
	{
		if (localconn)  
			hres = pLoc->ConnectServer(
				 _bstr_t(strNetworkResource),       // Object path of WMI namespace
				 NULL,								// User name. NULL = current user
				 NULL,								// User password. NULL = current
				 0,									// Locale. NULL indicates current
				 NULL,								// Security flags.
				 0,									// Authority (e.g. Kerberos)
				 0,									// Context object
				 &pSvc								// pointer to IWbemServices proxy
				 );
		else
			hres = pLoc->ConnectServer(
				_bstr_t(strNetworkResource),  // Object path of WMI namespace
				_bstr_t(pszName),             // User name
				_bstr_t(pszPwd),              // User password
				NULL,						  // Locale
				NULL,						  // Security flags
				NULL,						  // Authority
				NULL,						  // Context object
				&pSvc						  // IWbemServices proxy
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
	}

	//Force 64bit mode on Client Machine, it help for example read 64bit regitry from 32bit application

	else
	{
		//Creating context object
		IWbemContext *pContext = NULL;
		 hres = CoCreateInstance(CLSID_WbemContext, 0, CLSCTX_INPROC_SERVER, IID_IWbemContext, (LPVOID *) &pContext); 
		 if (FAILED(hres))
		{
			Log->WriteTxt("Can't create contextinstance\n");
		}

		 // set machine architecture and put information about it into context
		VARIANT vArchitecture;
		VariantInit(&vArchitecture);
		V_VT(&vArchitecture) = VT_I4;
		V_INT(&vArchitecture) = 64;

		hres = pContext->SetValue(_bstr_t(L"__ProviderArchitecture"), 0, &vArchitecture);
		VariantClear(&vArchitecture);

		if (localconn)  
			hres = pLoc->ConnectServer(
				 _bstr_t(strNetworkResource),       // Object path of WMI namespace
				 NULL,								// User name. NULL = current user
				 NULL,								// User password. NULL = current
				 0,									// Locale. NULL indicates current
				 NULL,								// Security flags.
				 0,									// Authority (e.g. Kerberos)
				 pContext,							// Context object
				 &pSvc								// pointer to IWbemServices proxy
				 );
		else
			hres = pLoc->ConnectServer(
				_bstr_t(strNetworkResource),  // Object path of WMI namespace
				_bstr_t(pszName),             // User name
				_bstr_t(pszPwd),              // User password
				NULL,						  // Locale
				NULL,						  // Security flags
				NULL,						  // Authority
			   pContext,					  // Context object
				&pSvc						  // IWbemServices proxy
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
	}

	Log->WriteTxt("Connected to " + Namespace + " namespace\n");

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

	CurNamespace = Namespace; //save current namespace name fo later use

	return 0;
}

bool CWMIRun::IsConnected()
{
	return BConnected;
}

std::string CWMIRun::GetCurNamespace()
{
	if(BConnected) return CurNamespace;
	else return ("Not Connected");
}

int CWMIRun::ExecMethod(string SMeth)
{
	if(!BConnected) return 2; //not connected

	 // Use the IWbemServices pointer to make requests of WMI ----

	BSTR MethodName = SysAllocString(L"Create");

    BSTR ClassName = SysAllocString(L"Win32_Process");


    pClass = NULL;

    hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL); //getobject from WMI

    pInParamsDefinition = NULL;

    hres = pClass->GetMethod(MethodName, 0, &pInParamsDefinition, NULL); // get definition object

    pClassInstance = NULL;

    hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance); // get instance

	VARIANT varCommand; // command to run

	VariantInit(&varCommand);

    varCommand.vt = VT_BSTR;

	char buffer[512]; // it must be char* with NULL character at end

	for(int i = 0; i < SMeth.size(); ++i)
	{
		buffer[i] = SMeth[i];
	}

	buffer[SMeth.size()] = NULL; //last character NULL

	bstr_t t = buffer;
	
	varCommand.bstrVal = t.GetBSTR(); //pass command

    hres = pClassInstance->Put(L"CommandLine", 0, &varCommand, 0); //put command in instance

	varCommand.vt = NULL;

    VariantClear(&varCommand); //clear variable

	IWbemCallResult *res = NULL; //shoudl be result
	
	
	// Execute Method
	Log->WriteTxt("Executing: " + SMeth + "\n");
	  
	pOutParams = NULL;

	//Execute methond with command
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
		// Get process ID
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
			 PID = varReturnValue.uintVal;
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
		//get return value, when its executed its always 0
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
			 ReturnVal = varReturnValue.uintVal;
			 Log->WriteTxt(Mystream.str());
			 ReturnVal = varReturnValue.uintVal;
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
    BSTR ParameterName = SysAllocString(L"Reason"); //why terminate

    IWbemClassObject* pClass = NULL;
    hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL); //get object

    IWbemClassObject* pInParamsDefinition = NULL;
    IWbemClassObject* pOutMethod = NULL;
    hres = pClass->GetMethod(MethodName, 0, 
        &pInParamsDefinition, &pOutMethod); //get parameters from method

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
        &pcVal, 0); //put reaseon in parameter

	//LOG
	{
	stringstream Mystream;
	Mystream.clear();
	Mystream << "Terminate process: " << ID << endl;
	Log->WriteTxt(Mystream.str());
	}

    // Execute Terminate Method
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
	return 0;
}

int CWMIRun::Terminate(string Name)
{
	if(!BConnected) return 2; //not connected

	CheckProcess(); // get list of processes

	//get PID of process and terminate
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
	Mystream << "SELECT * FROM __InstanceDeletionEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process' AND TargetInstance.ProcessID = " << ID; //command waiting for deletion
	TempCommand ="";
	TempCommand.clear();

	TempCommand = Mystream.str();
	for(int i = 0; i < TempCommand.size(); ++i)
	{
		buffer[i] = TempCommand[i];
	}

	buffer[TempCommand.size()] = NULL; //command need ends with NULL character
	
	//Query WQL put sink object which waits until process ends
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
		return 1;
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
	Mystream << "SELECT * FROM __InstanceDeletionEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process' AND TargetInstance.Name = " << Name; //command waiting for deletion
	TempCommand ="";
	TempCommand.clear();

	TempCommand = Mystream.str();
	for(int i = 0; i < TempCommand.size(); ++i)
	{
		buffer[i] = TempCommand[i];
	}

	buffer[TempCommand.size()] = NULL;//command need ends with NULL character
	
	//Query WQL put sink object which waits until process ends
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

std::vector<std::string> CWMIRun::GetSubKeysNames(std::string MainKey,std::string SKey)
{
	BSTR MethodName = SysAllocString(L"EnumKey"); //function

	BSTR ClassName = SysAllocString(L"StdRegProv"); // class

	BSTR ArgName1 = SysAllocString(L"hDefKey"); //args names
	BSTR ArgName2 = SysAllocString(L"sSubKeyName"); //args anmes


	IWbemClassObject* pClass = NULL;

	hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL);
	
	IWbemClassObject* pInParamsDefinition = NULL;

	hres = pClass->GetMethod(MethodName, 0, &pInParamsDefinition, NULL);
	
	IWbemClassObject* pClassInstance = NULL;

	hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance);

	//firt argument in method
	VARIANT varArg1;

	VariantInit(&varArg1);

	varArg1.vt = VT_UINT;

	// Which main key connect
	if(MainKey == "HKEY_LOCAL_MACHINE") varArg1.uintVal = (ULONG_PTR)HKEY_LOCAL_MACHINE;

	else if(MainKey == "HKEY_CURRENT_USER")	varArg1.uintVal = (ULONG_PTR)HKEY_CURRENT_USER;

	else if(MainKey == "HKEY_CLASSES_ROOT") varArg1.uintVal = (ULONG_PTR)HKEY_CLASSES_ROOT;

	else if(MainKey == "HKEY_USERS") varArg1.uintVal = (ULONG_PTR)HKEY_USERS;

	else if(MainKey == "HKEY_CURRENT_CONFIG") varArg1.uintVal = (ULONG_PTR)HKEY_CURRENT_CONFIG;

	else varArg1.uintVal = (ULONG_PTR)HKEY_LOCAL_MACHINE; //default

	hres = pClassInstance->Put(ArgName1, 0, &varArg1, 0); //put first argument
	VariantClear(&varArg1);
	varArg1.vt = NULL;

	//second argument in method
	VARIANT varArg2;
	varArg2.vt = VT_BSTR;

	//conversion string to wchar_t / BSTR
	wchar_t Key[128];
	for(int i = 0; i < 128; ++i)
	{
		Key[i] = NULL; //NULL character needed on end
	}

	for(int i = 0; i < SKey.size(); ++i)
	{
		Key[i] = SKey[i];
	}
	varArg2.bstrVal = SysAllocString(Key);
	///////////////////////////////////////

	hres = pClassInstance->Put(ArgName2, 0, &varArg2, 0);
	VariantClear(&varArg2);
	
	IWbemCallResult *res = NULL;

	// Execute Method
	  
	IWbemClassObject* pOutParams = NULL;

	//Execute that method and enuumerate keys
	hres = pSvc->ExecMethod(ClassName, MethodName, 0,

	NULL, pClassInstance, &pOutParams, &res);

	VARIANT varReturnValue;

	std::vector<std::string> Keys;

	//getting safearray of keys names
	hres = pOutParams->Get(L"sNames", 0, &varReturnValue, NULL, 0);

	 if (!FAILED(hres))

    {
	//	BSTR *lista =  new BSTR;
      if ((varReturnValue.vt==VT_NULL) || (varReturnValue.vt==VT_EMPTY))

		  Log->WriteTxt("No subkeys in this path");

      else

      if ((varReturnValue.vt & VT_ARRAY))
	  {
	
		  // get BSTR data from key
		  SAFEARRAY *arr = (varReturnValue.parray);
	 
		  BSTR *Keyval = (BSTR*)(arr->pvData);

		  string str ="";

		  //size of safearray
		  long LowBound, UpBound;
		  SafeArrayGetLBound(arr, 1, &LowBound);
		  SafeArrayGetUBound(arr, 1, &UpBound);
		  long cnt_elements = UpBound - LowBound + 1; 

		  //conversion to string
		  for (int i = 0; i < cnt_elements; ++i)  // iterate through returned values
		  {
			  str = (_com_util::ConvertBSTRToString(Keyval[i]));
			  Keys.push_back(str); //push it in container
			  str = "";
		  }
	  }
      else
		  Log->WriteTxt("Single value?");
		  Keys.push_back(_com_util::ConvertBSTRToString(varReturnValue.bstrVal));

    } 

    VariantClear(&varReturnValue); //clear variable

	return Keys;
}

std::string CWMIRun::GetSringVal(std::string MainKey,std::string SKey,std::string ValName)
{
	BSTR MethodName = SysAllocString(L"GetStringValue"); //function

	BSTR ClassName = SysAllocString(L"StdRegProv"); //class


	BSTR ArgName1 = SysAllocString(L"hDefKey"); //argument 1 name
	BSTR ArgName2 = SysAllocString(L"sSubKeyName"); //argument 2 name
	BSTR ArgName3 = SysAllocString(L"sValueName"); //argument 3 name

	IWbemClassObject* pClass = NULL;

	hres = pSvc->GetObject(ClassName, 0, NULL, &pClass, NULL); //get object
	
	IWbemClassObject* pInParamsDefinition = NULL;

	hres = pClass->GetMethod(MethodName, 0, &pInParamsDefinition, NULL); //get parameters
	
	IWbemClassObject* pClassInstance = NULL;

	hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance);

	//first argument in method
	VARIANT varArg1;

	VariantInit(&varArg1);

	varArg1.vt = VT_UINT;
		
	//set main key to connect
	if(MainKey == "HKEY_LOCAL_MACHINE") varArg1.uintVal = (ULONG_PTR)HKEY_LOCAL_MACHINE;

	else if(MainKey == "HKEY_CURRENT_USER")	varArg1.uintVal = (ULONG_PTR)HKEY_CURRENT_USER;

	else if(MainKey == "HKEY_CLASSES_ROOT") varArg1.uintVal = (ULONG_PTR)HKEY_CLASSES_ROOT;

	else if(MainKey == "HKEY_USERS") varArg1.uintVal = (ULONG_PTR)HKEY_USERS;

	else if(MainKey == "HKEY_CURRENT_CONFIG") varArg1.uintVal = (ULONG_PTR)HKEY_CURRENT_CONFIG;

	else varArg1.uintVal = (ULONG_PTR)HKEY_LOCAL_MACHINE; //default

	hres = pClassInstance->Put(ArgName1, 0, &varArg1, 0); //put first argument
	VariantClear(&varArg1);

	//second argument in method
	VARIANT varArg2;
	varArg2.vt = VT_BSTR;

	//conversion string to wchar_t / BSTR
	wchar_t Key[128];
	for(int i = 0; i < 128; ++i)
	{
		Key[i] = NULL; //NULL at end needed
	}

	for(int i = 0; i < SKey.size(); ++i)
	{
		Key[i] = SKey[i];
	}
	varArg2.bstrVal = SysAllocString(Key);
	///////////////////////////////////////

	hres = pClassInstance->Put(ArgName2, 0, &varArg2, 0); //second argument (subkey path)
	VariantClear(&varArg2);

	//third argument in method
	VARIANT varArg3;
	varArg3.vt = VT_BSTR;

	//conversion string to wchar_t / BSTR
	wchar_t Value[128];
	for(int i = 0; i < 128; ++i)
	{
		Value[i] = NULL;//NULL at end needed
	}

	for(int i = 0; i < ValName.size(); ++i)
	{
		Value[i] = ValName[i];
	}
	varArg3.bstrVal = SysAllocString(Value);
	///////////////////////////////////////

	hres = pClassInstance->Put(ArgName3, 0, &varArg3, 0); // put third argumernt value name from each get its value
	VariantClear(&varArg3);

	IWbemCallResult *res = NULL;

	// Execute Method
	  
	IWbemClassObject* pOutParams = NULL;

	// execute method (get string of key value 
	hres = pSvc->ExecMethod(ClassName, MethodName, 0,

	NULL, pClassInstance, &pOutParams, &res);

	VARIANT varReturnValue;

	std::vector<std::wstring> Keys;

	//get values from out parameters
	hres = pOutParams->Get(L"sValue", 0, &varReturnValue, NULL, 0);

	if (!FAILED(hres))

    {
	//	if value its empty or have null value
      if ((varReturnValue.vt==VT_NULL) || (varReturnValue.vt==VT_EMPTY))
	  {
		  return "";
	  }
      else if ((varReturnValue.vt & VT_ARRAY))
	  {
		  Log->WriteTxt("Key value in array not supported\n");
	  }
      else
	  {
		 string str = (_com_util::ConvertBSTRToString(varReturnValue.bstrVal));
		 return str;
	  }
    } 

}

UINT CWMIRun::GetLastPID()
{
	return PID;
}

UINT CWMIRun::GetLatReturnWMIVal()
{
	return ReturnVal;
}

std::string CWMIRun::Getloc()
{
	return localization;
}

void CWMIRun::EndWait()
{
	if(BConnected) hres = pSvc->CancelAsyncCall(pSink); //stop waiting
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

	//Query WQL for Win32_Process class content, it means processes
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
   
	//enumerate processes
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

		ProcessInfo.push_back(TempProcessInfo); // push to container

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

	//query WQL for info about operating system
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
   
	//enumerate system info structure fields
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
   
	//enumerate all disks stuctures
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, 
            &pclsObj, &uReturn);

        if(0 == uReturn)
        {
            break; //when reach end
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

		DiskInfo.push_back(TempDiskInfo); //push all info to container

        pclsObj->Release();
        pclsObj = NULL;
    }

	pEnumerator->Release();

	return 0;
}