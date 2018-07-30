#ifndef ChkPrg_h
#define ChkPrg_h

#include <string>
#include <map>
#include <tchar.h>
#include <windows.h>
#include "Log.h"
#include "WMIRun.h"
#include "UinstPrgCont.h"

class ChkPrg
{
public:
	
	ChkPrg();
	~ChkPrg();

	//takes log file
	void InsertLog(CLog *TLog);

	// akes pointer to WMI object for use it in class
	void InstertWMIPointer(CWMIRun *TWMI);

	//return program name and path to uninstall it
	std::vector<CUinstPrgCont> GetPrgandPath(std::string Computer = "local", std::string User = "", std::string Pass = "");

private:
	
	CLog *Log;

	CWMIRun *WMI;

	// const value for use in arrays
	static const unsigned short int MAX_KEY_LENGTH  = 255;
	static const unsigned short int MAX_VALUE_NAME_LENGHT = 16383;

	//holds program names and path to uninstallation
	std::vector<CUinstPrgCont> PrgDel;

	// query registry key for data and place it in PrgDel
	void QueryKey(HKEY hKey, std::string Key = "");

	//loads DisplayName and UninstallString for programs to map
	void CheckAll(std::string WhichKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", std::string Computer = "local");

	//checks local system
	BOOL Is64BitOS();

	//check remote system
	bool IsRemote64OS(std::string SRemoteIP, std::string User = "", std::string Pass = "");

	//get registy keys using WMI
	void CheckRemote64Keys(std::string SRemoteIP, std::string MainKey = "HKEY_LOCAL_MACHINE", std::string WhichKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\", std::string User = "", std::string Pass = "");

	//erases map content andd frees memory
	void Free();

};

#endif