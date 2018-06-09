#ifndef WMIRun_h
#define WMIRun_h

// 0 - Successful completion.

// 2 - The user does not have access to the requested information.

// 3 - The user does not have sufficient privilge.

// 8 - Unknown failure.

// 9 - The path specified does not exist.

// 21 - The specified parameter is invalid.


//CREDENTIAL structure
//http://msdn.microsoft.com/en-us/library/windows/desktop/aa374788%28v=vs.85%29.aspx

#define _WIN32_DCOM

#pragma comment(lib, "wbemuuid.lib")

#include <comdef.h>
#include <Wbemidl.h>
#include <sstream>
#include <string>
#include <Windows.h>
#include <vector>
#include "EventSink.h"
#include "DiskInfo.h"
#include "SysInfo.h"
#include "ProcessInfo.h"

using namespace std;


class CWMIRun

{
public:

	CWMIRun();
	~CWMIRun();

	//takes pointer to log file class (it is needed for correct module working
	void InsertLog(CLog *Tlog);

	//Connect to WMI root\\CIMV2
	int ConnectWMI( string SComp = "local", string SUser = "", string SPass = "");

	//execute file
	int ExecMethod(string SMeth);

	//terminate process
	int Terminate(UINT ID);
	int Terminate(string Name);

	//start wait until
	int WaitExeEnd(UINT ID);
	int WaitExeEnd(string Name);

	// is taced procees dead?
	bool IsProcessDead();

	//get info about machine
	std::vector<SDiskInfo> GetDiskInfo();
	SSysInfo GetSysInfo();
	std::vector<SProcessInfo> GetProcessInfo();

	//end waiting
	void EndWait();


	//it frees up memory
	void Free();


private:

	CLog *Log;
	
	short int CRED_MAX_USERNAME_LENGTH ;
	short int CRED_MAX_CREDENTIAL_BLOB_SIZE ;
	short int CREDUI_MAX_USERNAME_LENGTH ;
	short int CREDUI_MAX_PASSWORD_LENGTH ;


	wchar_t *pszName;
	wchar_t *pszPwd;

	HRESULT hres;

	//localization string
	string localization;

	//localization pointers
	IWbemServices *pSvc;
	IWbemLocator *pLoc;

	// method for execution and parameters
	IWbemClassObject* pClass;
	IWbemClassObject* pInParamsDefinition;
	IWbemClassObject* pClassInstance;
	IWbemClassObject* pOutParams;

	//UnsecuredApartment
	IUnsecuredApartment* pUnsecApp;

	//Sink object
	EventSink* pSink;
	IUnknown* pStubUnk;
	IWbemObjectSink* pStubSink;

	//keeps connecting status
	bool BConnected;
	
	string Name; //process Name
	UINT PID; //process ID
	UINT ReturnVal; //returned value

	std::vector<SDiskInfo> DiskInfo;
	std::vector<SProcessInfo> ProcessInfo;
	SSysInfo SysInfo;

	int CheckProcess();
	int CheckSys();
	int CheckDiskinfo();

};

#endif