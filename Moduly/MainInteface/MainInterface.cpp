#include "MainInterface.h"

void MainInterface::Init(CLog *TLog, ChkPrg *TChecker, CWMIRun *WMI, SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, 
	std::string Textures, std::vector<CUinstPrgCont> *Programslst, std::string FontPath)
{
	Phase = LOCALCH;
	Log = TLog;
	ScrWidth = ScrW;
	ScrHeight = ScrH;
	TexCont.Init(Render, TLog);
	LoadPos(TLog, Render,1);

	Checker = TChecker;
	RExec = WMI;


	SDL_Rect butpos;
	butpos.x = 0;
	butpos.y = 0;
	butpos.w = 100;
	butpos.h = 50;
	WAIWin.Init(TLog, TexCont.LoadTex(GetTexbyID(1)), Render, butpos, ScrW, ScrH,  FontPath);

	
	PrgChkBox.Init(TLog, ScrW ,ScrH ,Render, Programslst,FontPath, TexCont.LoadTex(Textures.c_str()));

}

void MainInterface::Render()
{
	switch(Phase)
	{
	case LOCALCH:
		Local.Render();
		Remote.Render();
		break;

	case GETIP:

		WAIWin.Render();

		break;

	case PRG_SELECT:

		break;

	case UNINST_STATUS:

		break;
	}
} 

void MainInterface::Update()
{

}

void MainInterface::HandleEvent(SDL_Event *e)
{
	switch(Phase)
	{
	case LOCALCH:
		if (Local.HandleEvent(e))
		{
			Programs = Checker->GetPrgandPath();
			PrgChkBox.SetNewProgramList(&Programs);
			RExec->ConnectWMI();

			Phase = PRG_SELECT;

		}

		if(Remote.HandleEvent(e)) Phase = GETIP;

		break;

	case GETIP:

		if (WAIWin.HandleEvent(e))
		{
			//getting info
			IP = WAIWin.GetIP();
			USER = WAIWin.GetUser();
			PASSWORD = WAIWin.GetPassword();

			//startring service
			CRSrvStart RSrv;
			RSrv.InsertLog(Log);
			RSrv.StartRemoteService(IP,"RemoteRegistry");

			//getting program list
			Programs = Checker->GetPrgandPath(IP);
			PrgChkBox.SetNewProgramList(&Programs);
			if(USER == "Domyœlny u¿ytkownik")RExec->ConnectWMI(IP);
			else RExec->ConnectWMI(IP, USER, PASSWORD);

			// stoping service
			RSrv.StopRemoteService(IP,"RemoteRegistry");

			Phase = PRG_SELECT;

		}
		break;

	case PRG_SELECT:

		break;

	case UNINST_STATUS:

		break;
	}
}

bool MainInterface::IsQuit()
{
	return BQuit;
}

void MainInterface::LoadPos(CLog *TLog, SDL_Renderer* Render, int ID)
{
	unsigned int FirstW = 100; //first 2 buttons width
	unsigned int FirstH = 50; //first 2 buttons height
	Local.Init(((ScrWidth/2) - FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(GetTexbyID(ID)),0,0, TLog,Render);
	Remote.Init(((ScrWidth/2) + FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(GetTexbyID(ID)),0,0, TLog,Render);

}

const char* MainInterface::GetTexbyID(int ID)
{
	switch (ID)
	{
	case 1:
		return "Textures/Button.png";
	case 2:
		return "Textures/Slider1.png";
	case 3:
		return "Textures/Slider2.png";
	}
}