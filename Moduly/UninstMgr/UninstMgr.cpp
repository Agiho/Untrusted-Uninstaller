#include "UninstMgr.h"

CUninstMgr::CUninstMgr()
{
	User = "";

	Pass = "";

}

void CUninstMgr::Init(CLog *TLog, CTerminator *TTerminator)
{
	Log = TLog;
	Terminator = TTerminator;

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

	Uninstlst = TUninstlst; // copy uninstall paths
	
	//create WMI object fo each computer and start first uninstall process, and try to start wait for process end function 
	for(int i = 0; i < Where.size(); ++i)
	{
	
		CWMIRun *WMI = new CWMIRun;
		WMI->InsertLog(Log);
		WMI->SecPrevAdded(true); //there shoudl always exist WMI object which connect somewhere before using this class
		WMI->ConnectWMI(Where[i],User, Pass); //connect
		Log->WriteTxt("Time to terminate");
		if(Terminator != nullptr) if(WMI->IsConnected()) Terminator->Terminate(WMI); //terminate all checked processes in container i terminator
		if(!TUninstlst.empty()) 
		{
			//create info object about uninstall processes on this computer
			std::pair<int, bool> AboutWMIObj;
			AboutWMIObj.first = 0;
			AboutWMIObj.second = false;

			bool BCanWait = true;
			int Error = WMI->ExecMethod(TUninstlst[0].Uninsstr); //execute method
			if(Error)
			{
				InfoMsg.ShowMsg("Problem z wykonaniem instrukcji " + Where[i], "Niepowodzenie uruchomienia procesu odinstalowywania na komputerze: " + Where[i]);
			}
			else if(WMI->WaitExeEnd(WMI->GetLastPID()) == 2) //try to start wait function
			{
				InfoMsg.ShowMsg("Problem z oczekiwaniem na koniec procesu", "Na komputerze: " + Where[i] + " jest dozwolone jedynie odinstalowywanie oprogramowania po jednym na raz.");
				BCanWait = false;
				WMI->EndWait();
			}

			if(Error) delete WMI; // when can't execute methods on computer, don't need keep it in containers
			else
			{
				//pushes information object and WMI object for each computer to containers
				CanWait.push_back(BCanWait);
				WMIobj.push_back(std::unique_ptr<CWMIRun>(WMI));
				About.push_back(AboutWMIObj);
			}
		}

	}
	Terminator->ClrLst();
}

void CUninstMgr::Update()
{
	if(!WMIobj.empty()) //if there exist objects
	{

		for(int i = 0; i < WMIobj.size(); ++i)
		{
			if(CanWait[i]) //if object can wait for end
			{
				if(WMIobj[i]->IsProcessDead() && !About[i].second) //if last process is dead and its not last process
				{
					if(About[i].first + 1 < Uninstlst.size()) //checks is it last process
					{
						About[i].first = About[i].first + 1; // change info about which process currently is running
						WMIobj[i]->ExecMethod(Uninstlst[About[i].first].Uninsstr); // execute new process
						if(WMIobj[i]->WaitExeEnd(WMIobj[i]->GetLastPID()) == 2)//wait for process end
						{
							InfoMsg.ShowMsg("Problem z oczekiwaniem na koniec procesu" ,"Na komputerze: " + WMIobj[i]->Getloc() + " jest dozwolone jedynie odinstalowywanie oprogramowania po jednym na raz.");
							CanWait[i] = false;

							WMIobj[i]->EndWait();
						}
					}
					else About[i].second = true; //when all uninstall processes ends
				}
			}
		}
	}
}

std::vector<std::pair<int, bool> > CUninstMgr::GetStatus()
{
	return About;
}