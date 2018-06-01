#include "RSrvStart.h"

RSrvStart::RSrvStart()
{
	RemoteLoc = "";

	WhichSrv = "";

	Started = false;

	hSCM = NULL;
}

void RSrvStart::InsertLog( CLog *TLog)
{
	Log = TLog;
}

int RSrvStart::StartRemoteService(std::string Where, std::string Which)
{
	Started = false;
	//access service control manager
	WhichSrv = "";
	WhichSrv.clear();
	RemoteLoc = "";
	RemoteLoc.clear();
	RemoteLoc = Where;
	WhichSrv = Which;
    SC_HANDLE hSCM = OpenSCManager(const_cast<char *>(RemoteLoc.c_str()),
                       SERVICES_ACTIVE_DATABASE,
                       SC_MANAGER_ALL_ACCESS);

	SC_HANDLE hService = OpenService(hSCM, const_cast<char *>(WhichSrv.c_str()), SERVICE_START);

	if (hService == NULL)
    {
		Log->WriteTxt("ERROR: COULDN'T ACCESS SERVICE\n");
        return 1;
    }

	if(StartService(hService, 0, NULL)==0)
    {
		Log->WriteTxt(GetLastError());
		return 1;
    }


	if(StartService(hService, 0, NULL)==0)
    {
		Log->WriteTxt(GetLastError());
		return 1;
    }
 
    CloseServiceHandle(hService);

	Started = true;
	return 0;
}

int RSrvStart::StopRemoteService(std::string Where, std::string Which)
{
	SC_HANDLE hService = ::OpenService(hSCM, 
                                       const_cast<char *>(WhichSrv.c_str()),
                                       SERVICE_STOP);
 
    if (hService == NULL)
    {
		Log->WriteTxt("ERROR: COULDN'T OPEN SERVICE\n");
        return 1;
    }
 
    SERVICE_STATUS status;
    if(!ControlService(hService, SERVICE_CONTROL_STOP,&status)) 
	{
		Log->WriteTxt("ERROR: COULDN'T STOP SERVICE\n");
		return 1;
	}
 
    CloseServiceHandle(hService);

	CloseServiceHandle(hSCM);
	
	Started = false;

	return 0;
}