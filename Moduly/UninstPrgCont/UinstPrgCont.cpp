#include "UinstPrgCont.h"

int CUinstPrgCont::Add(std::string TName, std::string Uninst, std::string QUninst)
{
	BChecked = false;

	Name = TName;

	//there is already quiet uninstall
	if(QUninst != "") 
	{
		Uninsstr = QUninst;
		StrState = UStr_OK;
		return UStr_OK;
	}

	std::transform(Uninst.begin(), Uninst.end(), Uninst.begin(), ::tolower); //change all character to lower
	
	//checks is it msiexec path
	if(Uninst.find("msiexec") != std::string::npos)
	{
		auto pos = Uninst.find("/i");
		if(pos != std::string::npos) Uninst.replace(pos,2,"/x");
		Uninsstr = Uninst + " /quiet /norestart";
		StrState = UStr_OK;
		return UStr_OK;
	}

	//its not msiexec
	if(Uninst.find_last_of(".exe") != std::string::npos)
	{
		Uninsstr = Uninst;
		StrState = UStr_EXE;
		return UStr_EXE;
	}

	//when its something else
	StrState = UStr_Unknown;
	return UStr_Unknown;
}