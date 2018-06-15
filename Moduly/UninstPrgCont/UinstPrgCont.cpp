#include "UinstPrgCont.h"

int CUinstPrgCont::Add(std::string TName, std::string Uninst, std::string QUninst)
{
	BChecked = false;

	Name = TName;

	//there is already quiet uninstall
	if(QUninst != "") 
	{
		Uninsstr = QUninst;
		return UStr_OK;
	}

	std::transform(Uninst.begin(), Uninst.end(), Uninst.begin(), ::tolower);
	
	//checks is it msiexec path
	if(Uninst.find("msiexec") != std::string::npos)
	{
		auto pos = Uninst.find("/i");
		if(pos != std::string::npos) Uninst.replace(pos,2,"/x");
		Uninsstr = Uninst + " /quiet /norestart";
		return UStr_OK;
	}

	//its not msiexec
	if(Uninst.find_last_of(".exe") != std::string::npos)
	{
		Uninsstr = Uninst;
		return UStr_EXE;
	}

	return UStr_Unknown;
}