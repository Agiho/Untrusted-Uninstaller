#ifndef UninstMgr_h
#define UninstMgr_h

#include <memory>
#include "WMIRun.h"
#include "MsgBox.h"
#include "UinstPrgCont.h"

class CUninstMgr
{

public:

	CUninstMgr();

	void Init(CLog *TLog);
	 
	void AddCred( std::string TUser = "", std::string TPass = "");

	void StartUninstall(std::vector<std::string> Where, std::vector<CUinstPrgCont> TUninstlst);

	void Update();

	std::vector<std::pair<int, bool> > GetStatus();

private:

	CLog *Log;

	std::string User;

	std::string Pass;

	CMsgBox InfoMsg;

	std::vector<std::unique_ptr<CWMIRun> > WMIobj;

	std::vector<bool> CanWait;

	std::vector<CUinstPrgCont> Uninstlst;
	
	std::vector<std::pair<int, bool> > About; 

};
#endif