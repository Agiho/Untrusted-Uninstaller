#include "ChkPrg.h"

ChkPrg::ChkPrg()
{
	if(!PrgDel.empty()) PrgDel.clear();
}

ChkPrg::~ChkPrg()
{
	Free();
}

void ChkPrg::InstgertLog(CLog *TLog)
{
	Log = TLog;
}

std::vector<CUinstPrgCont> ChkPrg::GetPrgandPath(std::string Computer)
{
	Free();
	if(Computer == "local")
	{
		CheckAll();
		if(Is64BitOS()) CheckAll("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	}
	else 
	{
		CheckAll("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",Computer);
		if(IsRemote64OS(Computer)) 
		{ 
			CheckAll("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall",Computer);
		}
	}
	return PrgDel;
}

void ChkPrg::QueryKey(HKEY hKey)
{
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME_LENGHT]; 
    DWORD cchValue = MAX_VALUE_NAME_LENGHT; 
 
    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
		 for (i=0; i<cSubKeys; i++) 
		{
				 cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hKey, i,
				achKey, 
				&cbName, 
				NULL, 
				NULL, 
				NULL, 
				&ftLastWriteTime); 

				//no error
			if (retCode == ERROR_SUCCESS) 
			{
				HKEY subKey;
				retCode = RegOpenKeyEx(hKey, 
				achKey,
				0, KEY_READ,
				&subKey);				
				if(retCode == ERROR_SUCCESS) QueryKey(subKey);
				else Log->WriteTxt("Can't open registry key\n");
			}
			else Log->WriteTxt("Can't open registry key\n");
		}
    } 
 
    // Enumerate the key values. 

    if (cValues) 
    {
       //temporary string variables for hold name and path
		std::string STempName = "";
		std::string STempPath = "";
		std::string SQuietUninst = "";

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
			const int SIZE = 128;
			char value[SIZE];
			DWORD value_length = SIZE;

            cchValue = MAX_VALUE_NAME_LENGHT; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                (LPBYTE)&value,
                &value_length);

			//no error
            if (retCode == ERROR_SUCCESS ) 
            { 

				std::string str = achValue;
				if (str == "DisplayName") 
				{
						//Assing Application name to variable
						STempName = value;					
				}
				if (str == "UninstallString") 
				{
						//Assing Application Uninstall path to variable
						STempPath = value;
				}
				
				if (str == "QuietUninstallString") 
				{
						//Assing Application Quiet Uninstall path to variable
						SQuietUninst = value;						
				}
            } 
        }
		//Add Program to container
		if (STempPath != "")
		{			
			CUinstPrgCont Temp;
			Temp.Add(STempName, STempPath, SQuietUninst);
			PrgDel.push_back(Temp);		
			STempName.clear();
			STempPath.clear();
			SQuietUninst.clear();
		}

    }
}

void ChkPrg::CheckAll(std::string WhichKey, std::string Computer)
{
	HKEY hOpenKey;
	if(Computer == "local")
	{
		//local section 
		
		//Open Key specified in WhichKey for read
		if(Is64BitOS())
		{
			if( RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT(WhichKey.c_str()),0, KEY_READ | KEY_WOW64_64KEY, &hOpenKey) == ERROR_SUCCESS)
			{
				Log->WriteTxt("Opening key on local computer \n");
				QueryKey(hOpenKey);
			}
			else
			{
				Log->WriteTxt("Can't open key " + WhichKey + " on local machine\n");
			}
		}
		else
			{
			if( RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT(WhichKey.c_str()),0, KEY_READ, &hOpenKey) == ERROR_SUCCESS)
			{
				Log->WriteTxt("Opening key on local computer \n");
				QueryKey(hOpenKey);
				}
			else
			{
				Log->WriteTxt("Can't open key " + WhichKey + " on local machine\n");
			}
		}
	  
	}
	else
	{
		RegConnectRegistry(Computer.c_str(),HKEY_LOCAL_MACHINE,&hOpenKey);
	
	   if( RegOpenKeyEx(hOpenKey, TEXT(WhichKey.c_str()), 0, KEY_ALL_ACCESS /* | KEY_WOW64_64KEY*/, &hOpenKey) == ERROR_SUCCESS )
	   {
		   Log->WriteTxt("Opening key on " + Computer + "\n");
		   QueryKey(hOpenKey);
	   }
	   else
	   {
		   Log->WriteTxt("Can't open key " + WhichKey + " on " + Computer + "\n");
	   }

	}

	//Close registry key
	RegCloseKey(hOpenKey);
}

BOOL ChkPrg::Is64BitOS()
{
   BOOL bIs64BitOS = FALSE;

   // We check if the OS is 64 Bit
   typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL); 

   LPFN_ISWOW64PROCESS
      fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
      GetModuleHandle("kernel32"),"IsWow64Process");
 
   if (NULL != fnIsWow64Process)
   {
      if (!fnIsWow64Process(GetCurrentProcess(),&bIs64BitOS))
      {
          //error
		  Log->WriteTxt("Can't recognize archicetrue \n");
      }
   }
   return bIs64BitOS;
}

bool ChkPrg::IsRemote64OS(std::string SRemoteIP)
{
	CWMIRun WMICheck;
	WMICheck.InsertLog(Log);

	WMICheck.ConnectWMI(SRemoteIP);
	//checks is process running on 64bit machine
	std::string VerOS = (WMICheck.GetSysInfo()).OSArch;	
	//WMICheck.Free();
	if(VerOS == "64-bit") return true;
	else return false;

}

void ChkPrg::Free()
{
	if( !PrgDel.empty())
	{
		//delete all elements
		PrgDel.erase(PrgDel.begin(),PrgDel.end());
	}
}