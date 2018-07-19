#include "UninstMgr.h"

CUninstMgr::CUninstMgr()
{
	User = "";

	Pass = "";

}

void CUninstMgr::Init(CLog *TLog)
{
	Log = TLog;

	InfoMsg.IstertLog(TLog);
	InfoMsg.MakeOK();
}

void CUninstMgr::AddCred(std::string TUser, std::string SPass)
{
	User = TUser;
	Pass = SPass;
}

void CUninstMgr::StartUninstall(std::vector<std::string> Where, std::vector<CUinstPrgCont> TUninstlst)
{

	Uninstlst = TUninstlst;
	
	for(int i = 0; i < Where.size(); ++i)
	{
	
		CWMIRun *WMI = new CWMIRun;
		WMI->InsertLog(Log);
		WMI->SecPrevAdded(true);
		WMI->ConnectWMI(Where[i],User, Pass);
		if(!TUninstlst.empty()) 
		{
			std::pair<int, bool> AboutWMIObj;
			AboutWMIObj.first = 0;
			AboutWMIObj.second = false;
			bool BCanWait = true;
			WMI->ExecMethod(TUninstlst[0].Uninsstr);
			if(WMI->WaitExeEnd(WMI->GetLastPID()) == 2)
			{
				InfoMsg.ShowMsg("Problem z oczekiwaniem na koniec procesu", "Na komputerze: " + Where[i] + " jest dozwolone jedynie odinstalowywanie oprogramowania po jednym na raz.");
				BCanWait = false;
				WMI->EndWait();
			}

			CanWait.push_back(BCanWait);
			WMIobj.push_back(std::unique_ptr<CWMIRun>(WMI));
			About.push_back(AboutWMIObj);
		}

	}
}

void CUninstMgr::Update()
{
	if(!WMIobj.empty())
	{

		for(int i = 0; i < WMIobj.size(); ++i)
		{
			if(CanWait[i])
			{
				if(WMIobj[i]->IsProcessDead() && !About[i].second)
				{
					if(About[i].first + 1 < Uninstlst.size())
					{
						About[i].first = About[i].first + 1;
						WMIobj[i]->ExecMethod(Uninstlst[About[i].first].Uninsstr);
						WMIobj[i]->WaitExeEnd(WMIobj[i]->GetLastPID());
						if(WMIobj[i]->WaitExeEnd(WMIobj[i]->GetLastPID()) == 2)
						{
							InfoMsg.ShowMsg("Problem z oczekiwaniem na koniec procesu" ,"Na komputerze: " + WMIobj[i]->Getloc() + " jest dozwolone jedynie odinstalowywanie oprogramowania po jednym na raz.");
							CanWait[i] = false;
							//About[i].second = true;
							WMIobj[i]->EndWait();
						}
					}
					else About[i].second = true;
				}
			}
		}
	}
}

std::vector<std::pair<int, bool> > CUninstMgr::GetStatus()
{
	return About;
}