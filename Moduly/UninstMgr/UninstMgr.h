#ifndef UninstMgr_h
#define UninstMgr_h

#include <memory>
#include "WMIRun.h"
#include "MsgBox.h"
#include "UinstPrgCont.h"
#include "Terminator.h"

class CUninstMgr
{

public:

	CUninstMgr();

	void Init(CLog *TLog, CTerminator *TTerminator = nullptr); //get pointer to Log and creates InfoBox
	 
	void AddCred( std::string TUser = "", std::string TPass = ""); //Add User and Password

	void StartUninstall(std::vector<std::string> Where, std::vector<CUinstPrgCont> TUninstlst); //start uninstall process

	void Update(); //menage uninstall processes

	std::vector<std::pair<int, bool> > GetStatus(); // returns status for all programs

private:

	CLog *Log;

	CTerminator *Terminator;

	std::string User; //username

	std::string Pass; //password

	CMsgBox InfoMsg; // box with message for user

	std::vector<std::unique_ptr<CWMIRun> > WMIobj; //container with connected WMI objects

	std::vector<bool> CanWait; //true when wait option in WMI object works

	std::vector<CUinstPrgCont> Uninstlst; //uninstall paths container
	
	std::vector<std::pair<int, bool> > About; // which program currenlty executing, true when all finished, in which WMI object(specified ovject in container)

};
#endif