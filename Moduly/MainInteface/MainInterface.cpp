#include "MainInterface.h"

void CMainInterface::Init(CLog *TLog, ChkPrg *TChecker , CWMIRun *WMI , SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, std::string FontPath)
{
	Phase = LOCALCH;
	Log = TLog;
	ScrWidth = ScrW;
	ScrHeight = ScrH;
	TexCont.Init(Render, TLog);
	LoadPos(TLog, Render,1,FontPath);

	Checker = TChecker;
	RExec = WMI;

	SDL_Rect butpos;
	butpos.x = 0;
	butpos.y = 0;
	butpos.w = 100;
	butpos.h = 50;
	WAIWin.Init(TLog, TexCont.LoadTex(GetTexbyID(1)), Render, butpos, ScrW, ScrH,  FontPath);
	Select.Init(TLog, RExec, ScrW, ScrH, Render, &Programs, FontPath, TexCont.LoadTex(GetTexbyID(2)), TexCont.LoadTex(GetTexbyID(3)), TexCont.LoadTex(GetTexbyID(1)));

	BQuit = false;
}

void CMainInterface::Render()
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

		Select.Render();

		break;

	case UNINST_STATUS:

		break;
	}
} 

void CMainInterface::Update()
{
	Select.Update();
}

void CMainInterface::HandleEvent(SDL_Event *e)
{
	switch(Phase)
	{
	case LOCALCH:
		if (Local.HandleEvent(e))
		{
			Programs = Checker->GetPrgandPath();
			RExec->ConnectWMI();
			Select.SetPrg(&Programs);
			Select.SetWhereConnected("Ten Komputer");
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
			Checker->InstrtWMIPointer(RExec);
			Programs = Checker->GetPrgandPath(IP, USER, PASSWORD);
			
			if(USER == "Domniemany")RExec->ConnectWMI(IP);
			else RExec->ConnectWMI(IP, USER, PASSWORD);

			Select.SetPrg(&Programs);
			Select.SetWhereConnected(IP);

			// stoping service
			RSrv.StopRemoteService(IP,"RemoteRegistry");

			Phase = PRG_SELECT;

		}
		break;

	case PRG_SELECT:

		Select.HandleEvent(e);

		break;

	case UNINST_STATUS:

		break;
	}
}

bool CMainInterface::IsQuit()
{
	return BQuit;
}

void CMainInterface::LoadPos(CLog *TLog, SDL_Renderer* Render, int ID, std::string Font)
{
	unsigned int FirstW = 100; //first 2 buttons width
	unsigned int FirstH = 50; //first 2 buttons height
	Local.Init(((ScrWidth/2) - FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(GetTexbyID(ID)),0,0, TLog,Render,"","",Font);
	Local.SetCaption("Lokalny");
	Remote.Init(((ScrWidth/2) + FirstW),((ScrHeight/2) - FirstH/2),FirstW,FirstH,TexCont.LoadTex(GetTexbyID(ID)),0,0, TLog,Render,"","",Font);
	Remote.SetCaption("W sieci");

}

const char* CMainInterface::GetTexbyID(int ID)
{
	switch (ID)
	{
	case 1:
		return "Textures/Buttons.png";
	case 2:
		return "Textures/Slider1.png";
	case 3:
		return "Textures/Slider2.png";
	}
}